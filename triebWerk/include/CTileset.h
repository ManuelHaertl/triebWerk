#pragma once

#include <unordered_map>
#include <string>

namespace triebWerk
{
	class CTileset
	{
	public:
		std::string m_TilesetName;
		unsigned short m_TileWidth;
		unsigned short m_TileHeight;
		unsigned short m_TileCount;
		unsigned short m_FirstGid;
		std::unordered_map<std::string, std::string>m_Properties;
		std::string m_ImageName;
		unsigned int m_ImageWidth;
		unsigned int m_ImageHeight;

	public:
		CTileset();
		~CTileset();
	};
}
