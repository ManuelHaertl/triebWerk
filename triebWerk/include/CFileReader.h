#pragma once
#include <string>
#include <fstream>
namespace triebWerk
{

class CFileReader
{
private:
	std::string m_Data;
	size_t m_StringIterator;
	unsigned int m_LineCounter;
	bool m_ReachedEnd;

public:
	CFileReader();
	virtual ~CFileReader();

protected:
	bool ReadData(const char* a_pLoadPath);
	bool ReachedEndOfFile();
	std::string& GetLine();
	std::string GetAllData();
	void CloseFile();
	unsigned int GetLineCount();
};
}
