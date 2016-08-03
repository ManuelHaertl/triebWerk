#include <CHLSLParser.h>
#include <iostream>

triebWerk::CHLSLParser::CHLSLParser() :
	m_CompileErrors(false),
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

bool triebWerk::CHLSLParser::ParseShader(const char* a_pShaderPath, CGraphics* a_pGraphicHandle, CMaterial* a_pMaterialOut)
{
	CompileShader(a_pShaderPath);

	std::string name = a_pShaderPath;
	name = name.substr(name.rfind("\\") + 1, name.size() - name.rfind("\\"));
	name = name.substr(0, name.find("."));

	if (m_pPSByteCode == nullptr || m_pVSByteCode == nullptr)
	{
		return false;
	}

	a_pMaterialOut->m_ID.SetName(name);


	SetConstantBuffers(m_pVSByteCode, &a_pMaterialOut->m_ConstantBuffer);

	a_pMaterialOut->m_ConstantBuffer.InitializeConstantBufffer(a_pGraphicHandle->GetDevice());

	if (m_pVSByteCode != nullptr)
		CreateVertexShader(a_pGraphicHandle, &a_pMaterialOut->m_pVertexShader);

	if (m_pPSByteCode != nullptr)
		CreatePixelShader(a_pGraphicHandle, &a_pMaterialOut->m_pPixelShader);

	if (m_pGSByteCode != nullptr)
		CreateGeometryShader(a_pGraphicHandle, &a_pMaterialOut->m_pGeometryShader);

	return true;
}

void triebWerk::CHLSLParser::CreateVertexShader(CGraphics* a_pGraphicHandle, CVertexShader* a_pShaderOut)
{
	HRESULT hResult;

	SetInputLayout(m_pVSByteCode, a_pGraphicHandle, a_pShaderOut);

	SetBoundResources(m_pVSByteCode, a_pShaderOut);

	a_pShaderOut->InitializeTextureBuffer();

	hResult = a_pGraphicHandle->GetDevice()->CreateVertexShader(m_pVSByteCode->GetBufferPointer(), m_pVSByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DVertexShader);

	if (FAILED(hResult))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Vertex Shader could not be created!");
	}

	a_pShaderOut->CreateInstanceData();
}

void triebWerk::CHLSLParser::CreatePixelShader(CGraphics* a_pGraphicHandle, CPixelShader* a_pShaderOut)
{
	HRESULT hResult;

	SetBoundResources(m_pPSByteCode, a_pShaderOut);

	a_pShaderOut->InitializeTextureBuffer();

	hResult = a_pGraphicHandle->GetDevice()->CreatePixelShader(m_pPSByteCode->GetBufferPointer(), m_pPSByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DPixelShader);

	if (FAILED(hResult))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Pixel Shader could not be created!");
	}
}

