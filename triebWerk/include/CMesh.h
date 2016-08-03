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

			static bool IsEqual(const SVertex& a_rVertexA, const SVertex& a_rVertexB)
			{
				if (memcmp(&a_rVertexA, &a_rVertexB, sizeof(SVertex)) == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

	public:
		CMesh::SVertex* m_pVertices;
		ID3D11Buffer* m_pVertexBuffer;
		size_t m_VertexCount;
		size_t m_IndexCount;

	public:
		CMesh();
		~CMesh();
	};
}
