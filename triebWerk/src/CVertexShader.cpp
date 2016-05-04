#include <CVertexShader.h>

triebWerk::CVertexShader::CVertexShader()
{
	m_ShaderType = IShader::EShaderType::Vertex;
}

triebWerk::CVertexShader::~CVertexShader()
{
	//m_pD3DVertexShader->Release();
}

void * triebWerk::CVertexShader::GetD3D11Shader()
{
	return m_pD3DVertexShader;
}
