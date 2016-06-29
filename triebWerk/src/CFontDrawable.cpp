#include <CFontDrawable.h>
#include <CDebugLogfile.h>

triebWerk::CFontDrawable::CFontDrawable(CGraphics * a_pGraphicsHandle) :
	m_pVertexBuffer(nullptr),
	m_Stride(0),
	m_Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	//Create a vertex buffer for the quad which will be used to draw the truetype textures
	m_pVertexBuffer = a_pGraphicsHandle->CreateDefaultQuad(&m_Stride, &m_VertexCount);
}

triebWerk::CFontDrawable::~CFontDrawable()
{
	if (m_pText != nullptr)
		delete m_pText;
}

void triebWerk::CFontDrawable::SetText(CText * a_pText)
{
	//m_ScaleOfTextureX = a_pText->GetWidth();
	//m_ScaleOfTextureY = a_pText->GetHeight();
	//m_pText = a_pText;

	//m_Material.m_pPixelShader.SetTexture(0, a_pText->GetTexture());
}

triebWerk::IDrawable::EDrawableType triebWerk::CFontDrawable::GetType()
{
	return IDrawable::EDrawableType::Font;
}

void triebWerk::CFontDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{
	m_Transformation = a_rTransform;
}

bool triebWerk::CFontDrawable::IsValidDrawable(const CFontDrawable * a_pDrawableToTest)
{
	if (a_pDrawableToTest->m_Material.m_ID.GetHash() != 0 && a_pDrawableToTest->m_pVertexBuffer != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
