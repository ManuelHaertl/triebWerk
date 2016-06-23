#pragma once
#include <IDrawable.h>
#include <vector>
#include <CMaterial.h>

namespace triebWerk
{
	class CPostEffectDrawable : public IDrawable
	{
	public:
		unsigned int m_RenderTargetSlotToStartOff;
		CMaterial m_Effect;

	private:

	public:
		CPostEffectDrawable();
		~CPostEffectDrawable();

	public:

		IDrawable::EDrawableType GetType() final;
		
		//Probly bad design of IDrawable this function does nothing as PostEffect
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;

	};
}