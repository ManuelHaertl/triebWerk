#include <CHLSLParser.h>
#include <iostream>

triebWerk::CHLSLParser::CHLSLParser() :
	m_pVSByteCode(nullptr),
	m_pPSByteCode(nullptr),
	m_pHSByteCode(nullptr),
	m_pGSByteCode(nullptr),
	m_pDSByteCode(nullptr),
	m_pCSByteCode(nullptr)
{
}

triebWerk::CHLSLParser::~CHLSLParser()
{
}

void triebWerk::CHLSLParser::ParseShader(const char* a_pShaderPath, CGraphics* a_pGraphicHandle, CMaterial* a_pMaterialOut)
{
	CompileShader(a_pShaderPath);

	std::string name = a_pShaderPath;
	name = name.substr(name.rfind("\\") + 1, name.size() - name.rfind("\\"));
	name = name.substr(0, name.find("."));

	a_pMaterialOut->m_ID.SetName(name);

	SetConstantBuffers(m_pVSByteCode, &a_pMaterialOut->m_ConstantBuffer);

	a_pMaterialOut->m_ConstantBuffer.InitializeConstantBufffer(a_pGraphicHandle->GetDevice());

	if (m_pVSByteCode != nullptr)
		CreateVertexShader(a_pGraphicHandle, &a_pMaterialOut->m_pVertexShader);

	if (m_pPSByteCode != nullptr)
		CreatePixelShader(a_pGraphicHandle, &a_pMaterialOut->m_pPixelShader);
}

void triebWerk::CHLSLParser::CreateVertexShader(CGraphics* a_pGraphicHandle, CVertexShader* a_pShaderOut)
{
	HRESULT hResult;

	a_pShaderOut->SetInputLayout(GetInputLayout(m_pVSByteCode, a_pGraphicHandle));

	SetBoundResources(m_pVSByteCode, a_pShaderOut);

	hResult = a_pGraphicHandle->GetDevice()->CreateVertexShader(m_pVSByteCode->GetBufferPointer(), m_pVSByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DVertexShader);
}

void triebWerk::CHLSLParser::CreatePixelShader(CGraphics* a_pGraphicHandle, CPixelShader* a_pShaderOut)
{
	HRESULT hResult;

	a_pShaderOut->SetInputLayout(GetInputLayout(m_pPSByteCode, a_pGraphicHandle));

	SetBoundResources(m_pPSByteCode, a_pShaderOut);

	hResult = a_pGraphicHandle->GetDevice()->CreatePixelShader(m_pPSByteCode->GetBufferPointer(), m_pPSByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DPixelShader);
}


void triebWerk::CHLSLParser::WriteCompileError(ID3DBlob * a_pMessage)
{
	if (a_pMessage != nullptr)
	{
		LPVOID pCompileErrors = a_pMessage->GetBufferPointer();
		const char* pMessage = (const char*)pCompileErrors;
		std::cout << pMessage << std::endl;
	}
}

void triebWerk::CHLSLParser::CompileShader(const char * a_pShaderPath)
{
	ID3DBlob* pErrorMessage;
	HRESULT hResult;

	//Cast shader path to widechar 
	WCHAR shaderPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(0, 0, a_pShaderPath, static_cast<int>(strlen(a_pShaderPath)), shaderPath, MAX_PATH);

	//Try to find EntryPoint for specific Shader if found compile the Shader

	//Vertex Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_VSEntryPoint.c_str(), "vs_5_0", m_CompileFlags, 0, &m_pVSByteCode, &pErrorMessage);
	if (FAILED(hResult))
		m_pVSByteCode = nullptr;

	//Pixel Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_PSEntryPoint.c_str(), "ps_5_0", m_CompileFlags, 0, &m_pPSByteCode, &pErrorMessage);
	if (FAILED(hResult))
		m_pPSByteCode = nullptr;

	//Hull Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_HSEntryPoint.c_str(), "hs_5_0", m_CompileFlags, 0, &m_pHSByteCode, &pErrorMessage);
	if (FAILED(hResult))
		m_pHSByteCode = nullptr;

	//Geometry Shader------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_HSEntryPoint.c_str(), "gs_5_0", m_CompileFlags, 0, &m_pHSByteCode, &pErrorMessage);
	if (FAILED(hResult))
		m_pHSByteCode = nullptr;

	//Domain Shader------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_DSEntryPoint.c_str(), "ds_5_0", m_CompileFlags, 0, &m_pDSByteCode, &pErrorMessage);
	if (FAILED(hResult))
		m_pDSByteCode = nullptr;

	//Compute Shader------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_CSEntryPoint.c_str(), "cs_5_0", m_CompileFlags, 0, &m_pCSByteCode, &pErrorMessage);
	if (FAILED(hResult))
		m_pCSByteCode = nullptr;
}

