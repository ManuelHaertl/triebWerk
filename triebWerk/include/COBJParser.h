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
	public:
		CMesh::SVertex* m_pVertices;
		unsigned int* m_pIndices;
		size_t m_VertexCount;
		size_t m_IndexCount;

	private:
		std::vector<DirectX::XMFLOAT3> m_VertexPoint;
		std::vector<DirectX::XMFLOAT2> m_UV;
		std::vector<DirectX::XMFLOAT3> m_Normal;

		std::vector<CMesh::SVertex> m_Vertices;
		std::vector<unsigned int> m_Indices;

		bool m_ContainsNormals;
		bool m_ContainsUVs;

	public:
		COBJParser();
		~COBJParser();

	public:
		void LoadOBJ(const char* a_pPath);

	private:
		unsigned int CreateVertex(CMesh::SVertex& a_rVertex);
		void AddVertex(std::string& a_Text);
		void AddVertexPoint(std::string& a_Text);
		void AddUV(std::string& a_Text);
		void AddNormal(std::string& a_Text);

		bool BeginLineWith(std::string& a_rLine, const char* a_pStart);
	};
}