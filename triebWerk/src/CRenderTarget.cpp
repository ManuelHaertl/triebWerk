#include <CRenderTarget.h>


triebWerk::CRenderTarget::CRenderTarget() :
	m_pGraphicsHandle(nullptr),
	m_pQuad(nullptr),
	m_pPostEffect(nullptr),
	m_Slot(0)
{
	m_ClearColor[0] = 1.0f;
	m_ClearColor[1] = 0.4f;
	m_ClearColor[2] = 0.7f;
	m_ClearColor[3] = 1.0f;
}

triebWerk::CRenderTarget::~CRenderTarget()
{
	delete m_pQuad;
	Clear();
}

void triebWerk::CRenderTarget::Initialize(CGraphics * a_pGraphic, const unsigned int a_Width, const unsigned int a_Height, const unsigned int a_Slot, bool a_Batching)
{
	m_Slot = a_Slot;
	m_pGraphicsHandle = a_pGraphic;

	//Create the a batch of data for the rendering
	if(a_Batching)
		m_RenderBatch.Create(a_pGraphic);


	for (size_t i = 0; i < 2; i++)
	{
		//Descriptor
		D3D11_TEXTURE2D_DESC textureDesc;
		HRESULT result;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.Width = a_Width;
		textureDesc.Height = a_Height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		ID3D11Texture2D* pTexture = nullptr;

		//Create a "normal rgba texture" to render into
		result = a_pGraphic->GetDevice()->CreateTexture2D(&textureDesc, NULL, &pTexture);

		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		ID3D11ShaderResourceView* pShaderResource = nullptr;

		//Create the RenderTargetView 
		result = a_pGraphic->GetDevice()->CreateRenderTargetView(pTexture, &renderTargetViewDesc, &m_pRenderTargetView[i]);

		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		// Create the shader resource view.
		result = a_pGraphic->GetDevice()->CreateShaderResourceView(pTexture, &shaderResourceViewDesc, &pShaderResource);

		m_Texture[i].SetTexture(a_Width, a_Height, pTexture, pShaderResource);
	}

	//Descriptor
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = a_Width;
	textureDesc.Height = a_Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	ID3D11Texture2D* pTexture = nullptr;

	//Create a "normal rgba texture" to render into
	result = a_pGraphic->GetDevice()->CreateTexture2D(&textureDesc, NULL, &pTexture);

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	ID3D11ShaderResourceView* pShaderResource = nullptr;

	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view.
	result = a_pGraphic->GetDevice()->CreateShaderResourceView(pTexture, &shaderResourceViewDesc, &pShaderResource);

	m_DefaultSceneTexture.SetTexture(a_Width, a_Height, pTexture, pShaderResource);

	//Create a screen aligent quad for the render target texture drawing
	//m_pPlaneBuffer = a_pGraphic->CreateDefaultQuad(&m_Stride, &m_VertexCount);
	m_pQuad = a_pGraphic->CreateCRenderQuad();

	//scale the texture at the screen size
	m_PlaneTransform.SetScale(static_cast<float>(m_Texture[0].GetWidth()), static_cast<float>(m_Texture[0].GetHeight()), 0);

	//Transform the quad just a littlebit so they dont get rendered over each other
	m_PlaneTransform.SetPosition(0, 0, m_Slot * -0.01f);
}

void triebWerk::CRenderTarget::SetRenderTarget(const unsigned short a_Slot) const
{
	m_pGraphicsHandle->GetDeviceContext()->OMSetRenderTargets(1, &m_pRenderTargetView[a_Slot], m_pGraphicsHandle->GetDepthStencilView());
}

void triebWerk::CRenderTarget::ClearRenderTarget(const unsigned short a_Slot) const
{
	m_pGraphicsHandle->GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView[a_Slot], m_ClearColor);

	m_pGraphicsHandle->GetDeviceContext()->ClearDepthStencilView(m_pGraphicsHandle->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void triebWerk::CRenderTarget::SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A)
{
	m_ClearColor[0] = a_R;
	m_ClearColor[1] = a_G;
	m_ClearColor[2] = a_B;
	m_ClearColor[3] = a_A;
}

void triebWerk::CRenderTarget::Resize(unsigned int a_ScreenWidth, unsigned int a_ScreenHeight)
{
	for (size_t i = 0; i < 2; i++)
	{

		m_Texture[i].GetD3D11Texture()->Release();
		m_Texture[i].GetShaderResourceView()->Release();

		D3D11_TEXTURE2D_DESC textureDesc;
		HRESULT result;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.Width = a_ScreenWidth;
		textureDesc.Height = a_ScreenHeight;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		ID3D11Texture2D* pTexture = nullptr;

		result = m_pGraphicsHandle->GetDevice()->CreateTexture2D(&textureDesc, NULL, &pTexture);

		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		ID3D11ShaderResourceView* pShaderResource = nullptr;

		result = m_pGraphicsHandle->GetDevice()->CreateRenderTargetView(pTexture, &renderTargetViewDesc, &m_pRenderTargetView[i]);

		// Setup the description of the shader resource view.
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		// Create the shader resource view.
		result = m_pGraphicsHandle->GetDevice()->CreateShaderResourceView(pTexture, &shaderResourceViewDesc, &pShaderResource);

		m_Texture[i].SetTexture(a_ScreenWidth, a_ScreenHeight, pTexture, pShaderResource);
	}

	//Resize the scale of the quad
	m_PlaneTransform.SetScale(static_cast<float>(m_Texture[0].GetWidth()), static_cast<float>(m_Texture[0].GetHeight()), 0);
}

triebWerk::CTexture2D * triebWerk::CRenderTarget::GetSceneTexture()
{
	return &m_DefaultSceneTexture;
}

void triebWerk::CRenderTarget::Clear()
{
	if(m_pRenderTargetView != nullptr)
		m_pRenderTargetView[0]->Release();

	m_RenderBatch.Free();
}