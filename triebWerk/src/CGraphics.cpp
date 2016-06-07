#include <CGraphics.h>
#include <iostream>
#include <CEngine.h>
#include <CMeshDrawable.h>

triebWerk::CGraphics::CGraphics() :
	m_IsFullscreen(false),
	m_IsVSynced(false),
	m_pDepthStencilBuffer(nullptr),
	m_pDepthStencilState(nullptr),
	m_pDevice(nullptr),
	m_pDepthStencilView(nullptr),
	m_pDeviceContext(nullptr),
	m_pInputLayout(nullptr),
	m_pRasterState(nullptr),
	m_pRenderTargetView(nullptr),
	m_pSwapChain(nullptr),
	m_pBlendState(nullptr)
{
	//default clear color
	SetClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

triebWerk::CGraphics::~CGraphics()
{
}

bool triebWerk::CGraphics::Initialize(HWND & a_rWindowHandle, const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight, const bool a_Fullscreen, const bool a_VSync)
{
	SetDisplayProperties();

	//Note: This value will not be use because the msdn documentation says that you shouldnt initialize the swapchain in fullscreen
	//instead of use the resize buffer function
	m_IsFullscreen = a_Fullscreen;
	m_IsVSynced = a_VSync;

	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;

	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = a_ScreenWidth;
	swapChainDesc.BufferDesc.Height = a_ScreenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = m_Numerator;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = m_Denominator;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = a_rWindowHandle;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&ENGINE_FEATURE_LEVEL,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pDeviceContext);
	
	if (FAILED(result))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Error: Swapchain coud not be created!");
		return false;
	}


	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBufferTexture);
	if (FAILED(result))
		return false;

	//Create render target view 
	result = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture, NULL, &m_pRenderTargetView);
	if (FAILED(result))
		return false;

	//Set up the description of the depth buffer
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = a_ScreenWidth;
	depthBufferDesc.Height = a_ScreenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = m_pDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_pDepthStencilBuffer);
	if (FAILED(result))
		return false;

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
	if (FAILED(result))
		return false;

	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);

	// Initialize the depthStencilViewDesc.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(result))
		return false;

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	// Setup the raster state
	rasterDesc.AntialiasedLineEnable = true;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = true;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	result = m_pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState);
	if (FAILED(result))
		return false;

	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));
	blendStateDescription.AlphaToCoverageEnable = false;
	blendStateDescription.IndependentBlendEnable = false;
	blendStateDescription.RenderTarget[0].BlendEnable = true;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	result = this->m_pDevice->CreateBlendState(&blendStateDescription, &m_pBlendState);
	this->m_pDeviceContext->OMSetBlendState(m_pBlendState, 0, 0xffffffff);

	m_pDeviceContext->RSSetState(m_pRasterState);

	//TODO: Move this to the camera
	// Setup the viewport for rendering.
	viewport.Width = (float)a_ScreenWidth;
	viewport.Height = (float)a_ScreenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_pDeviceContext->RSSetViewports(1, &viewport);

	return true;
}

void triebWerk::CGraphics::Shutdown()
{
	if (m_pDepthStencilBuffer != nullptr)
		m_pDepthStencilBuffer->Release();
	
	if (m_pDepthStencilState != nullptr)
		m_pDepthStencilState->Release();
	
	if (m_pDepthStencilView != nullptr)
		m_pDepthStencilView->Release();
	
	if (m_pDevice != nullptr)
		m_pDevice->Release();
	
	if (m_pDeviceContext != nullptr)
		m_pDeviceContext->Release();
	
	if (m_pRasterState != nullptr)
		m_pRasterState->Release();

	if (m_pRenderTargetView != nullptr)
		m_pRenderTargetView->Release();

	if (m_pSwapChain != nullptr)
		m_pSwapChain->Release();

	if (m_pBackBufferTexture != nullptr)
		m_pBackBufferTexture->Release();

	if (m_pInputLayout != nullptr)
		m_pInputLayout->Release();
}	

void triebWerk::CGraphics::SetBackBufferRenderTarget()
{
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
}

void triebWerk::CGraphics::ClearRenderTarget()
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_ClearColor);

	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void triebWerk::CGraphics::Present()
{
	m_pSwapChain->Present(m_IsVSynced, 0);
}

void triebWerk::CGraphics::SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A)
{
	m_ClearColor[0] = a_R;
	m_ClearColor[1] = a_G;
	m_ClearColor[2] = a_B;
	m_ClearColor[3] = a_A;
}

ID3D11Device * triebWerk::CGraphics::GetDevice()
{
	return m_pDevice;
}

ID3D11DeviceContext * triebWerk::CGraphics::GetDeviceContext()
{
	return m_pDeviceContext;
}

ID3D11DepthStencilView * triebWerk::CGraphics::GetDepthStencilView()
{
	return m_pDepthStencilView;
}

unsigned int triebWerk::CGraphics::GetVideoCardMemory()
{
	return m_VideoCardMemory;
}

