#include <CFileReader.h>

triebWerk::CFileReader::CFileReader() :
	m_ReachedEnd(false),
	m_LineCounter(0),
	m_pData(nullptr),
	m_pLineBuffer(nullptr),
	m_DataIterator(0),
	m_pFilePointer(nullptr)
{
}

triebWerk::CFileReader::~CFileReader()
{
	if(m_pData != nullptr)
		delete[] m_pData;
	if (m_pLineBuffer != nullptr)
		delete[] m_pLineBuffer;
}

bool triebWerk::CFileReader::ReadData(const char * a_pLoadPath)
{
	//open file read only
	fopen_s(&m_pFilePointer, a_pLoadPath, "rb");
	if (m_pFilePointer == nullptr)
		return false;

	//Get the data size
	fseek(m_pFilePointer, 0, SEEK_END);
	m_DataSize = static_cast<size_t>(ftell(m_pFilePointer));
	fseek(m_pFilePointer, 0, SEEK_SET);

	if (m_DataSize == 0)
		return false;

	//allocate the memory space and clear it
	m_pData = new char[m_DataSize+1];

	//allocate memory for buffering
	m_pLineBuffer = new char[m_MaxLineBufferSize];

	//read all data in one call
	fread(m_pData, m_DataSize, 1, m_pFilePointer);
	m_pData[m_DataSize] = 0;
	//close the data after reading
	fclose(m_pFilePointer);

	return true;
}

bool triebWerk::CFileReader::ReachedEndOfFile()
{
	return m_ReachedEnd;
}

char* triebWerk::CFileReader::GetLine()
{
	//new line
	m_LineCounter++;
	
	//clear buffer
	memset(m_pLineBuffer, '\0', m_MaxLineBufferSize);
	
	size_t lineStart = m_DataIterator;

	//run till end of file is reached
	while (*(m_pData + m_DataIterator))
	{
		//if reached end of line return a string
		if (*(m_pData + m_DataIterator) == '\n')
		{
			memcpy(m_pLineBuffer, m_pData + lineStart, m_DataIterator - lineStart);
			//std::string string = m_pLineBuffer;
			//Skip the '\n'
			m_DataIterator++;
			return m_pLineBuffer;
		}

		m_DataIterator++;
	}

	m_ReachedEnd = true;

	memcpy(m_pLineBuffer, m_pData + lineStart, m_DataIterator - lineStart);
	return m_pLineBuffer;
}

//void triebWerk::CFileReader::GetLineFast(std::string & a_rString)
//{
//	////Search for next backspace and return this Line
//	//size_t nextLine = m_Data.find("\n", m_StringIterator);
//	//if (nextLine == std::string::npos)
//	//{
//	//	m_ReachedEnd = true;
//	//}
//
//	//a_rString = m_Data.substr(m_StringIterator, nextLine - m_StringIterator);
//
//	//m_StringIterator = nextLine + strlen("\n");
//
//	//m_LineCounter++;
//}

std::string triebWerk::CFileReader::GetAllData()
{
	return m_pData;
}

unsigned int triebWerk::CFileReader::GetLineCount()
{
	return this->m_LineCounter;
}


