#pragma once
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <cfloat>
#include <CMesh.h>
#include <CDebugLogfile.h>
#include <CRenderQuad.h>

//#ifdef _DEBUG
//#define TW_CREATE_DEVICE_FLAG D3D11_CREATE_DEVICE_DEBUG
//#else
//#define TW_CREATE_DEVICE_FLAG 0
//#endif

#define TW_CREATE_DEVICE_FLAG 0

namespace triebWerk
{
	class CGraphics
	{
	public:
		const D3D_FEATURE_LEVEL ENGINE_FEATURE_LEVEL = D3D_FEATURE_LEVEL_11_0;
		const UINT SUPPORTED_FEATURE_LEVEL_COUNT = 1;

	private:
		HWND m_WindowObjectHandle;
		bool m_IsVSynced;
		bool m_IsFullscreen;

		D3D_FEATURE_LEVEL m_SupportedFeatureLevels;
		IDXGISwapChain* m_pSwapChain;
		ID3D11Texture2D* m_pBackBufferTexture;

		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;

		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11Texture2D* m_pDepthStencilBuffer;
		ID3D11DepthStencilView* m_pDepthStencilView;

		ID3D11RasterizerState* m_pCullNoneDefaultRasterizerState;
		ID3D11RasterizerState* m_pWireframeDefaultRasterizerState;
		ID3D11RasterizerState* m_pDefaultRasterizerState;

		ID3D11DepthStencilState* m_pDepthStencilState;

		ID3D11BlendState* m_pBlendState;

		ID3D11SamplerState* m_pSamplerState;

		float m_ClearColor[4];

		//Video card informations
		unsigned int m_Numerator;
		unsigned int m_Denominator;
		unsigned int m_VideoCardMemory;
		std::wstring m_VideoCardDescription;

	public:
		static int SizeOfFormatElement(DXGI_FORMAT a_Format);

	public:
		CGraphics();
		~CGraphics();

	public:
		//Initialize the graphics d3d11 device and set all graphics related options
		bool Initialize(HWND &a_rWindowHandle, const unsigned int a_ScreenHeight, const unsigned int a_ScreenWidth, const bool a_Fullscreen, const bool a_VSync);
		
		void Shutdown();
		
		//Set the backbuffer to render into it
		void SetBackBufferRenderTarget();
		
		//Clear the backbuffer
		void ClearRenderTarget();

		//Swap the buffers and display the drawen image on the screen
		void Present();

		ID3D11RasterizerState* GetDefaultRasterizerState() const;
		ID3D11RasterizerState* GetDefaultWireframeRasterizerState() const;
		ID3D11RasterizerState* GetDefaultCullNoneRasterizerState() const;
		ID3D11BlendState* GetDefaultBlendState() const;

		//Set the clearcolor of the rendertarget
		void SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A);

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		ID3D11DepthStencilView* GetDepthStencilView();

		//Get the amount of videomemory from the system
		unsigned int GetVideoCardMemory();

		//Updates all devices and the swapchain with the current client rect
		void UpdateSwapchainConfiguration();
		
		//Factory functions
		ID3D11Texture2D* CreateD3D11Texture2D(const void* a_pData, const unsigned int a_Width, const unsigned int a_Height) const;
		ID3D11Texture2D* CreateD3D11FontTexture(const void* a_pData, const unsigned int a_Width, const unsigned int a_Height) const;
		ID3D11ShaderResourceView* CreateID3D11ShaderResourceView(ID3D11Texture2D* a_Texture) const;
		ID3D11ShaderResourceView* CreateID3D11ShaderResourceViewFont(ID3D11Texture2D* a_Texture) const;
		ID3D11Buffer* CreateVertexBuffer(const void* a_pVertexData, const size_t a_VertexCount) const;
		ID3D11Buffer* CreateIndexBuffer(const void* a_pIndexData, const size_t a_ByteWidth) const;
		ID3D11Buffer* CreateDefaultQuad(UINT* a_pOutStride, UINT* a_pOutVertexCount) const;
		CRenderQuad* CreateCRenderQuad() const;
		ID3D11RasterizerState* CreateRasterizerState(const D3D11_CULL_MODE a_CullMode, const D3D11_FILL_MODE a_FillMode) const;

		void RemapTextureBuffer(const void * a_pData, const size_t a_DataSize, ID3D11Texture2D * a_pTextureToRemap) const;

	private:
		bool CreateSwapChain(const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight);
		bool CreateDepthBuffer(const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight);
		bool CreateDefaultRasterizerStates();
		bool CreateDefaultBlendStates();
		bool CreateDefaultSamplerStates();
		
		void SetViewport(const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight);

		void SetDisplayProperties();
		void ReleaseBackBuffer();
		void ConfigureBackBuffer();



	};
} 