void triebWerk::CGraphics::UpdateSwapchainConfiguration()
{
	HRESULT hr;
	
	ReleaseBackBuffer();

	hr = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

	if (FAILED(hr))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Critical Error: Graphics failed to resize swapchain buffers!");
	}

	ConfigureBackBuffer();

	RECT a;
	GetClientRect(CEngine::Instance().m_pWindow->GetWindowHandle(), &a);

	CEngine::Instance().m_pRenderer->GetCurrentActiveCamera()->SetAspect((float)(a.right - a.left) / (float)(a.bottom - a.top));
}

ID3D11Texture2D * triebWerk::CGraphics::CreateD3D11Texture2D(const void * a_pData, const unsigned int a_Width, const unsigned int a_Height) const
{
	HRESULT hr;

	ID3D11Texture2D* temp;

	D3D11_SUBRESOURCE_DATA textureData;
	textureData.pSysMem = a_pData;
	textureData.SysMemPitch = 4 * a_Width;
	textureData.SysMemSlicePitch = 0;

	D3D11_TEXTURE2D_DESC textureDescription = { 0 };
	textureDescription.ArraySize = 1;
	textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDescription.CPUAccessFlags = 0;
	textureDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDescription.MipLevels = 1;
	textureDescription.MiscFlags = 0;
	textureDescription.SampleDesc.Count = 1;
	textureDescription.SampleDesc.Quality = 0;
	textureDescription.Usage = D3D11_USAGE_DEFAULT;
	textureDescription.Height = a_Height;
	textureDescription.Width = a_Width;

	hr = this->m_pDevice->CreateTexture2D(&textureDescription, &textureData, &temp);
	if (FAILED(hr))
		return nullptr;
	else
		return temp;
}

ID3D11ShaderResourceView * triebWerk::CGraphics::CreateID3D11ShaderResourceView(ID3D11Texture2D * a_Texture) const
{
	HRESULT hr;

	ID3D11ShaderResourceView* temp;

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDescription;
	memset(&shaderResourceViewDescription, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	shaderResourceViewDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDescription.Texture2D.MipLevels = 1;

	hr = this->m_pDevice->CreateShaderResourceView(a_Texture, &shaderResourceViewDescription, &temp);
	if (FAILED(hr))
		return nullptr;
	else
		return temp;
}

ID3D11Buffer * triebWerk::CGraphics::CreateVertexBuffer(void* a_pVertexData, size_t a_VertexCount)
{
	ID3D11Buffer* pVertexBuffer;

	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDescription.ByteWidth = static_cast<UINT>(sizeof(CMesh::SVertex) * a_VertexCount);
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData;
	ZeroMemory(&subresourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	subresourceData.pSysMem = a_pVertexData;

	HRESULT hr = m_pDevice->CreateBuffer(&vertexBufferDescription, &subresourceData, &pVertexBuffer);

	if (FAILED(hr))
		return nullptr;

	return pVertexBuffer;
}

ID3D11Buffer * triebWerk::CGraphics::CreateIndexBuffer(void * a_pIndexData, size_t a_ByteWidth)
{
	ID3D11Buffer* pIndexBuffer;

	D3D11_BUFFER_DESC indexBufferDescription;
	ZeroMemory(&indexBufferDescription, sizeof(D3D11_BUFFER_DESC));
	indexBufferDescription.ByteWidth = static_cast<UINT>(a_ByteWidth);
	indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDescription.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData;
	ZeroMemory(&subresourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	subresourceData.pSysMem = a_pIndexData;

	HRESULT hr = m_pDevice->CreateBuffer(&indexBufferDescription, &subresourceData, &pIndexBuffer);

	if (FAILED(hr))
		return nullptr;

	return pIndexBuffer;
}

void triebWerk::CGraphics::SetDisplayProperties()
{
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	HRESULT result;
	unsigned int numModes;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

	result = factory->EnumAdapters(0, &adapter);

	result = adapter->EnumOutputs(0, &adapterOutput);

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);

	displayModeList = new DXGI_MODE_DESC[numModes];

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);

	//MSDN: Adapter with the output on which the desktop primary is displayed. This adapter corresponds with an index of zero
	m_Numerator = displayModeList[0].RefreshRate.Numerator;
	m_Denominator = displayModeList[0].RefreshRate.Denominator;

	result = adapter->GetDesc(&adapterDesc);

	m_VideoCardMemory = static_cast<unsigned int>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
	m_VideoCardDescription = adapterDesc.Description;

    delete displayModeList;
}

void triebWerk::CGraphics::ReleaseBackBuffer()
{
	m_pRenderTargetView->Release();

	m_pBackBufferTexture->Release();

	m_pDepthStencilView->Release();
	m_pDepthStencilBuffer->Release();

	m_pDeviceContext->Flush();
}

void triebWerk::CGraphics::ConfigureBackBuffer()
{
	HRESULT hr = S_OK;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pBackBufferTexture);

	hr = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture, nullptr, &m_pRenderTargetView);

	m_pBackBufferTexture->GetDesc(&m_bbDesc);

	CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT,static_cast<UINT> (m_bbDesc.Width),static_cast<UINT> (m_bbDesc.Height),1,1,D3D11_BIND_DEPTH_STENCIL);

	hr = m_pDevice->CreateTexture2D(&depthStencilDesc,nullptr,&m_pDepthStencilBuffer);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer,&depthStencilViewDesc,&m_pDepthStencilView);

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Height = (float)m_bbDesc.Height;
	viewport.Width = (float)m_bbDesc.Width;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	m_pDeviceContext->RSSetViewports(1,&viewport);
}

