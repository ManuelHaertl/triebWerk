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
		const size_t m_MAX_VERTICES = 10000;

	public:
		CMesh::SVertex* m_pVertices;
		unsigned int* m_pIndices;
		size_t m_VertexCount;
		size_t m_IndexCount;

	private:
		std::vector<DirectX::XMFLOAT3> m_VertexPoint;
		std::vector<DirectX::XMFLOAT2> m_UV;
		std::vector<DirectX::XMFLOAT3> m_Normal;

		CMesh::SVertex* m_Vertices;
		std::vector<unsigned int> m_Indices;

		bool m_ContainsNormals;
		bool m_ContainsUVs;

	public:
		COBJParser();
		~COBJParser();

	public:
		bool LoadOBJ(const char* a_pPath);

	private:
		unsigned int CreateVertex(CMesh::SVertex& a_rVertex);
		void AddVertex(std::string& a_Text);
		void AddVertexPoint(const char* a_pLine);
		void AddUV(const char* a_pLine);
		void AddNormal(const char* a_pLine);
		void ReadFaces(std::string& a_Line);

		bool BeginLineWith(std::string& a_rLine, const char* a_pStart);
		void GetCoordinatesFromLine(const char* a_pLine, DirectX::XMFLOAT3* a_pOutBuffer);
	};
}