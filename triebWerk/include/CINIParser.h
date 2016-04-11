#pragma once
#include <CFileReader.h>
#include <CConfiguration.h>

namespace triebWerk
{
	class CINIParser : public CFileReader
	{
	public:
		CINIParser();
		~CINIParser();

	public:
		CConfiguration* ParseData(const char * a_pFilePath);
	};
}