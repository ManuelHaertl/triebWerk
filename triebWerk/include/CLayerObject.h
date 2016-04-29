#pragma once
#include <unordered_map>
namespace triebWerk
{
	class CLayerObject
	{
	public:
		int m_ID;
		int m_GID;
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
		std::unordered_map<std::string, std::string>m_Properties;
	};
}
