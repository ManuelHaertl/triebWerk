#pragma once
#include <string>
#include <fstream>
namespace triebWerk
{

class CFileReader
{
private:
	const size_t m_MaxLineBufferSize = 400;

private:
	FILE* m_pFilePointer;
	char* m_pData;
	char* m_pLineBuffer;
	size_t m_DataIterator;
	size_t m_DataSize;
	unsigned int m_LineCounter;
	bool m_ReachedEnd;

public:
	CFileReader();
	virtual ~CFileReader();

protected:
	//Reads the all data into memory 
	bool ReadData(const char* a_pLoadPath);
	//Is file reader at the end of file
	bool ReachedEndOfFile();
	//Get the next data till a \n is hit
	std::string GetLine();
	//Get all data in memory
	std::string GetAllData();
	//Get the line count of the reader
	unsigned int GetLineCount();
};
}
