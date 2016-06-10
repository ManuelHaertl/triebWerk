#include <CGeometryShader.h>

triebWerk::CGeometryShader::CGeometryShader() :
	m_pD3DGeometryShader(nullptr)
{

}

triebWerk::CGeometryShader::~CGeometryShader()
{
}

void * triebWerk::CGeometryShader::GetD3D11Shader()
{
	return m_pD3DGeometryShader;
}
