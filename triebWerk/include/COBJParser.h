#pragma once
#include <CMesh.h>
#include <fstream>
#include <DirectXMath.h>
#include <string>
#include <CFileReader.h>
#include <vector>

namespace triebWerk
{
	class COBJParser : CFileReader
	{
	private:
		const size_t m_MAX_VERTICES = 60000;

	public:
		CMesh::SVertex* m_pVertices;
		unsigned int* m_pIndices;
		size_t m_VertexCount;
		size_t m_IndexCount;

	private:
		DirectX::XMFLOAT3* m_VertexPoint;
		DirectX::XMFLOAT2* m_UV;
		DirectX::XMFLOAT3* m_Normal;

		CMesh::SVertex* m_Vertices;

		bool m_ContainsNormals;
		bool m_ContainsUVs;

		size_t m_VertexPointCount = 0;
		size_t m_NormalCount = 0;
		size_t m_UVCount = 0;

	public:
		COBJParser();
		~COBJParser();

	public:
		bool LoadOBJ(const char* a_pPath);

	private:
		unsigned int CreateVertex(CMesh::SVertex& a_rVertex);
		void AddVertex(const char* a_Text);
		void AddVertexPoint(const char* a_pLine);
		void AddUV(const char* a_pLine);
		void AddNormal(const char* a_pLine);
		void ReadFaces(const char* a_Line);

		bool BeginLineWith(const char* a_pLine, const char* a_pStart);
		void GetCoordinatesFromLine(const char* a_pLine, DirectX::XMFLOAT3* a_pOutBuffer);
	};
}