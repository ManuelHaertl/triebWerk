#include <CINIParser.h>

triebWerk::CINIParser::CINIParser()
{
}

triebWerk::CINIParser::~CINIParser()
{
}

triebWerk::CConfiguration * triebWerk::CINIParser::ParseData(const char * a_pFilePath)
{
	CConfiguration* configuration = new CConfiguration();
	ReadData(a_pFilePath);

	std::string line;

	do
	{
		line = GetLine();
		
		if (line.front() == ';')
		{
			//skip comment
		}
		else
		{
			std::string key;
			std::string value;

			size_t equalPos = line.find("=");

			if (equalPos == std::string::npos)
				continue;

			key = line.substr(0, equalPos);
			value = line.substr(equalPos + 1, line.size() - equalPos);
			configuration->AddConfigurationPair(key, value);
		}

	} while (ReachedEndOfFile() != true);

	return configuration;
}


