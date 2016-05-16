#pragma once
#include <CFileReader.h>
#include <CTWFParser.h>
#include <CTWFData.h>

namespace triebWerk
{
	class CTWFParser : public CFileReader
	{
	public:
		CTWFParser();
		~CTWFParser();

	public:
		void ParseData(const char * a_pFilePath, CTWFData* a_pDataOut);
	};
}