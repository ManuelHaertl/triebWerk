#include <CGraphics.h>
#include <iostream>
#include <CEngine.h>
#include <SafeDeletes.h>

triebWerk::CGraphics::CGraphics()
	: m_IsVSynced(false)
	, m_IsFullscreen(false)
	, m_pSwapChain(nullptr)
	, m_pBackBufferTexture(nullptr)
	, m_pDevice(nullptr)
	, m_pDeviceContext(nullptr)
	, m_pRenderTargetView(nullptr)
	, m_pDepthStencilBuffer(nullptr)
	, m_pDepthStencilView(nullptr)
	, m_pCullNoneDefaultRasterizerState(nullptr)
	, m_pWireframeDefaultRasterizerState(nullptr)
	, m_pDefaultRasterizerState(nullptr)
	, m_pDepthStencilState(nullptr)
	, m_pBlendState(nullptr)
	, m_pSamplerState(nullptr)
	, m_Numerator(0)
	, m_Denominator(0)
	, m_VideoCardMemory(0)
{
	//default clear color
	SetClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

triebWerk::CGraphics::~CGraphics()
{
}

bool triebWerk::CGraphics::Initialize(HWND & a_rWindowHandle, const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight, const bool a_Fullscreen, const bool a_VSync)
{
	bool result = false;

	m_IsFullscreen = a_Fullscreen;
	m_IsVSynced = a_VSync;

	m_WindowObjectHandle = a_rWindowHandle;

	SetDisplayProperties();

	//Create and initialize the device and swapchain
	result = CreateSwapChain(a_ScreenWidth, a_ScreenHeight);
	if (result == false)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Error: Could not create the swapchain or device!");
		return false;
	}

	//Create and initialize the depth buffer related objects
	result = CreateDepthBuffer(a_ScreenWidth, a_ScreenHeight);
	if (result == false)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Error: Could not create the depth buffer!");
		return false;
	}


	//If the depth buffer and the swapchain were successfully created set the rendertarget
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


	//Create and set the rasterizer state
	result = CreateDefaultRasterizerStates();
	if (result == false)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Error: Could not create rasterizer states!");
		return false;
	}
	m_pDeviceContext->RSSetState(m_pDefaultRasterizerState);


	//Create and set the blend state
	result = CreateDefaultBlendStates();
	if (result == false)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Error: Could not create the blend states!");
		return false;
	}
	this->m_pDeviceContext->OMSetBlendState(m_pBlendState, 0, 0xffffffff);

	CreateDefaultSamplerStates();
	if (result == false)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Error: Could not create the sampler states!");
		return false;
	}
	m_pDeviceContext->VSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->GSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->CSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->HSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->DSSetSamplers(0, 1, &m_pSamplerState);


	SetViewport(a_ScreenWidth, a_ScreenHeight);

	return true;
}

bool triebWerk::CGraphics::CreateSwapChain(const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight)
{
	HRESULT result = NULL;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = a_ScreenWidth;
	swapChainDesc.BufferDesc.Height = a_ScreenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = m_Numerator;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = m_Denominator;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_WindowObjectHandle;
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
		TW_CREATE_DEVICE_FLAG,
		&ENGINE_FEATURE_LEVEL,
		SUPPORTED_FEATURE_LEVEL_COUNT,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		&m_SupportedFeatureLevels,
		&m_pDeviceContext);

	if (FAILED(result))
		return false;

	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBufferTexture);
	if (FAILED(result))
		return false;

	result = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture, NULL, &m_pRenderTargetView);
	if (FAILED(result))
		return false;

	return true;
}

bool triebWerk::CGraphics::CreateDepthBuffer(const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight)
{
	HRESULT result = NULL;

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	//Set up the description of the depth buffer
	ZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
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

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
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

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	// Initialize the depthStencilViewDesc.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(result))
		return false;

	return true;
}

