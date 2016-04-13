#include <CGraphics.h>

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
	m_pSwapChain(nullptr)
{
	m_ClearColor = DirectX::XMVectorSet(1, 1, 1, 1);
}

triebWerk::CGraphics::~CGraphics()
{
}

bool triebWerk::CGraphics::Initialize(HWND & a_rWindowHandle, const unsigned int a_ScreenWidth, const unsigned int a_ScreenHeight, const bool a_Fullscreen, const bool a_VSync)
{
	SetDisplayProperties(a_ScreenHeight, a_ScreenWidth);

	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D11Texture2D* pBackBuffer;
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
		return false;

	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(result))
		return false;

	//Create render target view 
	result = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	if (FAILED(result))
		return false;

	pBackBuffer->Release();
	pBackBuffer = nullptr;

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
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	result = m_pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState);
	if (FAILED(result))
		return false;

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
	
	//Debug function: loading simple shader
	InitShaders();

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
}	

void triebWerk::CGraphics::ClearRenderTarget()
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_ClearColor.m128_f32);

	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void triebWerk::CGraphics::Present()
{
	if (m_IsVSynced)
		m_pSwapChain->Present(1, 0);
	else
		m_pSwapChain->Present(0, 0);
}

void triebWerk::CGraphics::SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A)
{
	m_ClearColor.m128_f32[0] = a_R;
	m_ClearColor.m128_f32[1] = a_G;
	m_ClearColor.m128_f32[2] = a_B;
	m_ClearColor.m128_f32[3] = a_A;

}

void triebWerk::CGraphics::SetClearColor(DirectX::XMVECTOR a_Color)
{
	m_ClearColor = a_Color;
}

ID3D11Device * triebWerk::CGraphics::GetDevice()
{
	return m_pDevice;
}

ID3D11DeviceContext * triebWerk::CGraphics::GetDeviceContext()
{
	return m_pDeviceContext;
}

unsigned int triebWerk::CGraphics::GetVideoCardMemory()
{
	return m_VideoCardMemory;
}

void triebWerk::CGraphics::InitShaders()
{
	ID3D10Blob* vertexShader;
	ID3D11VertexShader* vertex;

	HRESULT error;
	error = D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "VShader", "vs_4_0", D3DCOMPILE_DEBUG, 0, &vertexShader, 0);

	error = this->m_pDevice->CreateVertexShader(vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), NULL, &vertex);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	m_pDevice->CreateInputLayout(ied, 2, vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), &m_pInputLayout);
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);

	ID3D10Blob* pixelShader;
	ID3D11PixelShader* pixel;

	error = D3DCompileFromFile(L"PixelShader.hlsl", 0, 0, "PShader", "ps_4_0", D3DCOMPILE_DEBUG, 0, &pixelShader, 0);

	error = this->m_pDevice->CreatePixelShader(pixelShader->GetBufferPointer(), pixelShader->GetBufferSize(), NULL, &pixel);

	m_pDeviceContext->VSSetShader(vertex, 0, 0);
	m_pDeviceContext->PSSetShader(pixel, 0, 0);
}

void triebWerk::CGraphics::UpdateSwapchainConfiguration()
{
	HRESULT result;
	//TODO: elaborate if this is necessary
	//result = m_pSwapChain->SetFullscreenState(a_Fullscreen, NULL);
	
	m_pRenderTargetView->Release();
	result = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
	
	ID3D11Buffer* pBackBuffer;
	
	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	
	//Create render target view 
	result = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);

	pBackBuffer->Release();
	pBackBuffer = nullptr;
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

void triebWerk::CGraphics::SetDisplayProperties(const unsigned int a_ScreenHeight, const unsigned int a_ScreenWidth)
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
