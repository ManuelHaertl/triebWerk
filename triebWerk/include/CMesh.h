#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

namespace triebWerk
{
	class CMesh
	{
	public:
		struct SVertex
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 uv;
			DirectX::XMFLOAT3 normal;
		};

	public:
		ID3D11Buffer* m_pVertexBuffer;
		unsigned int m_VertexCount;

	public:
		CMesh();
		~CMesh();
	};
}
