#pragma once
#include <IDrawable.h>
#include <CMaterial.h>
#include <CElementContainer.h>

namespace triebWerk
{
	class CPostEffectDrawable : public IDrawable
	{
	public:
		unsigned int m_RenderTargetSlotToStartOff;
		std::vector<CMaterial> m_Materials;

	private:

	public:
		CPostEffectDrawable();
		~CPostEffectDrawable();

	public:
		//TODO: Resize of vector will end in crashing the materials
		//Adds a material you can add as many materials as you like. The materials will be display in the order in which they were added
		void AddMaterial(const CMaterial* a_pMaterial);

		IDrawable::EDrawableType GetType() final;
		
		//Probly bad design of IDrawable this function does nothing as PostEffect
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;

	};
}