void triebWerk::CHLSLParser::CreateGeometryShader(CGraphics * a_pGraphicHandle, CGeometryShader * a_pShaderOut)
{
	HRESULT hResult;

	SetBoundResources(m_pGSByteCode, a_pShaderOut);

	a_pShaderOut->InitializeTextureBuffer();

	hResult = a_pGraphicHandle->GetDevice()->CreateGeometryShader(m_pGSByteCode->GetBufferPointer(), m_pGSByteCode->GetBufferSize(), NULL, &a_pShaderOut->m_pD3DGeometryShader);

	if (FAILED(hResult))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Geometry Shader could not be created!");
	}
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
	{
		LogErrors((char*)pErrorMessage->GetBufferPointer());
		m_pVSByteCode = nullptr;
	}


	//Pixel Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_PSEntryPoint.c_str(), "ps_5_0", m_CompileFlags, 0, &m_pPSByteCode, &pErrorMessage);
	if (FAILED(hResult))
	{
		LogErrors((char*)pErrorMessage->GetBufferPointer());
		m_pPSByteCode = nullptr;
	}

	//Hull Shader----------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_HSEntryPoint.c_str(), "hs_5_0", m_CompileFlags, 0, &m_pHSByteCode, &pErrorMessage);
	if (FAILED(hResult))
	{
		std::string errorString = (char*)pErrorMessage->GetBufferPointer();

		//Ignore entry point error because this is a optional shader
		if (errorString.find("X3501") == std::string::npos)
		{
			LogErrors((char*)pErrorMessage->GetBufferPointer());
		}

		m_pHSByteCode = nullptr;
	}


	//Geometry Shader------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_GSEntryPoint.c_str(), "gs_5_0", m_CompileFlags, 0, &m_pGSByteCode, &pErrorMessage);
	if (FAILED(hResult))
	{
		std::string errorString = (char*)pErrorMessage->GetBufferPointer();

		//Ignore entry point error because this is a optional shader
		if (errorString.find("X3501") == std::string::npos)
		{
			LogErrors((char*)pErrorMessage->GetBufferPointer());
		}

		m_pHSByteCode = nullptr;
	}

	//Domain Shader------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_DSEntryPoint.c_str(), "ds_5_0", m_CompileFlags, 0, &m_pDSByteCode, &pErrorMessage);
	if (FAILED(hResult))
	{
		std::string errorString = (char*)pErrorMessage->GetBufferPointer();

		//Ignore entry point error because this is a optional shader
		if (errorString.find("X3501") == std::string::npos)
		{
			LogErrors((char*)pErrorMessage->GetBufferPointer());
		}

		m_pDSByteCode = nullptr;
	}

	//Compute Shader------------------------
	hResult = D3DCompileFromFile(shaderPath, 0, 0, m_CSEntryPoint.c_str(), "cs_5_0", m_CompileFlags, 0, &m_pCSByteCode, &pErrorMessage);
	if (FAILED(hResult))
	{
		std::string errorString = (char*)pErrorMessage->GetBufferPointer();

		//Ignore entry point error because this is a optional shader
		if (errorString.find("X3501") == std::string::npos)
		{
			LogErrors((char*)pErrorMessage->GetBufferPointer());
		}

		m_pCSByteCode = nullptr;
	}
}

void triebWerk::CHLSLParser::SetInputLayout(ID3DBlob * a_pShaderByteCode, CGraphics* a_pGraphicHandle, IShader* a_pShader)
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

		std::string semanticName = inputDesc.SemanticName;
		size_t sematicInstancePosition = semanticName.find("INST"); //The "INST" declares this parameter as D3D11_INPUT_PER_INSTANCE_DATA

		if (sematicInstancePosition != std::string::npos)
		{
			element.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			element.InputSlot = 1;
			element.InstanceDataStepRate = 1;
		}
		else
		{
			element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			element.InputSlot = 0;
			element.InstanceDataStepRate = 0;
		}

		element.SemanticName = inputDesc.SemanticName;
		element.SemanticIndex = inputDesc.SemanticIndex;
		element.Format = DetermineInputFormat(inputDesc);
		element.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; //convenience to define the current element directly after the previous one, including any packing if necessary.
		
		if (sematicInstancePosition != std::string::npos)
		{
			a_pShader->m_InputInstanceDescriptions.push_back(element);
		}

		inputLayoutDesc[i] = element;
	}

	ID3D11InputLayout * layout = nullptr;

	hResult = a_pGraphicHandle->GetDevice()->CreateInputLayout(inputLayoutDesc, shaderDescription.InputParameters, a_pShaderByteCode->GetBufferPointer(), a_pShaderByteCode->GetBufferSize(), &layout);

	delete inputLayoutDesc;
	pReflector->Release();

	a_pShader->SetInputLayout(layout);
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
		pConstantBuffer->GetDesc(&a_pConstantBuffer->m_BuffferDescription);
		 
		for (UINT j = 0; j < a_pConstantBuffer->m_BuffferDescription.Variables; j++)
		{
			ID3D11ShaderReflectionVariable* pVariable = pConstantBuffer->GetVariableByIndex(j);
			D3D11_SHADER_VARIABLE_DESC variableDesc;
			pVariable->GetDesc(&variableDesc);

			a_pConstantBuffer->m_Variables.push_back(variableDesc);

			ID3D11ShaderReflectionType* pType = pVariable->GetType();
			D3D11_SHADER_TYPE_DESC typeDesc;
			pType->GetDesc(&typeDesc);

			a_pConstantBuffer->m_Types.push_back(typeDesc);
		}
	}

	if (shaderDescription.ConstantBuffers == 0 && m_pGSByteCode != nullptr)
	{
		SetConstantBuffers(m_pGSByteCode, a_pConstantBuffer);
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

void triebWerk::CHLSLParser::LogErrors(const char * a_pErrorMessage)
{
	if (m_CompileErrors == false)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Critical error: Could not compile Shader: ");
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, a_pErrorMessage);
		m_CompileErrors = true;
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