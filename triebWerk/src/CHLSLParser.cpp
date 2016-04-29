#include <CHLSLParser.h>
#include <iostream>

triebWerk::CHLSLParser::CHLSLParser()
{
}

triebWerk::CHLSLParser::~CHLSLParser()
{
}

triebWerk::CMaterial* triebWerk::CHLSLParser::ParseShader(const char* a_pShaderPath, CGraphics* a_pGraphicHandle)
{
	CompileShader(a_pShaderPath);

	CMaterial* pMaterial = new CMaterial();

	//Now create the specific Shader if they could be compiled

	if (m_pVSByteCode != nullptr)
		pMaterial->m_pVertexShader = CreateVertexShader(a_pGraphicHandle);

	if (m_pPSByteCode != nullptr)
		pMaterial->m_pPixelShader = CreatePixelShader(a_pGraphicHandle);

	return pMaterial;
}

triebWerk::CVertexShader* triebWerk::CHLSLParser::CreateVertexShader(CGraphics* a_pGraphicHandle)
{
	HRESULT hResult;

	CVertexShader* pVertexShader = new CVertexShader();

	pVertexShader->SetInputLayout(GetInputLayout(m_pVSByteCode, a_pGraphicHandle));

	SetConstantBuffers(m_pVSByteCode, pVertexShader);

	for (size_t i = 0; i < pVertexShader->m_ConstantBuffers.size(); ++i)
	{
		pVertexShader->m_ConstantBuffers[i].InitializeConstantBufffer(a_pGraphicHandle->GetDevice());
	}

	SetBoundResources(m_pVSByteCode, pVertexShader);

	hResult = a_pGraphicHandle->GetDevice()->CreateVertexShader(m_pVSByteCode->GetBufferPointer(), m_pVSByteCode->GetBufferSize(), NULL, &pVertexShader->m_pD3DVertexShader);

	return pVertexShader;
}

triebWerk::CPixelShader* triebWerk::CHLSLParser::CreatePixelShader(CGraphics* a_pGraphicHandle)
{
	HRESULT hResult;

	CPixelShader* pPixelShader = new CPixelShader();

	pPixelShader->SetInputLayout(GetInputLayout(m_pPSByteCode, a_pGraphicHandle));

	SetConstantBuffers(m_pPSByteCode, pPixelShader);

	for (auto constantBuffer : pPixelShader->m_ConstantBuffers)
	{
		constantBuffer.InitializeConstantBufffer(a_pGraphicHandle->GetDevice());
	}

	SetBoundResources(m_pPSByteCode, pPixelShader);

	hResult = a_pGraphicHandle->GetDevice()->CreatePixelShader(m_pPSByteCode->GetBufferPointer(), m_pPSByteCode->GetBufferSize(), NULL, &pPixelShader->m_pD3DPixelShader);

	return pPixelShader;
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
	MultiByteToWideChar(0, 0, a_pShaderPath, strlen(a_pShaderPath), shaderPath, MAX_PATH);

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

void triebWerk::CHLSLParser::SetConstantBuffers(ID3DBlob* a_pShaderByteCode, IShader * a_pShader)
{
	HRESULT hResult;

	ID3D11ShaderReflection* pReflector = nullptr;
	hResult = D3DReflect(a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);

	D3D11_SHADER_DESC shaderDescription;

	pReflector->GetDesc(&shaderDescription);

	for (UINT i = 0; i < shaderDescription.ConstantBuffers; i++)
	{
		CConstantBuffer constantBuffer;
		ID3D11ShaderReflectionConstantBuffer* pConstantBuffer = pReflector->GetConstantBufferByIndex(i);
		pConstantBuffer->GetDesc(&constantBuffer.BuffferDescription);
		 
		for (UINT j = 0; j < constantBuffer.BuffferDescription.Variables; j++)
		{
			ID3D11ShaderReflectionVariable* pVariable = pConstantBuffer->GetVariableByIndex(j);
			D3D11_SHADER_VARIABLE_DESC variableDesc;
			pVariable->GetDesc(&variableDesc);

			constantBuffer.Variables.push_back(variableDesc);

			ID3D11ShaderReflectionType* pType = pVariable->GetType();
			D3D11_SHADER_TYPE_DESC typeDesc;
			pType->GetDesc(&typeDesc);

			constantBuffer.Types.push_back(typeDesc);
		}

		a_pShader->m_ConstantBuffers.push_back(constantBuffer);
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
		pReflector->GetResourceBindingDesc(i, &resourceDesc);

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
