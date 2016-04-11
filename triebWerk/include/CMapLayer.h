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
		std::vector<short>m_Indices;
		std::unordered_map<std::string, std::string>m_Properties;
		std::string m_TilesetName;
		//CTexture2D* m_TileSetTexture;

	public:
		CMapLayer();
		~CMapLayer();

	public:
		ETypes::Type GetType() override;

	};
}