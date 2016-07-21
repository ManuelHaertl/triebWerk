#pragma once
#include <IDrawable.h>
#include <CGraphics.h>
#include <CMaterial.h>
#include <CText.h>

namespace triebWerk
{

	class CFontDrawable : public IDrawable
	{
	public:

		DirectX::XMMATRIX m_Transformation;

		ID3D11Buffer* m_pVertexBuffer;
		UINT m_Stride;
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;
		UINT m_VertexCount;

		CText* m_pText;
		CMaterial m_Material;

	public:
		CFontDrawable(CGraphics* a_pGraphicsHandle);
		~CFontDrawable();

		IDrawable::EDrawableType GetType() final;
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;

		//Return if this is a valid drawable to render properly
		bool IsDrawableValid() final;
	};
}