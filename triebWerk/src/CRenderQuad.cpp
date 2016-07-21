#include <CRenderQuad.h>


triebWerk::CRenderQuad::CRenderQuad(UINT a_VertexCount, UINT a_Stride, ID3D11Buffer * a_pVertexBuffer)
	: m_VertexCount(0)
	, m_Stride(0)
	, m_pVertexBuffer(nullptr)
	, m_Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	m_VertexCount = a_VertexCount;
	m_Stride = a_Stride;
	m_pVertexBuffer = a_pVertexBuffer;
}

triebWerk::CRenderQuad::~CRenderQuad()
{
	if (m_pVertexBuffer != nullptr)
		m_pVertexBuffer->Release();
}

void triebWerk::CRenderQuad::SetBuffer(ID3D11DeviceContext* a_pDeviceContext) const
{
	UINT offset = 0;
	a_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_Stride, &offset);
}