bool triebWerk::CGraphics::CreateDefaultRasterizerStates()
{
	HRESULT result = NULL;


	//Default triebWerk rasterizer state which will be used if no other was set
	D3D11_RASTERIZER_DESC defaultRasterizerState;
	// Setup the raster state
	ZeroMemory(&defaultRasterizerState, sizeof(D3D11_RASTERIZER_DESC));
	defaultRasterizerState.AntialiasedLineEnable = true;
	defaultRasterizerState.CullMode = D3D11_CULL_BACK;
	defaultRasterizerState.DepthBias = 0;
	defaultRasterizerState.DepthBiasClamp = 0.0f;
	defaultRasterizerState.DepthClipEnable = true;
	defaultRasterizerState.FillMode = D3D11_FILL_SOLID;
	defaultRasterizerState.FrontCounterClockwise = true;
	defaultRasterizerState.MultisampleEnable = false;
	defaultRasterizerState.ScissorEnable = false;
	defaultRasterizerState.SlopeScaledDepthBias = 0.0f;

	result = m_pDevice->CreateRasterizerState(&defaultRasterizerState, &m_pDefaultRasterizerState);
	if (FAILED(result))
		return false;

	//Default cull none rasterizer state 
	D3D11_RASTERIZER_DESC defaultCullNoneRasterizerState;
	// Setup the raster state
	ZeroMemory(&defaultCullNoneRasterizerState, sizeof(D3D11_RASTERIZER_DESC));
	defaultCullNoneRasterizerState.AntialiasedLineEnable = true;
	defaultCullNoneRasterizerState.CullMode = D3D11_CULL_NONE;
	defaultCullNoneRasterizerState.DepthBias = 0;
	defaultCullNoneRasterizerState.DepthBiasClamp = 0.0f;
	defaultCullNoneRasterizerState.DepthClipEnable = true;
	defaultCullNoneRasterizerState.FillMode = D3D11_FILL_SOLID;
	defaultCullNoneRasterizerState.FrontCounterClockwise = true;
	defaultCullNoneRasterizerState.MultisampleEnable = false;
	defaultCullNoneRasterizerState.ScissorEnable = false;
	defaultCullNoneRasterizerState.SlopeScaledDepthBias = 0.0f;

	result = m_pDevice->CreateRasterizerState(&defaultCullNoneRasterizerState, &m_pCullNoneDefaultRasterizerState);
	if (FAILED(result))
		return false;

	//Default wireframe rasterizer state 
	D3D11_RASTERIZER_DESC defaultWireframeRasterizerState;
	// Setup the raster state
	ZeroMemory(&defaultRasterizerState, sizeof(D3D11_RASTERIZER_DESC));
	defaultWireframeRasterizerState.AntialiasedLineEnable = true;
	defaultWireframeRasterizerState.CullMode = D3D11_CULL_NONE;
	defaultWireframeRasterizerState.DepthBias = 0;
	defaultWireframeRasterizerState.DepthBiasClamp = 0.0f;
	defaultWireframeRasterizerState.DepthClipEnable = true;
	defaultWireframeRasterizerState.FillMode = D3D11_FILL_WIREFRAME;
	defaultWireframeRasterizerState.FrontCounterClockwise = true;
	defaultWireframeRasterizerState.MultisampleEnable = false;
	defaultWireframeRasterizerState.ScissorEnable = false;
	defaultWireframeRasterizerState.SlopeScaledDepthBias = 0.0f;

	result = m_pDevice->CreateRasterizerState(&defaultWireframeRasterizerState, &m_pWireframeDefaultRasterizerState);
	if (FAILED(result))
		return false;

	return true;
}

bool triebWerk::CGraphics::CreateDefaultBlendStates()
{
	HRESULT result = NULL;

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
	if (FAILED(result))
		return false;

	return true;
}

