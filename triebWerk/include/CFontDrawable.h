#pragma once
#include <IDrawable.h>
#include <CGraphics.h>
#include <CMaterial.h>

namespace triebWerk
{
	class CText;

	class CFontDrawable : public IDrawable
	{
	public:
		CMaterial m_Material;
		DirectX::XMMATRIX m_Transformation;
		ID3D11Buffer* m_pVertexBuffer;
		UINT m_Stride;
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;
		UINT m_VertexCount;

		CText* m_pText;

	private:
		unsigned int m_ScaleOfTextureX;
		unsigned int m_ScaleOfTextureY;

	public:
		CFontDrawable(CGraphics* a_pGraphicsHandle);
		~CFontDrawable();

		void SetFont(CTexture2D* a_pFontTexture);

		IDrawable::EDrawableType GetType() final;
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;

		//Return if this is a valid drawable to render properly
		static bool IsValidDrawable(const CFontDrawable* a_pDrawableToTest);
	};
}