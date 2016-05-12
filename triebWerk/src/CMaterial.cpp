#include <CMaterial.h>
#include <CEngine.h>
triebWerk::CMaterial::CMaterial()
{
}

triebWerk::CMaterial::~CMaterial()
{
}

void triebWerk::CMaterial::SetMaterial(const CMaterial * a_pMaterial)
{
	m_ConstantBuffer.BuffferDescription = a_pMaterial->m_ConstantBuffer.BuffferDescription;
	m_ConstantBuffer.Types = a_pMaterial->m_ConstantBuffer.Types;
	m_ConstantBuffer.Variables = a_pMaterial->m_ConstantBuffer.Variables;

	m_ConstantBuffer.InitializeConstantBufffer(CEngine::Instance().m_pGraphics->GetDevice());

	m_pPixelShader = a_pMaterial->m_pPixelShader;
	m_pVertexShader = a_pMaterial->m_pVertexShader;

	m_ID = a_pMaterial->m_ID;

}
