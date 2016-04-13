#pragma once
#include <d3d11.h>

namespace triebWerk
{
	class CMesh
	{
	public:
		struct SVertices
		{
			float x, y, z;
			float u, v;
		};

	public:
		ID3D11Buffer* m_pVertexBuffer;
		unsigned int m_VertexCount;

	public:
		CMesh(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext);
		~CMesh();
	};
}
