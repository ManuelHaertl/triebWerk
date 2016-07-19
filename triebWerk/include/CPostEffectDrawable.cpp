#include "CPostEffectDrawable.h"
#include <CStringHasher.h>

triebWerk::CPostEffectDrawable::CPostEffectDrawable()
{
}

triebWerk::CPostEffectDrawable::~CPostEffectDrawable()
{
	for (size_t i = 0; i < m_Materials.size(); i++)
	{
		delete m_Materials[i];
	}
}

triebWerk::CMaterial* triebWerk::CPostEffectDrawable::AddMaterial(const CMaterial * a_pMaterial)
{
	if (a_pMaterial == nullptr)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: You can't add a empty material as PostEffect");
		return nullptr;
	}

	CMaterial* material = new CMaterial();
	material->SetMaterial(a_pMaterial);

	m_Materials.push_back(material);

	return material;
}

triebWerk::CMaterial* triebWerk::CPostEffectDrawable::GetMaterial(const int a_Slot) const
{
	if (static_cast<size_t>(a_Slot) + 1 > m_Materials.size())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "No Material at this Slot in the CPostEffectDrawable");
		return nullptr;
	}

	return m_Materials[a_Slot];
}

triebWerk::CMaterial * triebWerk::CPostEffectDrawable::GetMaterial(const char * a_pNameOfMaterial) const
{
	for (size_t i = 0; i < m_Materials.size(); i++)
	{
		if (m_Materials[i]->m_ID.GetHash() == StringHasher(a_pNameOfMaterial))
		{
			return m_Materials[i];
		}
	}

	DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: There is no Material in the posteffect with the name: %s", a_pNameOfMaterial);
	return nullptr;

}

void triebWerk::CPostEffectDrawable::RemoveMaterial(const int a_SlotToRemove)
{
	delete m_Materials[a_SlotToRemove];
	m_Materials.erase(m_Materials.begin() + a_SlotToRemove);
}

void triebWerk::CPostEffectDrawable::RemoveMaterial(const char * a_pNameOfMaterial)
{
	for (size_t i = 0; i < m_Materials.size(); i++)
	{
		if (m_Materials[i]->m_ID.GetHash() == StringHasher(a_pNameOfMaterial))
		{
			delete m_Materials[i];
			m_Materials.erase(m_Materials.begin() + i);
		}
	}
}

triebWerk::IDrawable::EDrawableType triebWerk::CPostEffectDrawable::GetType()
{
	return IDrawable::EDrawableType::PostEffect;
}

void triebWerk::CPostEffectDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{
}

bool triebWerk::CPostEffectDrawable::IsDrawableValid()
{
	if (m_Materials.size() > 0 && m_RenderTargetSlotToStartOff >= 0)
		return true;
	else
		return false;
}
