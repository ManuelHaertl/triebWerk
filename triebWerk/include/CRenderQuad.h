#pragma once
#include <d3d11.h>

namespace triebWerk
{
	class CRenderQuad
	{
	public:
		UINT m_VertexCount;

	private:
		UINT m_Stride;
		ID3D11Buffer* m_pVertexBuffer;
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;

	public:
		CRenderQuad(UINT a_VertexCount, UINT a_Stride, ID3D11Buffer* a_pVertexBuffer);
		~CRenderQuad();

	public:
		void SetBuffer(ID3D11DeviceContext* a_pDeviceContext) const;
	};
}