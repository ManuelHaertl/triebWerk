#pragma once
#include <unordered_map>
#include <string>

#include "IMapLayer.h"

namespace triebWerk
{
	class CMapImageLayer : public IMapLayer
	{
	public:
		std::string m_Name;
		short m_PositionX;
		short m_PositionY;
		std::unordered_map<std::string, std::string>Properties;
		std::string m_ImageName;
		unsigned int m_ImageWidth;
		unsigned int m_ImageHeight;

	public:
		CMapImageLayer();
		~CMapImageLayer();

	public:
		ETypes::Type GetType() override;
	};
}

