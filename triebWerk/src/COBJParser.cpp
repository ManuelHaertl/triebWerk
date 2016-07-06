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

bool triebWerk::COBJParser::LoadOBJ(const char * a_pPath)
{
	m_Vertices = new CMesh::SVertex[m_MAX_VERTICES];

	//Let the FileReader preload the data
	bool success = ReadData(a_pPath);
	
	if (!success)
		return false;

	//Reserve memory for the string
	char* line;

	do
	{
		//Get Line to read
		line = GetLine();

		if (line[0] == '#' || line[0] == '\r')
			continue;

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
			ReadFaces(line);
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

	return true;
}

void triebWerk::COBJParser::AddVertexPoint(const char* a_pLine)
{
	DirectX::XMFLOAT3 vertex;
	
	GetCoordinatesFromLine(a_pLine, &vertex);

	vertex.z *= -1.0f; // LH

	//size_t pos1 = a_Text.find_first_of(' ', 0) +1;
	//size_t pos2 = a_Text.find(' ', pos1+1);
	//size_t pos3 = a_Text.find(' ', pos2+1);

	//vertex.x = std::stof(a_Text.substr(pos1, pos2-pos1));
	//vertex.y = std::stof(a_Text.substr(pos2, pos3-pos2));
	//vertex.z = std::stof(a_Text.substr(pos3, a_Text.size()-pos3)) * -1.0f; //transfer to lh
	
	m_VertexPoint.push_back(vertex);
}

void triebWerk::COBJParser::AddUV(const char* a_pLine)
{
	DirectX::XMFLOAT2 uv;
	DirectX::XMFLOAT3 uvw;

	GetCoordinatesFromLine(a_pLine, &uvw);

	uv.x = uvw.x;
	uv.y = 1.0f - uvw.y; // LH

/*
	int counter = 0;
	double multi = 1.0f;

	const char* ptr = a_Text.c_str();
	float val = 0;
	bool before = true;

	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '\r')
		{
			if (counter == 1)
			{
				uv.x = val;
			}
			else if(counter == 2)
			{
				uv.y = 1.0f - val;
				break;
			}

			val = 0.0f;
			before = true;
			multi = 1.0f;
			counter++;
		}
		else
		{
			if (*ptr == '.')
			{
				multi = 1.0f;
				before = false;
			}

			if (*ptr >= '0' && *ptr <= '9')
			{
				if (before)
				{
					val *= 10;
					val += *ptr - '0';
				}
				else
				{
					float t = *ptr - '0';
					multi *= 10.0f;
					val += t / multi;
				}
			}
		}

		ptr++;
	}*/

	
	//size_t pos1 = a_Text.find_first_of(' ', 0);
	//size_t pos2 = a_Text.find(' ', pos1 + 1);

	//uv.x = std::stof(a_Text.substr(pos1, pos2 - pos1));
	//uv.y = 1.0f - std::stof(a_Text.substr(pos2, a_Text.size() - pos2)); //transfer to lh

	m_UV.push_back(uv);
	m_ContainsUVs = true;
}

void triebWerk::COBJParser::AddNormal(const char* a_pLine)
{
	DirectX::XMFLOAT3 normal;

	GetCoordinatesFromLine(a_pLine, &normal);

	normal.z *= -1.0f; //LH

	//size_t pos1 = a_Text.find_first_of(' ', 0);
	//size_t pos2 = a_Text.find(' ', pos1 + 1);
	//size_t pos3 = a_Text.find(' ', pos2 + 1);

	//normal.x = std::stof(a_Text.substr(pos1, pos2 - pos1));
	//normal.y = std::stof(a_Text.substr(pos2, pos3 - pos2));
	//normal.z = std::stof(a_Text.substr(pos3, a_Text.size() - pos3)) * -1.0f; //transfer to lh

	m_Normal.push_back(normal);
	m_ContainsNormals = true;
}

void triebWerk::COBJParser::ReadFaces(const char* a_pLine)
{
	char buffer[512] = { 0 };
	int counter = 0;
	const char* ptr = a_pLine;
	//int charLength = a_Line.size();
	
	while (*ptr)
	{
		if (*ptr >= '0' && *ptr <= '9')
			break;

		ptr++;
	}

	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '\r' && counter > 0)
		{
			AddVertex(buffer);
			memset(&buffer, 0, 400);
			counter = 0;
		}
		else if((*ptr >= '0' && *ptr <= '9') || *ptr == '/')
		{
			buffer[counter] = *ptr;
			counter++;
		}

		ptr++;
	}

	if (counter > 0)
	{
		AddVertex(buffer);
		memset(&buffer, 0, 400);
		counter = 0;
	}

	//size_t firstSpace = 0;
	//size_t secondSpace = 0;
	//bool endOfLine = false;
	//int counter = 0;

	////Read all Vertex Indices
	//while (!endOfLine)
	//{
	//	firstSpace = a_Line.find(' ', secondSpace);

	//	secondSpace = a_Line.find(' ', firstSpace + 1);

	//	//End of Line reached
	//	if (secondSpace == std::string::npos || secondSpace + 1 == a_Line.size())
	//	{
	//		secondSpace = a_Line.size();
	//		endOfLine = true;
	//	}
	//	std::string t = a_Line.substr(firstSpace, secondSpace - firstSpace);
	//	counter++;
	//	if (counter < 4)
	//		AddVertex(t);
	//}
}

unsigned int triebWerk::COBJParser::CreateVertex(CMesh::SVertex & a_rVertex)
{
	//for (size_t i = 0; i < m_VertexCount; i++)
	//{
	//	if (CMesh::SVertex::IsEqual(m_Vertices[i], a_rVertex) == true)
	//	{
	//		return static_cast<unsigned int>(i);
	//	}
	//}

	m_Vertices[m_VertexCount] = a_rVertex;
	m_VertexCount++;
	return static_cast<unsigned int>(m_VertexCount -1);
}

