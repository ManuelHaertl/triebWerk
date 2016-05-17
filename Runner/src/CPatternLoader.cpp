#include <CPatternLoader.h>

CPatternLoader::CPatternLoader()
{

}

CPatternLoader::~CPatternLoader()
{

}

void CPatternLoader::LoadPattern(std::vector<CPattern*>(&a_pPattern)[CPattern::MaxDifficulty])
{
    std::vector<triebWerk::CTilesetMap*> tilesets;
    twResourceManager->GetAll<triebWerk::CTilesetMap>("data\\Pattern", &tilesets);

    // loop through all tilesets
    for (size_t i = 0; i < tilesets.size(); ++i)
    {
        auto& tileset = *tilesets[i];

        CPattern* pattern = new CPattern();
        pattern->m_Width = tileset.m_Map.m_Width;
        pattern->m_Height = tileset.m_Map.m_Height;

        // loop through all layers in a tileset
        for (size_t j = 0; j < tileset.m_Layers.size(); ++j)
        {
            auto* layer = tileset.m_Layers[j];

            switch (layer->GetType())
            {
            case triebWerk::IMapLayer::ETypes::MapLayer:
                SetMapLayer(static_cast<triebWerk::CMapLayer*>(layer), pattern);
                break;
            case triebWerk::IMapLayer::ETypes::ObjectLayer:
                SetObjectLayer(static_cast<triebWerk::CObjectLayer*>(layer), pattern);
                break;
            }
        }

        m_AllPattern.push_back(pattern);
        a_pPattern[pattern->m_Difficulty - 1].push_back(pattern);
    }

    SetConnectedPattern();
}

void CPatternLoader::SetMapLayer(triebWerk::CMapLayer* const a_pLayer, CPattern* a_pPattern)
{
    int layerWidth = static_cast<int>(a_pLayer->m_LayerWidth);
    int layerHeight = static_cast<int>(a_pLayer->m_LayerHeight);

    for (int y = layerHeight - 1; y >= 0; --y)
    {
        for (int x = layerWidth - 1; x >= 0; --x)
        {
            // get the Tile type
            size_t current = y * layerWidth + x;
            short tile = a_pLayer->m_Indices[current];
            ETileType::Type type = GetTileType(tile);

            if (type != ETileType::Invalid)
            {
                // convert the .TMX Map Layer coordinates to our
                float xPos = static_cast<float>(x) - a_pPattern->m_Width / 2.0f + 0.5f;
                float yPos = static_cast<float>(layerHeight - y - 1) + 0.5f;

                SetTile(type, xPos, yPos, a_pPattern);
            }
        }
    }
}

void CPatternLoader::SetObjectLayer(triebWerk::CObjectLayer* const a_pLayer, CPattern* a_pPattern)
{
    if (a_pLayer->m_Name == StringGame)
    {
        SetPatternProperties(a_pLayer, a_pPattern);
        return;
    }

    for (size_t i = 0; i < a_pLayer->m_Objects.size(); ++i)
    {
        auto& objectProperty = a_pLayer->m_Objects[i];
        ETileType::Type type = GetTileType(objectProperty.m_GID);

        if (type != ETileType::Invalid)
        {
            // convert the .TMX Object Layer coordinates to our
            float xPos = static_cast<float>(objectProperty.m_X) / static_cast<float>(objectProperty.m_Width) - a_pPattern->m_Width / 2.0f + 0.5f;
            float yPos = a_pPattern->m_Height - static_cast<float>(objectProperty.m_Y) / static_cast<float>(objectProperty.m_Height) + 0.5f;

            SetTile(type, xPos, yPos, a_pPattern);
        }
    }
}

void CPatternLoader::SetTile(const ETileType::Type a_Type, const float a_X, const float a_Y, CPattern* a_pPattern)
{
    SPatternTile patternTile;
    patternTile.m_X = a_X;
    patternTile.m_Y = a_Y;
    patternTile.m_Type = a_Type;

    InsertPatternTile(patternTile, a_pPattern);
}

void CPatternLoader::InsertPatternTile(const SPatternTile& a_rPatternTile, CPattern* a_pPattern)
{
    for (int i = a_pPattern->m_Tiles.size() - 1; i >= 0; --i)
    {
        if (a_pPattern->m_Tiles[i].m_Y <= a_rPatternTile.m_Y)
        {
            a_pPattern->m_Tiles.insert(a_pPattern->m_Tiles.begin() + i + 1, a_rPatternTile);
            return;
        }
    }

    a_pPattern->m_Tiles.insert(a_pPattern->m_Tiles.begin(), a_rPatternTile);
}

ETileType::Type CPatternLoader::GetTileType(const short a_Tile) const
{
    switch (a_Tile)
    {
    case ETileType::Checkpoint:
        return ETileType::Checkpoint;
    case ETileType::Points:
        return ETileType::Points;
    case ETileType::Shield:
        return ETileType::Shield;
    case ETileType::Block1x1:
        return ETileType::Block1x1;
    case ETileType::Block2x2:
        return ETileType::Block2x2;
    }

    return ETileType::Invalid;
}

void CPatternLoader::SetPatternProperties(triebWerk::CObjectLayer* const a_pLayer, CPattern* a_pPattern)
{
    for (auto& prop : a_pLayer->Properties)
    {
        if (prop.first == StringDifficulty)
        {
            int difficulty = std::stoi(prop.second);
            a_pPattern->m_Difficulty = difficulty;
        }

        else if (prop.first == StringPriority)
        {
            int priority = std::stoi(prop.second);
            a_pPattern->m_Priority = CPattern::MaxPriorities + 1 - priority;
        }
    }
}

void CPatternLoader::SetConnectedPattern()
{
    size_t patternCount = m_AllPattern.size();
    for (size_t i = 0; i < patternCount; ++i)
    {
        CPattern* current = m_AllPattern[i];

        for (size_t j = 0; j < patternCount; ++j)
        {
            size_t difficulty = current->m_Difficulty - 1;
            size_t priority = current->m_Priority - 1;

            m_AllPattern[j]->m_ConnectedPattern[difficulty][priority].push_back(m_AllPattern[i]);
            AddPriority(m_AllPattern[j]->m_Priorities[difficulty], priority);
        }
    }
}

void CPatternLoader::AddPriority(std::vector<size_t>& a_Priorities, const size_t a_Priority)
{
    size_t count = a_Priorities.size();

    for (size_t i = 0; i < count; ++i)
    {
        if (a_Priority < a_Priorities[i])
        {
            a_Priorities.insert(a_Priorities.begin() + i, a_Priority);
            return;
        }
        else if (a_Priority == a_Priorities[i])
        {
            return;
        }
    }

    a_Priorities.push_back(a_Priority);
}

