#pragma once

#include <CTexture2D.h>
#include <CGraphics.h>
#include <d3d11.h>
#include <CRenderBatch.h>
#include <CPostEffectDrawable.h>

namespace triebWerk
{
	class CRenderTarget
	{
	public:
		CTexture2D m_Texture;
		ID3D11RenderTargetView* m_pRenderTargetView;
		CRenderBatch m_RenderBatch;
		CPostEffectDrawable* m_pPostEffect;

		//Objects needed to draw the RenderTarget
		UINT m_Stride;
		UINT m_VertexCount;
		CTransform m_PlaneTransform;
		ID3D11Buffer* m_pPlaneBuffer;

	private:
		CGraphics* m_pGraphicsHandle;
		unsigned int m_Slot;
		float m_ClearColor[4];

	public:
		CRenderTarget();
		~CRenderTarget();

	public:
		void Initialize(CGraphics* a_pGraphic, const unsigned int a_Width, const unsigned int a_Height, const unsigned int a_Slot);
		void SetRenderTarget() const;
		void ClearRenderTarget() const;
		void SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A);
		void Resize(unsigned int a_ScreenWidth, unsigned int a_ScreenHeight);
		void Clear();

	private:

	};
}