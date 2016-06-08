#pragma once
#include <IDrawable.h>
#include <CMaterial.h>

namespace triebWerk
{
	class CFontDrawable : public IDrawable
	{
	private:

	public:
		CMaterial m_Material;

	private:


	public:
		CFontDrawable();
		~CFontDrawable();

		IDrawable::EDrawableType GetType() final;
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;
	};
}