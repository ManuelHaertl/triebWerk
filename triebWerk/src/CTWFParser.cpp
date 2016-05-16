#include <CTWFParser.h>

triebWerk::CTWFParser::CTWFParser()
{
}

triebWerk::CTWFParser::~CTWFParser()
{
}

void triebWerk::CTWFParser::ParseData(const char * a_pFilePath, CTWFData* a_pDataOut)
{
	ReadData(a_pFilePath);

	std::string line;

	do
	{
		line = GetLine();

		if (line.size() != 0 && line.front() == ';')
		{
			//skip comment
		}
		else
		{
			std::string key;
			std::string value;

			size_t equalPos = line.find(" = ");

			if (equalPos == std::string::npos)
			{
				continue;
			}


			key = line.substr(0, equalPos);
			value = line.substr(equalPos + 1, line.size() - equalPos);
			a_pDataOut->AddConfigurationPair(key, value);
		}

	} while (ReachedEndOfFile() != true);
}


