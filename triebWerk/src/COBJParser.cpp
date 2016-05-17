#include <COBJParser.h>
#include <iostream>


triebWerk::COBJParser::COBJParser() :
	m_pVertices(nullptr),
	m_VertexCount(0),
	m_IndexCount(0),
	m_pIndices(nullptr)
{

}

triebWerk::COBJParser::~COBJParser()
{
	delete[] m_Vertices;
}

//Alexander new code:

bool triebWerk::COBJParser::LoadOBJ(const char * a_pPath)
{
	m_Vertices = new CMesh::SVertex[m_MAX_VERTICES];

	//Let the FileReader preload the data
	bool success = ReadData(a_pPath);
	
	if (!success)
		return false;

	//Reserve memory for the string
	std::string line;
	line.reserve(200);

	do
	{
		//Get Line to read
		GetLineFast(line);

		if (BeginLineWith(line, "v "))
		{
			AddVertexPoint(line);
		}
		else if(BeginLineWith(line, "vt "))
		{
			AddUV(line);
		}
		else if(BeginLineWith(line, "vn "))
		{
			AddNormal(line);
		}
		else if(BeginLineWith(line, "f "))
		{
			size_t firstSpace = 0;
			size_t secondSpace = 0;
			bool endOfLine = false;

			//Read all Vertex Indices
			while (!endOfLine)
			{
				firstSpace = line.find(' ', secondSpace);

				secondSpace = line.find(' ', firstSpace + 1);

				//End of Line reached
				if (secondSpace == std::string::npos || secondSpace +1 == line.size())
				{
					secondSpace = line.size();
					endOfLine = true;
				}

				//Add final Vertex 
				AddVertex(line.substr(firstSpace, secondSpace - firstSpace));
			}
		}

	} while (ReachedEndOfFile() != true);

	if (m_VertexCount > 0 && m_Indices.size() > 0)
	{
		m_pVertices = m_Vertices;
		m_pIndices = &m_Indices[0];
	}
	else
	{
		return false;
	}

	m_IndexCount = m_Indices.size();

	CloseFile();

	return true;
}

void triebWerk::COBJParser::AddVertexPoint(std::string & a_Text)
{
	DirectX::XMFLOAT3 vertex;
	
	size_t pos1 = a_Text.find_first_of(' ', 0) +1;
	size_t pos2 = a_Text.find(' ', pos1+1);
	size_t pos3 = a_Text.find(' ', pos2+1);

	vertex.x = std::stof(a_Text.substr(pos1, pos2-pos1));
	vertex.y = std::stof(a_Text.substr(pos2, pos3-pos2));
	vertex.z = std::stof(a_Text.substr(pos3, a_Text.size()-pos3)) * -1.0f; //transfer to lh
	
	m_VertexPoint.push_back(vertex);
}

void triebWerk::COBJParser::AddUV(std::string & a_Text)
{
	DirectX::XMFLOAT2 uv;

	size_t pos1 = a_Text.find_first_of(' ', 0);
	size_t pos2 = a_Text.find(' ', pos1 + 1);

	uv.x = std::stof(a_Text.substr(pos1, pos2 - pos1));
	uv.y = 1.0f - std::stof(a_Text.substr(pos2, a_Text.size() - pos2)); //transfer to lh

	m_UV.push_back(uv);
	m_ContainsUVs = true;
}

void triebWerk::COBJParser::AddNormal(std::string & a_Text)
{
	DirectX::XMFLOAT3 normal;

	size_t pos1 = a_Text.find_first_of(' ', 0);
	size_t pos2 = a_Text.find(' ', pos1 + 1);
	size_t pos3 = a_Text.find(' ', pos2 + 1);

	normal.x = std::stof(a_Text.substr(pos1, pos2 - pos1));
	normal.y = std::stof(a_Text.substr(pos2, pos3 - pos2));
	normal.z = std::stof(a_Text.substr(pos3, a_Text.size() - pos3)) * -1.0f; //transfer to lh

	m_Normal.push_back(normal);
	m_ContainsNormals = true;
}

unsigned int triebWerk::COBJParser::CreateVertex(CMesh::SVertex & a_rVertex)
{

	for (size_t i = 0; i < m_VertexCount; i++)
	{
		if (CMesh::SVertex::IsEqual(m_Vertices[i], a_rVertex) == true)
		{
			return static_cast<unsigned int>(i);
		}
	}

	m_Vertices[m_VertexCount] = a_rVertex;
	m_VertexCount++;
	return static_cast<unsigned int>(m_VertexCount -1);
}

void triebWerk::COBJParser::AddVertex(std::string & a_Text)
{
	CMesh::SVertex vertex;

	if (!m_ContainsNormals && !m_ContainsUVs)
	{
		int v = std::stoi(a_Text);

		vertex.position = m_VertexPoint[v - 1];
		vertex.normal = DirectX::XMFLOAT3(0, 0, 0);
		vertex.uv = DirectX::XMFLOAT2(0, 0);
	}


	if (m_ContainsNormals && !m_ContainsUVs)
	{
		size_t backslashPos = a_Text.find_first_of("//", 0);

		int v = std::stoi(a_Text.substr(0, backslashPos));
		int vn = std::stoi(a_Text.substr(backslashPos + 2, backslashPos - a_Text.size()));

		vertex.position = m_VertexPoint[v - 1];
		vertex.normal = m_Normal[vn-1];
		vertex.uv = DirectX::XMFLOAT2(0, 0);
	}

	if (m_ContainsUVs && !m_ContainsNormals)
	{
		size_t backslashPos = a_Text.find_first_of("/", 0);

		int v = std::stoi(a_Text.substr(0, backslashPos));
		int vt = std::stoi(a_Text.substr(backslashPos + 1, backslashPos - a_Text.size()));

		vertex.position = m_VertexPoint[v - 1];
		vertex.normal = DirectX::XMFLOAT3(0, 0, 0);
		vertex.uv = m_UV[vt - 1];
	}
	
	if (m_ContainsUVs && m_ContainsNormals)
	{
		size_t backslashPosFirst = a_Text.find_first_of("/", 0);
		size_t backslashPosSecond = a_Text.find("/", backslashPosFirst+1);

		int v = std::stoi(a_Text.substr(0, backslashPosFirst));
		int vt = std::stoi(a_Text.substr(backslashPosFirst + 1, backslashPosSecond - backslashPosFirst));
		int vn = std::stoi(a_Text.substr(backslashPosSecond + 1, a_Text.size() - backslashPosSecond));

		vertex.position = m_VertexPoint[v - 1];
		vertex.normal = m_Normal[vn -1];
		vertex.uv = m_UV[vt - 1];
	}

	m_Indices.push_back(CreateVertex(vertex));
}

