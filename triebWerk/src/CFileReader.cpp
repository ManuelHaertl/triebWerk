#include <CFileReader.h>

triebWerk::CFileReader::CFileReader() : m_ReachedEnd(false)
{
}

triebWerk::CFileReader::~CFileReader()
{
}

bool triebWerk::CFileReader::ReadData(const char * a_pLoadPath)
{

	//Read the complete File into one String
	std::ifstream input(a_pLoadPath);
	m_Data.assign((std::istreambuf_iterator<char>(input)),(std::istreambuf_iterator<char>()));

	m_StringIterator = 0;
	m_LineCounter = 0;

	if (m_Data.size() == 0)
		return false;

	return true;
}

bool triebWerk::CFileReader::ReachedEndOfFile()
{
	return this->m_ReachedEnd;
}

std::string& triebWerk::CFileReader::GetLine()
{
	//Search for next backspace and return this Line
	size_t nextLine = m_Data.find("\n", m_StringIterator);
	if (nextLine == std::string::npos)
	{
		m_ReachedEnd = true;
	}

	std::string t = m_Data.substr(m_StringIterator, nextLine - m_StringIterator);

	m_StringIterator = nextLine + strlen("\n");

	m_LineCounter++;

	return t;
}

std::string triebWerk::CFileReader::GetAllData()
{
	return this->m_Data;
}

void triebWerk::CFileReader::CloseFile()
{
	this->m_Data.clear();
	this->m_StringIterator = 0;
	this->m_ReachedEnd = false;
	m_LineCounter = 0;
}

unsigned int triebWerk::CFileReader::GetLineCount()
{
	return this->m_LineCounter;
}


