#include <CVertexShader.h>

triebWerk::CVertexShader::CVertexShader() :
	m_pCustomInstanceData(nullptr),
	m_pD3DVertexShader(nullptr),
	m_SizeOfInstanceDataBytes(0)
{
	m_ShaderType = IShader::EShaderType::Vertex;
}

triebWerk::CVertexShader::~CVertexShader()
{
	//m_pD3DVertexShader->Release();
	if (m_pCustomInstanceData != nullptr)
	{
		delete[] m_pCustomInstanceData;
		m_pCustomInstanceData = nullptr;
	}

}

void * triebWerk::CVertexShader::GetD3D11Shader()
{
	return m_pD3DVertexShader;
}

void triebWerk::CVertexShader::SetInstanceData(int a_Index, void * a_pAdressOfData, size_t a_ByteSize)
{
	if (m_SizeOfInstanceDataBytes == 0)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: There is no CostumInstanceData to set");
		return;
	}

	int offset = 0;

	for (size_t i = 0; i < a_Index; i++)
	{
		if (m_InputInstanceDescriptions[i].InputSlotClass == D3D11_INPUT_PER_INSTANCE_DATA)
		{
			offset += CGraphics::SizeOfFormatElement(m_InputInstanceDescriptions[i].Format);
		}
	}

	memcpy(m_pCustomInstanceData + offset, a_pAdressOfData, a_ByteSize);
}

void triebWerk::CVertexShader::CreateInstanceData()
{
	for (size_t i = 0; i < m_InputInstanceDescriptions.size(); i++)
	{
		if (m_InputInstanceDescriptions[i].InputSlotClass == D3D11_INPUT_PER_INSTANCE_DATA)
		{
			m_SizeOfInstanceDataBytes += CGraphics::SizeOfFormatElement(m_InputInstanceDescriptions[i].Format);
		}
	}

	if(m_SizeOfInstanceDataBytes == 0)
		return;

	m_pCustomInstanceData = new char[m_SizeOfInstanceDataBytes];
}
