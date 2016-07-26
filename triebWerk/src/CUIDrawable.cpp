#include "..\include\CUIDrawable.h"

triebWerk::CUIDrawable::CUIDrawable(CGraphics * a_pGraphicsHandle) :
	m_pVertexBuffer(nullptr),
	m_Stride(0),
	m_Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	m_pVertexBuffer = a_pGraphicsHandle->CreateDefaultQuad(&m_Stride, &m_VertexCount);
}

triebWerk::CUIDrawable::~CUIDrawable()
{
	m_pVertexBuffer->Release();
}

triebWerk::IDrawable::EDrawableType triebWerk::CUIDrawable::GetType()
{
	return IDrawable::EDrawableType::UI;
}

void triebWerk::CUIDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{
	m_Transformation = a_rTransform;

	if (m_Material.m_pPixelShader.m_pTextures[0] != nullptr)
	{
		m_Transformation.r[0].m128_f32[0] *= m_Material.m_pPixelShader.m_pTextures[0]->GetWidth();
		m_Transformation.r[1].m128_f32[1] *= m_Material.m_pPixelShader.m_pTextures[0]->GetHeight();
	}
}

bool triebWerk::CUIDrawable::IsDrawableValid()
{
	if (m_Material.m_ID.GetHash() != 0 && m_pVertexBuffer != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
