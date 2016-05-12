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
				if (a_rVertexA.position.x == a_rVertexB.position.x && a_rVertexA.position.y == a_rVertexB.position.y && a_rVertexA.position.z == a_rVertexB.position.z &&
					a_rVertexA.normal.x == a_rVertexB.normal.x && a_rVertexA.normal.y == a_rVertexB.normal.y && a_rVertexA.normal.z == a_rVertexB.normal.z &&
					a_rVertexA.uv.x == a_rVertexB.uv.x && a_rVertexA.uv.y == a_rVertexB.uv.y)
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
		ID3D11Buffer* m_pIndexBuffer;
		size_t m_VertexCount;
		size_t m_IndexCount;

	public:
		CMesh();
		~CMesh();
	};
}
