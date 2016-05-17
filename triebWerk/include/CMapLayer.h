#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "IMapLayer.h"
//#include "CTexture2D.h"
namespace triebWerk
{
	class CMapLayer : public IMapLayer
	{
	public:
		std::string m_LayerName;
		unsigned short m_LayerWidth;
		unsigned short m_LayerHeight;
		short* m_Indices;
		short m_IndicesIterator;
		std::unordered_map<std::string, std::string>m_Properties;
		std::string m_TilesetName;

	public:
		CMapLayer();
		~CMapLayer();

	public:
		ETypes::Type GetType() override;

	};
}