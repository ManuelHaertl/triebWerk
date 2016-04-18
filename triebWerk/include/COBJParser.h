#pragma once
#include <CMesh.h>
#include <fstream>
#include <DirectXMath.h>
#include <string>
#include <vector>

namespace triebWerk
{
	class COBJParser
	{
	public:
		CMesh::SVertex* m_pVertices;
		size_t m_VertexCount;

	private:
		std::vector<DirectX::XMFLOAT3> m_VertexPoint;
		std::vector<DirectX::XMFLOAT2> m_UV;
		std::vector<DirectX::XMFLOAT3> m_Normal;

		std::vector<CMesh::SVertex> m_Vertices;

	public:
		COBJParser();
		~COBJParser();

	public:
		void LoadOBJ(const char* a_pPath);

	private:
		std::string GetLine(std::string& a_rText);
		void AddVertex(std::string& a_Text);
		void AddVertexPoint(std::string& a_Text);
		void AddUV(std::string& a_Text);
		void AddNormal(std::string& a_Text);

	};
}