int triebWerk::CGraphics::SizeOfFormatElement(DXGI_FORMAT a_Format)
{
	switch (a_Format)
	{
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return 16;

	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_FLOAT:
	case DXGI_FORMAT_R32G32B32_UINT:
	case DXGI_FORMAT_R32G32B32_SINT:
		return 12;

	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
	case DXGI_FORMAT_R16G16B16A16_UNORM:
	case DXGI_FORMAT_R16G16B16A16_UINT:
	case DXGI_FORMAT_R16G16B16A16_SNORM:
	case DXGI_FORMAT_R16G16B16A16_SINT:
	case DXGI_FORMAT_R32G32_TYPELESS:
	case DXGI_FORMAT_R32G32_FLOAT:
	case DXGI_FORMAT_R32G32_UINT:
	case DXGI_FORMAT_R32G32_SINT:
	case DXGI_FORMAT_R32G8X24_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		return 8;

	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
	case DXGI_FORMAT_R10G10B10A2_UNORM:
	case DXGI_FORMAT_R10G10B10A2_UINT:
	case DXGI_FORMAT_R11G11B10_FLOAT:
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	case DXGI_FORMAT_R16G16_TYPELESS:
	case DXGI_FORMAT_R16G16_FLOAT:
	case DXGI_FORMAT_R16G16_UNORM:
	case DXGI_FORMAT_R16G16_UINT:
	case DXGI_FORMAT_R16G16_SNORM:
	case DXGI_FORMAT_R16G16_SINT:
	case DXGI_FORMAT_R32_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT:
	case DXGI_FORMAT_R32_FLOAT:
	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_SINT:
	case DXGI_FORMAT_R24G8_TYPELESS:
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		return 4;

	case DXGI_FORMAT_R8G8_TYPELESS:
	case DXGI_FORMAT_R8G8_UNORM:
	case DXGI_FORMAT_R8G8_UINT:
	case DXGI_FORMAT_R8G8_SNORM:
	case DXGI_FORMAT_R8G8_SINT:
	case DXGI_FORMAT_R16_TYPELESS:
	case DXGI_FORMAT_R16_FLOAT:
	case DXGI_FORMAT_D16_UNORM:
	case DXGI_FORMAT_R16_UNORM:
	case DXGI_FORMAT_R16_UINT:
	case DXGI_FORMAT_R16_SNORM:
	case DXGI_FORMAT_R16_SINT:
	case DXGI_FORMAT_B5G6R5_UNORM:
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		return 2;

	case DXGI_FORMAT_R8_TYPELESS:
	case DXGI_FORMAT_R8_UNORM:
	case DXGI_FORMAT_R8_UINT:
	case DXGI_FORMAT_R8_SNORM:
	case DXGI_FORMAT_R8_SINT:
	case DXGI_FORMAT_A8_UNORM:
		return 1;

		// Compressed format; http://msdn2.microsoft.com/en-us/library/bb694531(VS.85).aspx
	case DXGI_FORMAT_BC2_TYPELESS:
	case DXGI_FORMAT_BC2_UNORM:
	case DXGI_FORMAT_BC2_UNORM_SRGB:
	case DXGI_FORMAT_BC3_TYPELESS:
	case DXGI_FORMAT_BC3_UNORM:
	case DXGI_FORMAT_BC3_UNORM_SRGB:
	case DXGI_FORMAT_BC5_TYPELESS:
	case DXGI_FORMAT_BC5_UNORM:
	case DXGI_FORMAT_BC5_SNORM:
		return 16;

		// Compressed format; http://msdn2.microsoft.com/en-us/library/bb694531(VS.85).aspx
	case DXGI_FORMAT_R1_UNORM:
	case DXGI_FORMAT_BC1_TYPELESS:
	case DXGI_FORMAT_BC1_UNORM:
	case DXGI_FORMAT_BC1_UNORM_SRGB:
	case DXGI_FORMAT_BC4_TYPELESS:
	case DXGI_FORMAT_BC4_UNORM:
	case DXGI_FORMAT_BC4_SNORM:
		return 8;

		// Compressed format; http://msdn2.microsoft.com/en-us/library/bb694531(VS.85).aspx
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		return 4;

		// These are compressed, but bit-size information is unclear.
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		return 4;

	case DXGI_FORMAT_UNKNOWN:
	default:
		return 0;
	}
}