#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "CMapImageLayer.h"
#include "CMapLayer.h"
#include "CTileset.h"
#include <CObjectLayer.h>

namespace triebWerk
{
    class CTilesetMap
    {
    public:
        typedef std::pair<std::string, std::string>PropertyPair;

    public:
        struct SMap
        {
            std::string m_MapName;
            std::string m_Orientation;
            std::string m_RenderOrder;
            unsigned short m_Width;
            unsigned short m_Height;
            unsigned short m_TileWidth;
            unsigned short m_TileHeight;
            unsigned short m_NextObjectID;
        };

    public:
        std::vector<CTileset*> m_Tilesets;
        std::vector<IMapLayer*> m_Layers;
        SMap m_Map;

    public:
        CTilesetMap();
        ~CTilesetMap();

    public:
        void ClearMap();
    };
}