void triebWerk::COBJParser::AddVertex(const char* a_pText)
{
	CMesh::SVertex vertex;

	const char* ptr = a_pText;

	if (!m_ContainsNormals && !m_ContainsUVs)
	{
		std::string a_Text = a_pText;
		int v = std::stoi(a_Text);

		vertex.position = m_VertexPoint[v - 1];
		vertex.normal = DirectX::XMFLOAT3(0, 0, 0);
		vertex.uv = DirectX::XMFLOAT2(0, 0);
	}

	if (m_ContainsNormals && !m_ContainsUVs)
	{
		std::string a_Text = a_pText;
		size_t backslashPos = a_Text.find_first_of("//", 0);

		int v = std::stoi(a_Text.substr(0, backslashPos));
		int vn = std::stoi(a_Text.substr(backslashPos + 2, backslashPos - a_Text.size()));

		vertex.position = m_VertexPoint[v - 1];
		vertex.normal = m_Normal[vn-1];
		vertex.uv = DirectX::XMFLOAT2(0, 0);
	}

	if (m_ContainsUVs && !m_ContainsNormals)
	{
		std::string a_Text = a_pText;
		size_t backslashPos = a_Text.find_first_of("/", 0);

		int v = std::stoi(a_Text.substr(0, backslashPos));
		int vt = std::stoi(a_Text.substr(backslashPos + 1, backslashPos - a_Text.size()));

		vertex.position = m_VertexPoint[v - 1];
		vertex.normal = DirectX::XMFLOAT3(0, 0, 0);
		vertex.uv = m_UV[vt - 1];
	}
	
	if (m_ContainsUVs && m_ContainsNormals)
	{
		int val = 0;
		int elementCount = 0;

		int elements[3] = { 0 };

		do
		{
			if (*ptr == '/')
			{
				elements[elementCount] = val;
				elementCount++;
				val = 0;
			}
			else
			{
				if (*ptr >= '0' && *ptr <= '9')
				{
					val *= 10;
					val += *ptr - '0';
				}
			}

			ptr++;
		} while (*ptr);

		//last element
		elements[elementCount] = val;

		//size_t backslashPosFirst = a_Text.find_first_of("/", 0);
		//size_t backslashPosSecond = a_Text.find("/", backslashPosFirst+1);

		//int v = std::stoi(a_Text.substr(0, backslashPosFirst));
		//int vt = std::stoi(a_Text.substr(backslashPosFirst + 1, backslashPosSecond - backslashPosFirst));
		//int vn = std::stoi(a_Text.substr(backslashPosSecond + 1, a_Text.size() - backslashPosSecond));

		vertex.position = m_VertexPoint[elements[0] - 1];
		vertex.uv = m_UV[elements[1] - 1];
		vertex.normal = m_Normal[elements[2] - 1];
	}

	m_Indices.push_back(CreateVertex(vertex));
}

bool triebWerk::COBJParser::BeginLineWith(const char* a_pLine, const char * a_pStart)
{
	int wordLength = strlen(a_pStart);
	int charCounter = 0;
	char wordBuffer[32] = { 0 };
	const char* ptr = a_pLine;

	while (*ptr)
	{
		if (charCounter == wordLength)
		{
			if (strcmp(wordBuffer, a_pStart) == 0)
				return true;
			else
				return false;
		}
		else
		{
			wordBuffer[charCounter] = *ptr;
			charCounter++;
		}

		ptr++;
	}

	return false;
	/*std::string a_rLine = a_pLine;
	size_t startPos = a_rLine.find(a_pStart);

	if (startPos != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}*/
}

void triebWerk::COBJParser::GetCoordinatesFromLine(const char * a_pLine, DirectX::XMFLOAT3 * a_pOutBuffer)
{
	//count of coordinates written to
	int elementCount = 0;
	//multiplier to shift the decimal places 
	float decimalPlaceMultiplier = 1.0f;

	//is the coordinate negative or positive
	int sign = 1;

	//iterator 
	const char* ptr = a_pLine;

	float val = 0;

	bool isAtDecimalPlace = false;

	//skip everthing which is at the beginning
	do
	{
		if ((*ptr >= '0' && *ptr <= '9') || *ptr == '-')
		{
			break;
		}

		ptr++;
	} while (*ptr);


	while (*ptr)
	{
		//if a space or the of the line occurs
		if (*ptr == ' ' || *ptr == '\r')
		{
			//set the value for the specific coordinate
			if (elementCount == 0)
				a_pOutBuffer->x = val * sign;
			else if (elementCount == 1)
				a_pOutBuffer->y = val * sign;
			else if (elementCount == 2)
				a_pOutBuffer->z = val*sign;

			//reset the values for the next iteration
			val = 0.0f;
			isAtDecimalPlace = false;
			decimalPlaceMultiplier = 1.0f;
			sign = 1;
			elementCount++;
		}
		else
		{
			if (*ptr == '.')
				isAtDecimalPlace = true;

			if (*ptr == '-')
				sign = -1;

			//numbers to set into value
			if (*ptr >= '0' && *ptr <= '9')
			{
				if (!isAtDecimalPlace)
				{
					val *= 10;
					val += *ptr - '0';
				}
				else
				{
					float number = *ptr - '0';
					//shift the number to the correct decimal place
					decimalPlaceMultiplier *= 10.0f;
					val += number / decimalPlaceMultiplier;
				}
			}
		}

		ptr++;
	}

	if (elementCount == 2)
	{
		a_pOutBuffer->z = val*sign;
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
