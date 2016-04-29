#include <IShader.h>
#include <iostream>

triebWerk::IShader::IShader()
{
}

triebWerk::IShader::~IShader()
{
	std::cout << "Delete Sghader" << std::endl;
}

void triebWerk::IShader::SetInputLayout(ID3D11InputLayout* a_pInputLayout)
{
	m_pInputLayout = a_pInputLayout;
}

ID3D11InputLayout * triebWerk::IShader::GetInputLayout()
{
	return m_pInputLayout;
}