bool triebWerk::CGraphics::CreateDefaultSamplerStates()
{
	HRESULT result = NULL;

	D3D11_SAMPLER_DESC samplerStateDesc;
	ZeroMemory(&samplerStateDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.MinLOD = FLT_MAX;
	samplerStateDesc.MaxLOD = FLT_MAX;
	samplerStateDesc.MipLODBias = 0.0f;
	samplerStateDesc.MaxAnisotropy = 16;
	samplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	result = m_pDevice->CreateSamplerState(&samplerStateDesc, &m_pSamplerState);
	if (FAILED(result))
		return false;
}

void triebWerk::CGraphics::SetViewport(const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Width = (float)a_ScreenWidth;
	viewport.Height = (float)a_ScreenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_pDeviceContext->RSSetViewports(1, &viewport);
}

void triebWerk::CGraphics::Shutdown()
{
	SafeDirectXRelease(&m_pSwapChain);
	SafeDirectXRelease(&m_pBackBufferTexture);
	SafeDirectXRelease(&m_pDevice);
	SafeDirectXRelease(&m_pDeviceContext);
	SafeDirectXRelease(&m_pRenderTargetView);
	SafeDirectXRelease(&m_pDepthStencilBuffer);
	SafeDirectXRelease(&m_pDepthStencilView);
	SafeDirectXRelease(&m_pCullNoneDefaultRasterizerState);
	SafeDirectXRelease(&m_pWireframeDefaultRasterizerState);
	SafeDirectXRelease(&m_pDefaultRasterizerState);
	SafeDirectXRelease(&m_pDepthStencilState);
	SafeDirectXRelease(&m_pBlendState);
	SafeDirectXRelease(&m_pSamplerState);
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

ID3D11RasterizerState* triebWerk::CGraphics::GetDefaultRasterizerState() const
{
	return m_pDefaultRasterizerState;
}

ID3D11RasterizerState * triebWerk::CGraphics::GetDefaultWireframeRasterizerState() const
{
	return m_pWireframeDefaultRasterizerState;
}

ID3D11RasterizerState * triebWerk::CGraphics::GetDefaultCullNoneRasterizerState() const
{
	return m_pCullNoneDefaultRasterizerState;
}

ID3D11BlendState * triebWerk::CGraphics::GetDefaultBlendState() const
{
	return m_pBlendState;
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

	//Resize the Rendering
	CEngine::Instance().m_pRenderer->ResizeRenderer((a.right - a.left), (a.bottom - a.top));
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

ID3D11Texture2D * triebWerk::CGraphics::CreateD3D11FontTexture(const void * a_pData, const unsigned int a_Width, const unsigned int a_Height) const
{
	HRESULT hr;

	ID3D11Texture2D* temp;

	D3D11_SUBRESOURCE_DATA textureData;
	textureData.pSysMem = a_pData;
	textureData.SysMemPitch = a_Width;
	textureData.SysMemSlicePitch = 0;

	D3D11_TEXTURE2D_DESC textureDescription = { 0 };
	textureDescription.ArraySize = 1;
	textureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDescription.CPUAccessFlags = 0;
	textureDescription.Format = DXGI_FORMAT_R8_UNORM;
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

ID3D11ShaderResourceView * triebWerk::CGraphics::CreateID3D11ShaderResourceViewFont(ID3D11Texture2D * a_Texture) const
{
	HRESULT hr;

	ID3D11ShaderResourceView* temp;

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDescription;
	memset(&shaderResourceViewDescription, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	shaderResourceViewDescription.Format = DXGI_FORMAT_R8_UNORM;
	shaderResourceViewDescription.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDescription.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDescription.Texture2D.MipLevels = 1;

	hr = this->m_pDevice->CreateShaderResourceView(a_Texture, &shaderResourceViewDescription, &temp);
	if (FAILED(hr))
		return nullptr;
	else
		return temp;
}

ID3D11Buffer * triebWerk::CGraphics::CreateVertexBuffer(const void* a_pVertexData, const size_t a_VertexCount) const
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

ID3D11Buffer * triebWerk::CGraphics::CreateIndexBuffer(const void * a_pIndexData, const size_t a_ByteWidth) const
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

ID3D11Buffer * triebWerk::CGraphics::CreateDefaultQuad(UINT* a_pStrideOut, UINT* a_pOutVertexCount) const
{
	ID3D11Buffer* pVertexBuffer;

	struct SVertices
	{
		float x, y, z;
		float u, v;
	};

	//Vertice structure for a simple quad 
	SVertices vertices[] =
	{
		{ 0.5f, 0.5f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, 0.5f, 0.0f, 0.0f, 0.0f },
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, 0.5f, 0.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5, 0.0f, 0.0f, 1.0f },
	};

	//Buffer description for a vertex buffer
	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDescription.ByteWidth = sizeof(SVertices) * 6;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//Create Buffer
	HRESULT hrError = m_pDevice->CreateBuffer(&vertexBufferDescription, NULL, &pVertexBuffer);

	if (FAILED(hrError))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warnig: Could not create vertex buffer for default quad!");
		pVertexBuffer = nullptr;
		*a_pStrideOut = 0;
		return nullptr;
	}

	//Map the actual vertex data into the vertex buffer;
	D3D11_MAPPED_SUBRESOURCE subResourceVertexBuffer;
	m_pDeviceContext->Map(pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subResourceVertexBuffer);
	memcpy(subResourceVertexBuffer.pData, vertices, sizeof(vertices));
	m_pDeviceContext->Unmap(pVertexBuffer, NULL);

	//Stride size of the vertix struct 4* xyz and 4*uv
	*a_pStrideOut = sizeof(SVertices);

	//Vertex count of a quad 
	*a_pOutVertexCount = 6;

	return pVertexBuffer;
}

triebWerk::CRenderQuad* triebWerk::CGraphics::CreateCRenderQuad() const
{

	ID3D11Buffer* pVertexBuffer;

	struct SVertices
	{
		float x, y, z;
		float u, v;
	};

	//Vertice structure for a simple quad 
	SVertices vertices[] =
	{
		{ 0.5f, 0.5f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, 0.5f, 0.0f, 0.0f, 0.0f },
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, 0.5f, 0.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5, 0.0f, 0.0f, 1.0f },
	};

	//Buffer description for a vertex buffer
	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDescription.ByteWidth = sizeof(SVertices) * 6;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//Create Buffer
	HRESULT hrError = m_pDevice->CreateBuffer(&vertexBufferDescription, NULL, &pVertexBuffer);

	if (FAILED(hrError))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warnig: Could not create vertex buffer for default quad!");
		pVertexBuffer = nullptr;
		return nullptr;
	}

	//Map the actual vertex data into the vertex buffer;
	D3D11_MAPPED_SUBRESOURCE subResourceVertexBuffer;
	m_pDeviceContext->Map(pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subResourceVertexBuffer);
	memcpy(subResourceVertexBuffer.pData, vertices, sizeof(vertices));
	m_pDeviceContext->Unmap(pVertexBuffer, NULL);


	//Stride size of the vertix struct 4* xyz and 4*uv and Vertex count of a quad 
	CRenderQuad* pQuad = new CRenderQuad(6, sizeof(SVertices), pVertexBuffer);

	return pQuad;
}

ID3D11RasterizerState * triebWerk::CGraphics::CreateRasterizerState(const D3D11_CULL_MODE a_CullMode, const D3D11_FILL_MODE a_FillMode) const
{
	ID3D11RasterizerState* rasterState = nullptr;
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	// Setup the raster state
	rasterDesc.AntialiasedLineEnable = true;
	rasterDesc.CullMode = a_CullMode;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = a_FillMode;
	rasterDesc.FrontCounterClockwise = true;
	rasterDesc.MultisampleEnable = true;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	HRESULT hResult = m_pDevice->CreateRasterizerState(&rasterDesc, &rasterState);
	if (FAILED(hResult))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Could not create ID3D11RasterizerState!");
		return nullptr;
	}

	return rasterState;
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

	D3D11_TEXTURE2D_DESC backBufferTextureDesc;
	m_pBackBufferTexture->GetDesc(&backBufferTextureDesc);

	CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT,static_cast<UINT> (backBufferTextureDesc.Width),static_cast<UINT> (backBufferTextureDesc.Height),1,1,D3D11_BIND_DEPTH_STENCIL);

	hr = m_pDevice->CreateTexture2D(&depthStencilDesc,nullptr,&m_pDepthStencilBuffer);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer,&depthStencilViewDesc,&m_pDepthStencilView);

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Height = static_cast<float>(backBufferTextureDesc.Height);
	viewport.Width = static_cast<float>(backBufferTextureDesc.Width);
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

void triebWerk::CGraphics::RemapTextureBuffer(const void * a_pData, const size_t a_DataSize, ID3D11Texture2D * a_pTextureToRemap) const
{
    m_pDeviceContext->UpdateSubresource(a_pTextureToRemap, 0, nullptr, a_pData, a_DataSize, 0);
}
