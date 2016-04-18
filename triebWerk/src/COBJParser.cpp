#include <COBJParser.h>

triebWerk::COBJParser::COBJParser() :
	m_pVertices(nullptr),
	m_VertexCount(0)
{

}

triebWerk::COBJParser::~COBJParser()
{
	if (m_pVertices != nullptr)
		delete[] m_pVertices;
}

void triebWerk::COBJParser::LoadOBJ(const char * a_pPath)
{
	std::ifstream ifs(a_pPath);
	std::string data(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	while (data.length() > 0)
	{
		std::string line = GetLine(data);

		size_t linePosition = line.find_first_of(' ', 0);
		if (linePosition == std::string::npos)
			continue;

		std::string kind = line.substr(0, linePosition);
		line.erase(0, linePosition + 1);

		if (kind == "v")
		{
			AddVertexPoint(line);
		}
		else if (kind == "vt")
		{
			AddUV(line);
		}
		else if (kind == "vn")
		{
			AddNormal(line);
		}
		else if (kind == "f")
		{
			size_t pos;
			std::string vertex;

			pos = line.find_first_of(" ", 0);
			vertex = line.substr(0, pos);
			AddVertex(vertex);

			line.erase(0, pos + 1);
			pos = line.find_first_of(" ", 0);
			vertex = line.substr(0, pos);
			AddVertex(vertex);

			line.erase(0, pos + 1);
			AddVertex(line);
		}
	}

	m_pVertices = new CMesh::SVertex[m_VertexCount];

	for (size_t i = 0; i < m_VertexCount; ++i)
	{
		m_pVertices[i] = m_Vertices[i];
	}
}

std::string triebWerk::COBJParser::GetLine(std::string & a_rText)
{
	size_t linePosition = a_rText.find_first_of('\n', 0);

	if (linePosition == std::string::npos)
	{
		std::string line = a_rText;
		a_rText.clear();
		return line;
	}

	std::string line = a_rText.substr(0, linePosition);
	a_rText.erase(0, linePosition + 1);
	return line;
}

void triebWerk::COBJParser::AddVertex(std::string & a_Text)
{
	CMesh::SVertex vertex;

	size_t pos = a_Text.find_first_of('/', 0);
	int v = std::stoi(a_Text.substr(0, pos));

	a_Text.erase(0, pos + 1);

	pos = a_Text.find_first_of('/', 0);
	int vt = std::stoi(a_Text.substr(0, pos));

	a_Text.erase(0, pos + 1);
	int vn = std::stoi(a_Text);

	vertex.position = m_VertexPoint[v - 1];
	vertex.uv = m_UV[vt - 1];
	vertex.normal = m_Normal[vn - 1];

	m_Vertices.push_back(vertex);
	m_VertexCount++;
}

void triebWerk::COBJParser::AddVertexPoint(std::string & a_Text)
{
	DirectX::XMFLOAT3 vertex;

	size_t pos = a_Text.find_first_of(' ', 0);
	vertex.x = std::stof(a_Text.substr(0, pos));

	a_Text.erase(0, pos + 1);

	pos = a_Text.find_first_of(' ', 0);
	vertex.y = std::stof(a_Text.substr(0, pos));

	a_Text.erase(0, pos + 1);
	vertex.z = std::stof(a_Text);

	m_VertexPoint.push_back(vertex);
}

void triebWerk::COBJParser::AddUV(std::string & a_Text)
{
	DirectX::XMFLOAT2 uv;

	size_t pos = a_Text.find_first_of(' ', 0);
	uv.x = std::stof(a_Text.substr(0, pos));

	a_Text.erase(0, pos + 1);
	uv.y = std::stof(a_Text);

	m_UV.push_back(uv);
}

void triebWerk::COBJParser::AddNormal(std::string & a_Text)
{
	DirectX::XMFLOAT3 vertex;

	size_t pos = a_Text.find_first_of(' ', 0);
	vertex.x = std::stof(a_Text.substr(0, pos));

	a_Text.erase(0, pos + 1);

	pos = a_Text.find_first_of(' ', 0);
	vertex.y = std::stof(a_Text.substr(0, pos));

	a_Text.erase(0, pos + 1);
	vertex.z = std::stof(a_Text);

	m_Normal.push_back(vertex);
}
