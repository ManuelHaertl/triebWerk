#pragma once
#include <IDrawable.h>
#include <CMaterial.h>

namespace triebWerk
{
	class CUIDrawable : public IDrawable
	{
	public:
		unsigned int m_RenderTargetSlotToStartOff;
		DirectX::XMMATRIX m_Transformation;

		ID3D11Buffer* m_pVertexBuffer;
		UINT m_Stride;
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;
		UINT m_VertexCount;

	public:
		CMaterial m_Material;

	public:
		CUIDrawable(CGraphics* a_pGraphicsHandle);
		~CUIDrawable();

	public:
		IDrawable::EDrawableType GetType() final;
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;

		//Return if this is a valid drawable to render properly
		bool IsDrawableValid() final;

	};
}