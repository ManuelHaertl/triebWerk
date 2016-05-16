#pragma once
#include <unordered_map>
namespace triebWerk
{
	class CTWFData
	{
	public:
		std::unordered_map<std::string, std::string> m_ConfigurationTable;

	public:
		void AddConfigurationPair(std::string a_Key, std::string a_Value);
		std::string GetValue(std::string a_Value);
	};
}
