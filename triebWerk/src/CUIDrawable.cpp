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
	return IDrawable::EDrawableType();
}

void triebWerk::CUIDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{
	m_Transformation = a_rTransform;
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
