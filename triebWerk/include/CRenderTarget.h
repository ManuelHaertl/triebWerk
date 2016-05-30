#pragma once

#include <CTexture2D.h>
#include <CGraphics.h>
#include <d3d11.h>

namespace triebWerk
{
	class CRenderTarget
	{

	public:
		ID3D11Texture2D* m_pTexture;
		ID3D11ShaderResourceView* m_pTextureShaderResourceView;
		ID3D11RenderTargetView* m_pRenderTargetView;

	private:
		CGraphics* m_pGraphicsHandle;
		float m_ClearColor[4];

	public:
		CRenderTarget();
		~CRenderTarget();

	public:
		void Initialize(CGraphics* a_pGraphic, unsigned int a_Width, unsigned int a_Height);
		void SetRenderTarget() const;
		void ClearRenderTarget() const;
		void SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A);
		void Clear();

	private:

	};
}