ID3D11InputLayout* triebWerk::CHLSLParser::GetInputLayout(ID3DBlob * a_pShaderByteCode, CGraphics* a_pGraphicHandle)
{
	HRESULT hResult;

	ID3D11ShaderReflection* pReflector = nullptr;
	hResult = D3DReflect(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);

	D3D11_SHADER_DESC shaderDescription;

	pReflector->GetDesc(&shaderDescription);

	D3D11_INPUT_ELEMENT_DESC* inputLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDescription.InputParameters];

	for (UINT i = 0; i < shaderDescription.InputParameters; i++)
	{
		D3D11_INPUT_ELEMENT_DESC element;

		D3D11_SIGNATURE_PARAMETER_DESC inputDesc;
		pReflector->GetInputParameterDesc(i, &inputDesc);

		//TODO: Instacing ?
		element.SemanticName = inputDesc.SemanticName;
		element.SemanticIndex = inputDesc.SemanticIndex;
		element.Format = DetermineInputFormat(inputDesc);
		element.InputSlot = 0;
		element.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; //convenience to define the current element directly after the previous one, including any packing if necessary.
		element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		element.InstanceDataStepRate = 0;

		inputLayoutDesc[i] = element;
	}

	ID3D11InputLayout * layout = nullptr;

	hResult = a_pGraphicHandle->GetDevice()->CreateInputLayout(inputLayoutDesc, shaderDescription.InputParameters, a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), &layout);

	delete inputLayoutDesc;
	pReflector->Release();

	return layout;
}

void triebWerk::CHLSLParser::SetConstantBuffers(ID3DBlob* a_pShaderByteCode, triebWerk::CConstantBuffer* a_pConstantBuffer)
{
	HRESULT hResult;

	ID3D11ShaderReflection* pReflector = nullptr;
	hResult = D3DReflect(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);

	D3D11_SHADER_DESC shaderDescription;

	pReflector->GetDesc(&shaderDescription);

	for (UINT i = 0; i < shaderDescription.ConstantBuffers; i++)
	{
		ID3D11ShaderReflectionConstantBuffer* pConstantBuffer = pReflector->GetConstantBufferByIndex(i);
		pConstantBuffer->GetDesc(&a_pConstantBuffer->BuffferDescription);
		 
		for (UINT j = 0; j < a_pConstantBuffer->BuffferDescription.Variables; j++)
		{
			ID3D11ShaderReflectionVariable* pVariable = pConstantBuffer->GetVariableByIndex(j);
			D3D11_SHADER_VARIABLE_DESC variableDesc;
			pVariable->GetDesc(&variableDesc);

			a_pConstantBuffer->Variables.push_back(variableDesc);

			ID3D11ShaderReflectionType* pType = pVariable->GetType();
			D3D11_SHADER_TYPE_DESC typeDesc;
			pType->GetDesc(&typeDesc);

			a_pConstantBuffer->Types.push_back(typeDesc);
		}
	}
}

void triebWerk::CHLSLParser::SetBoundResources(ID3DBlob * a_pShaderByteCode, IShader * a_PShader)
{
	HRESULT hResult;

	ID3D11ShaderReflection* pReflector = nullptr;
	hResult = D3DReflect(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);

	D3D11_SHADER_DESC shaderDescription;

	pReflector->GetDesc(&shaderDescription);

	for (size_t i = 0; i < shaderDescription.BoundResources; ++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
		pReflector->GetResourceBindingDesc(static_cast<UINT>(i), &resourceDesc);

		if (resourceDesc.Type == D3D_SIT_TEXTURE)
		{
			a_PShader->m_TextureDescriptions.push_back(resourceDesc);
		}

		if (resourceDesc.Type == D3D_SIT_SAMPLER)
		{
			a_PShader->m_SamplerDescriptions.push_back(resourceDesc);
		}
	}
}

//This function determine the format based on the mask and
//component type of D3D11_SIGNATURE_PARAMETER_DESC
DXGI_FORMAT triebWerk::CHLSLParser::DetermineInputFormat(const D3D11_SIGNATURE_PARAMETER_DESC & a_rSignature)
{
	if (a_rSignature.Mask == 15)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32G32B32A32_UINT;
		else if(a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32G32B32A32_SINT;
		else if(a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}
	else if (a_rSignature.Mask == 0x7)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32G32B32_UINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32G32B32_SINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32G32B32_FLOAT;
	}
	else if (a_rSignature.Mask == 0x3)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32G32_UINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32G32_SINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32G32_FLOAT;
	}
	else if (a_rSignature.Mask == 0x1)
	{
		if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
			return DXGI_FORMAT_R32_UINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
			return DXGI_FORMAT_R32_SINT;
		else if (a_rSignature.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
			return DXGI_FORMAT_R32_FLOAT;
	}

	return DXGI_FORMAT_UNKNOWN;
}