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

triebWerk::CMaterial* triebWerk::CPostEffectDrawable::AddMaterial(const CMaterial * a_pMaterial)
{
	if (a_pMaterial == nullptr)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: You can't add a empty material as PostEffect");
		return nullptr;
	}

	CMaterial t;
	m_Materials.push_back(t);
	m_Materials[m_Materials.size() - 1].SetMaterial(a_pMaterial);

	return const_cast<CMaterial*>(&m_Materials[m_Materials.size() - 1]);
}

triebWerk::CMaterial* triebWerk::CPostEffectDrawable::GetMaterial(const int a_Slot) const
{
	if (a_Slot + 1 > m_Materials.size())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "No Material at this Slot in the CPostEffectDrawable");
		return nullptr;
	}

	return const_cast<CMaterial*>(&m_Materials[a_Slot]);
}

triebWerk::IDrawable::EDrawableType triebWerk::CPostEffectDrawable::GetType()
{
	return IDrawable::EDrawableType::PostEffect;
}

void triebWerk::CPostEffectDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{

}
