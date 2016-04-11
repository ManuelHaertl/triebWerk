#include <CConfiguration.h>

void triebWerk::CConfiguration::AddConfigurationPair(std::string a_Key, std::string a_Value)
{
	m_ConfigurationTable.insert(std::pair<std::string, std::string>(a_Key, a_Value));
}

std::string triebWerk::CConfiguration::GetValue(std::string a_Key)
{
	auto foundIterator = this->m_ConfigurationTable.find(a_Key);

	if (foundIterator == this->m_ConfigurationTable.end())
	{
		return std::string();
	}
	else
	{
		return foundIterator->second;
	}
}
