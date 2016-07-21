#pragma once
#include <IDrawable.h>
#include <CMaterial.h>
#include <list>

namespace triebWerk
{
	class CPostEffectDrawable : public IDrawable
	{
	public:
		unsigned int m_RenderTargetSlotToStartOff;
		std::vector<CMaterial*> m_Materials;

	private:


	public:
		CPostEffectDrawable();
		~CPostEffectDrawable();

	public:
		//TODO: Resize of vector will end in crashing the materials
		//Adds a material you can add as many materials as you like. The materials will be display in the order in which they were added
		//Retunrs the added Material to manipulate
		CMaterial* AddMaterial(const CMaterial* a_pMaterial);

		//Gets the Material from the posteffect pipeline
		CMaterial* GetMaterial(const int a_Slot) const;
		CMaterial* GetMaterial(const char* a_pNameOfMaterial) const;

		//Remove the effect at the given slot
		//Keep in mind that the list of effects will change and resizes
		void RemoveMaterial(const int a_SlotToRemove);
		void RemoveMaterial(const char* a_pNameOfMaterial);

		IDrawable::EDrawableType GetType() final;
		
		//Probly bad design of IDrawable this function does nothing as PostEffect
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;
		
		bool IsDrawableValid() final;

	};
}