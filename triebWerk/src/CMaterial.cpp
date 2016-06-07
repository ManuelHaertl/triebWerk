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
	if (a_pMaterial == nullptr)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: You tried to set an empty Material!");
		return;
	}
	m_ConstantBuffer.m_BuffferDescription = a_pMaterial->m_ConstantBuffer.m_BuffferDescription;
	m_ConstantBuffer.m_Types = a_pMaterial->m_ConstantBuffer.m_Types;
	m_ConstantBuffer.m_Variables = a_pMaterial->m_ConstantBuffer.m_Variables;

	m_ConstantBuffer.InitializeConstantBufffer(CEngine::Instance().m_pGraphics->GetDevice());

	m_pPixelShader = a_pMaterial->m_pPixelShader;
	m_pPixelShader.InitializeTextureBuffer();
	m_pVertexShader = a_pMaterial->m_pVertexShader;
	m_pVertexShader.InitializeTextureBuffer();
	m_pVertexShader.CreateInstanceData();

	m_ID = a_pMaterial->m_ID;

}
