#pragma once
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <cfloat>
#include <CMesh.h>
#include <CDebugLogfile.h>

namespace triebWerk
{
	class CGraphics
	{
	public:
		const D3D_FEATURE_LEVEL ENGINE_FEATURE_LEVEL = D3D_FEATURE_LEVEL_11_0;

	private:
		bool m_IsVSynced;
		bool m_IsFullscreen;

		unsigned int m_Numerator;
		unsigned int m_Denominator;

		IDXGISwapChain* m_pSwapChain;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11Texture2D* m_pDepthStencilBuffer;
		ID3D11DepthStencilState* m_pDepthStencilState;
		ID3D11DepthStencilView* m_pDepthStencilView;
		ID3D11RasterizerState* m_pRasterState;
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Texture2D* m_pBackBufferTexture;
		D3D11_TEXTURE2D_DESC m_bbDesc;
		ID3D11BlendState* m_pBlendState;
	
		//Debug
		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;

		float m_ClearColor[4];

		unsigned int m_VideoCardMemory;
		std::wstring m_VideoCardDescription;
	public:
		CGraphics();
		~CGraphics();

	public:
		//Get the actual byte size of a DXGI_FORMAT
		static int SizeOfFormatElement(DXGI_FORMAT a_Format);

	public:
		//Initialize the graphics d3d11 device and set all graphics related options
		bool Initialize(HWND &a_rWindowHandle, const unsigned int a_ScreenHeight, const unsigned int a_ScreenWidth, const bool a_Fullscreen, const bool a_VSync);
		void Shutdown();
		
		void ClearRenderTarget();
		void Present();

		//Set the clearcolor of the rendertarget
		void SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A);

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		//Get the amount of videomemory from the system
		unsigned int GetVideoCardMemory();

		//Updates all devices and the swapchain with the current client rect
		void UpdateSwapchainConfiguration();
		
		//Factory functions
		ID3D11Texture2D* CreateD3D11Texture2D(const void* a_pData, const unsigned int a_Width, const unsigned int a_Height) const;
		ID3D11ShaderResourceView* CreateID3D11ShaderResourceView(ID3D11Texture2D* a_Texture) const;
		ID3D11Buffer* CreateVertexBuffer(void* a_pVertexData, size_t a_VertexCount);
		ID3D11Buffer* CreateIndexBuffer(void* a_pIndexData, size_t a_ByteWidth);

	private:
		void SetDisplayProperties();
		void ReleaseBackBuffer();
		void ConfigureBackBuffer();
	};
}
