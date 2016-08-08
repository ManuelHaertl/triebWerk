#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace triebWerk
{
	class CFileWriter
	{
	private:
		std::vector<std::string> m_Lines;
		FILE* m_pFile;

	public:
		CFileWriter();
		~CFileWriter();

	public:
		bool CreateSaveFile(const char* a_pPath);
		void SetParams(const std::string& a_rKey, const std::string& a_rValue);
		void SaveFile();
	};
}