#include <CRenderTarget.h>

triebWerk::CRenderTarget::CRenderTarget() :
	m_pGraphicsHandle(nullptr),
	m_pRenderTargetView(nullptr),
	m_pTexture(nullptr),
	m_pTextureShaderResourceView(nullptr)
{
	m_ClearColor[0] = 1.0f;
	m_ClearColor[1] = 1.0f;
	m_ClearColor[2] = 1.0f;
	m_ClearColor[3] = 1.0f;
}

triebWerk::CRenderTarget::~CRenderTarget()
{
}

void triebWerk::CRenderTarget::Initialize(CGraphics * a_pGraphic, unsigned int a_Width, unsigned int a_Height)
{
	m_pGraphicsHandle = a_pGraphic;

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

	result = a_pGraphic->GetDevice()->CreateTexture2D(&textureDesc, NULL, &m_pTexture);

	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	result = a_pGraphic->GetDevice()->CreateRenderTargetView(m_pTexture, &renderTargetViewDesc, &m_pRenderTargetView);

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view.
	result = a_pGraphic->GetDevice()->CreateShaderResourceView(m_pTexture, &shaderResourceViewDesc, &m_pTextureShaderResourceView);
}

void triebWerk::CRenderTarget::SetRenderTarget() const
{
	m_pGraphicsHandle->GetDeviceContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pGraphicsHandle->GetDepthStencilView());
}

void triebWerk::CRenderTarget::ClearRenderTarget() const
{
	m_pGraphicsHandle->GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView, m_ClearColor);

	m_pGraphicsHandle->GetDeviceContext()->ClearDepthStencilView(m_pGraphicsHandle->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void triebWerk::CRenderTarget::SetClearColor(const float a_R, const float a_G, const float a_B, const float a_A)
{
	m_ClearColor[0] = a_R;
	m_ClearColor[1] = a_G;
	m_ClearColor[2] = a_B;
	m_ClearColor[3] = a_A;
}

void triebWerk::CRenderTarget::Clear()
{
	m_pRenderTargetView->Release();
	m_pTexture->Release();
	m_pTextureShaderResourceView->Release();
}
