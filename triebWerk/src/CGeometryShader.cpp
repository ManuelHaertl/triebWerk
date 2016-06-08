#include <CGeometryShader.h>

triebWerk::CGeometryShader::CGeometryShader()
{

}

triebWerk::CGeometryShader::~CGeometryShader()
{
}

void * triebWerk::CGeometryShader::GetD3D11Shader()
{
	return m_pD3DGeometryShader;
}