bool triebWerk::COBJParser::BeginLineWith(std::string& a_rLine, const char * a_pStart)
{
	size_t startPos = a_rLine.find(a_pStart);

	if (startPos != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//Manuel old working code:
//void triebWerk::COBJParser::LoadOBJ(const char * a_pPath)
//{
//	std::ifstream ifs(a_pPath);
//	std::string data(
//		(std::istreambuf_iterator<char>(ifs)),
//		(std::istreambuf_iterator<char>()));
//
//	while (data.length() > 0)
//	{
//		std::string line = GetLine(data);
//
//		size_t linePosition = line.find_first_of(' ', 0);
//		if (linePosition == std::string::npos)
//			continue;
//
//		std::string kind = line.substr(0, linePosition);
//		line.erase(0, linePosition + 1);
//
//		if (kind == "v")
//		{
//			AddVertexPoint(line);
//		}
//		else if (kind == "vt")
//		{
//			AddUV(line);
//		}
//		else if (kind == "vn")
//		{
//			AddNormal(line);
//		}
//		else if (kind == "f")
//		{
//			size_t pos;
//			std::string vertex;
//
//			pos = line.find_first_of(" ", 0);
//			vertex = line.substr(0, pos);
//			AddVertex(vertex);
//
//			line.erase(0, pos + 1);
//			pos = line.find_first_of(" ", 0);
//			vertex = line.substr(0, pos);
//			AddVertex(vertex);
//
//			line.erase(0, pos + 1);
//			AddVertex(line);
//		}
//	}
//
//	m_pVertices = new CMesh::SVertex[m_VertexCount];
//
//	for (size_t i = 0; i < m_VertexCount; ++i)
//	{
//		m_pVertices[i] = m_Vertices[i];
//	}
//}
//
//std::string triebWerk::COBJParser::GetLine(std::string & a_rText)
//{
//	size_t linePosition = a_rText.find_first_of('\n', 0);
//
//	if (linePosition == std::string::npos)
//	{
//		std::string line = a_rText;
//		a_rText.clear();
//		return line;
//	}
//
//	std::string line = a_rText.substr(0, linePosition);
//	a_rText.erase(0, linePosition + 1);
//	return line;
//}
//
//void triebWerk::COBJParser::AddVertex(std::string & a_Text)
//{
//	CMesh::SVertex vertex;
//
//	size_t pos = a_Text.find_first_of('/', 0);
//	int v = std::stoi(a_Text.substr(0, pos));
//
//	a_Text.erase(0, pos + 1);
//
//	pos = a_Text.find_first_of('/', 0);
//	int vt = std::stoi(a_Text.substr(0, pos));
//
//	a_Text.erase(0, pos + 1);
//	int vn = std::stoi(a_Text);
//
//	vertex.position = m_VertexPoint[v - 1];
//	vertex.uv = m_UV[vt - 1];
//	vertex.normal = m_Normal[vn - 1];
//
//	m_Vertices.push_back(vertex);
//	m_VertexCount++;
//}
//
//void triebWerk::COBJParser::AddVertexPoint(std::string & a_Text)
//{
//	DirectX::XMFLOAT3 vertex;
//
//	size_t pos = a_Text.find_first_of(' ', 0);
//	vertex.x = std::stof(a_Text.substr(0, pos));
//
//	a_Text.erase(0, pos + 1);
//
//	pos = a_Text.find_first_of(' ', 0);
//	vertex.y = std::stof(a_Text.substr(0, pos));
//
//	a_Text.erase(0, pos + 1);
//	vertex.z = std::stof(a_Text);
//
//	m_VertexPoint.push_back(vertex);
//}
//
//void triebWerk::COBJParser::AddUV(std::string & a_Text)
//{
//	DirectX::XMFLOAT2 uv;
//
//	size_t pos = a_Text.find_first_of(' ', 0);
//	uv.x = std::stof(a_Text.substr(0, pos));
//
//	a_Text.erase(0, pos + 1);
//	uv.y = std::stof(a_Text);
//
//	m_UV.push_back(uv);
//}
//
//void triebWerk::COBJParser::AddNormal(std::string & a_Text)
//{
//	DirectX::XMFLOAT3 vertex;
//
//	size_t pos = a_Text.find_first_of(' ', 0);
//	vertex.x = std::stof(a_Text.substr(0, pos));
//
//	a_Text.erase(0, pos + 1);
//
//	pos = a_Text.find_first_of(' ', 0);
//	vertex.y = std::stof(a_Text.substr(0, pos));
//
//	a_Text.erase(0, pos + 1);
//	vertex.z = std::stof(a_Text);
//
//	m_Normal.push_back(vertex);
//}
