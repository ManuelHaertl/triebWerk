#include "CPostEffectDrawable.h"

triebWerk::CPostEffectDrawable::CPostEffectDrawable()
{
	m_Materials.reserve(5);
}

triebWerk::CPostEffectDrawable::~CPostEffectDrawable()
{
}

//void triebWerk::CPostEffectDrawable::AddAdditionalEffect(CMaterial * a_pEffect)
//{
//	CMaterial t;
//	t.SetMaterial(a_pEffect);
//
//	m_AdditionalEffects.push_back(t);
//}

//size_t triebWerk::CPostEffectDrawable::GetAdditionalEffectCount() const
//{
//	return m_AdditionalEffects.size();
//}
//
//triebWerk::CMaterial * triebWerk::CPostEffectDrawable::GetAdditionalEffect(unsigned int a_Index)
//{
//	if (a_Index > m_AdditionalEffects.size() - 1 || m_AdditionalEffects.size() == 0)
//	{
//		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: There is no AdditionalEffect at the given Index");
//		return nullptr;
//	}
//
//	return &m_AdditionalEffects[a_Index];
//}

void triebWerk::CPostEffectDrawable::AddMaterial(const CMaterial * a_pMaterial)
{
	CMaterial t;
	m_Materials.push_back(t);
	m_Materials[m_Materials.size() - 1].SetMaterial(a_pMaterial);
}

triebWerk::IDrawable::EDrawableType triebWerk::CPostEffectDrawable::GetType()
{
	return IDrawable::EDrawableType::PostEffect;
}

void triebWerk::CPostEffectDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{

}
