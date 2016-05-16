#include <CPatternLoader.h>

CPatternLoader::CPatternLoader() :
    m_pPattern(nullptr),
    m_PatternCount(0),
    m_MinDifficulty(0),
    m_MaxDifficulty(0),
    m_HasSetDifficulty(false),
    m_MinPriority(0),
    m_MaxPriority(0),
    m_HasSetPriority(false)
{
    
}

CPatternLoader::~CPatternLoader()
{
    
}

void CPatternLoader::LoadPattern()
{
    if (m_pPattern != nullptr)
        delete[] m_pPattern;

	std::vector<triebWerk::CTilesetMap*> tilesets;

   twResourceManager->GetAll<triebWerk::CTilesetMap>("data\\Pattern", &tilesets);

    m_PatternCount = tilesets.size();
    m_pPattern = new CPattern[m_PatternCount];

    SetDefaultValues();

    for (size_t i = 0; i < m_PatternCount; ++i)
    {
        auto& tileset = *tilesets[i];

        m_pPattern[i].m_Width = tileset.m_Map.m_Width;
        m_pPattern[i].m_Height = tileset.m_Map.m_Height;

        for (size_t j = 0; j < tileset.m_Layers.size(); ++j)
        {
            auto* layer = tileset.m_Layers[j];

            switch (layer->GetType())
            {
            case triebWerk::IMapLayer::ETypes::MapLayer:
                SetMapLayer(static_cast<triebWerk::CMapLayer*>(layer), i);
                break;
            case triebWerk::IMapLayer::ETypes::ObjectLayer:
                SetObjectLayer(static_cast<triebWerk::CObjectLayer*>(layer), i);
                break;
            }
        }
    }
}

CPattern* CPatternLoader::GetPattern() const
{
    return m_pPattern;
}

size_t CPatternLoader::GetPatternCount() const
{
    return m_PatternCount;
}

size_t CPatternLoader::GetMinDifficulty() const
{
    return m_MinDifficulty;
}

size_t CPatternLoader::GetMaxDifficulty() const
{
    return m_MaxDifficulty;
}

size_t CPatternLoader::GetMinPriority() const
{
    return m_MinPriority;
}

size_t CPatternLoader::GetMaxPriority() const
{
    return m_MaxPriority;
}

void CPatternLoader::SetMapLayer(triebWerk::CMapLayer* const a_pLayer, const size_t a_Index)
{
    CPattern& pattern = m_pPattern[a_Index];
    int width = static_cast<int>(a_pLayer->m_LayerWidth);
    int height = static_cast<int>(a_pLayer->m_LayerHeight);

    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = width - 1; x >= 0; --x)
        {
            size_t current = y * width + x;
            short tile = a_pLayer->m_Indices[current];
            float xPos = static_cast<float>(x) - pattern.m_Width / 2.0f + 0.5f;
            float yPos = static_cast<float>(height - y - 1) + 0.5f;

            SetMapLayerTile(tile, xPos, yPos, a_Index);
        }
    }
}

void CPatternLoader::SetMapLayerTile(const short a_Tile, const float a_X, const float a_Y, const size_t a_Index)
{ 
    ETileType::Type type = GetTileType(a_Tile);

    if (type != ETileType::Invalid)
    {
        SPatternTile patternTile;
        patternTile.m_X = a_X;
        patternTile.m_Y = a_Y;
        patternTile.m_Type = type;

        InsertPatternTile(patternTile, a_Index);
    }
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

void CPatternLoader::SetObjectLayer(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index)
{
    if (a_pLayer->m_Name == StringGame)
    {
        SetPatternProperties(a_pLayer, a_Index);
        return;
    }

    for (size_t i = 0; i < a_pLayer->m_Objects.size(); ++i)
    {
        auto& objectProperty = a_pLayer->m_Objects[i];
        
        ETileType::Type type = GetTileType(objectProperty.m_GID);

        if (type != ETileType::Invalid)
        {
            int xPos = objectProperty.m_X / objectProperty.m_Width;
            int yPos = static_cast<int>(m_pPattern[a_Index].m_Height) - objectProperty.m_Y / objectProperty.m_Height;

            SPatternTile patternTile;
            patternTile.m_X = static_cast<float>(xPos) - m_pPattern[a_Index].m_Width / 2.0f + 0.5f;
            patternTile.m_Y = static_cast<float>(yPos) + 0.5f;
            patternTile.m_Type = type;

            InsertPatternTile(patternTile, a_Index);
        }
    }
}

void CPatternLoader::InsertPatternTile(const SPatternTile& a_rPatternTile, const size_t a_Index)
{
    CPattern& pattern = m_pPattern[a_Index];

    for (int i = pattern.m_Tiles.size() - 1; i >= 0; --i)
    {
        if (pattern.m_Tiles[i].m_Y <= a_rPatternTile.m_Y)
        {
            pattern.m_Tiles.insert(pattern.m_Tiles.begin() + i + 1, a_rPatternTile);
            return;
        }
    }

    pattern.m_Tiles.insert(pattern.m_Tiles.begin(), a_rPatternTile);
}

void CPatternLoader::SetPatternProperties(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index)
{
    CPattern& pattern = m_pPattern[a_Index];

    for (auto& prop : a_pLayer->Properties)
    {
        if (prop.first == StringDifficulty)
        {
            int difficulty = std::stoi(prop.second);
            pattern.m_Difficulty = difficulty;

            SetMinMaxDifficulty(difficulty);
        }

        else if (prop.first == StringPriority)
        {
            int priority = std::stoi(prop.second);
            pattern.m_Priority = priority;

            SetMinMaxPriority(priority);
        }
    }
}

void CPatternLoader::SetDefaultValues()
{
    std::vector<CPattern*> connectedPattern;

    for (size_t i = 0; i < m_PatternCount; ++i)
        connectedPattern.push_back(&m_pPattern[i]);

    for (size_t i = 0; i < m_PatternCount; ++i)
    {
        m_pPattern[i].m_ConnectedPattern = connectedPattern;
        m_pPattern[i].m_Difficulty = 0;
        m_pPattern[i].m_Priority = 0;
    }
}

void CPatternLoader::SetMinMaxDifficulty(const size_t a_Difficulty)
{
    if (m_HasSetDifficulty == false)
    {
        m_MinDifficulty = a_Difficulty;
        m_MaxDifficulty = a_Difficulty;
        m_HasSetDifficulty = true;
        return;
    }

    if (a_Difficulty < m_MinDifficulty)
        m_MinDifficulty = a_Difficulty;

    if (a_Difficulty > m_MaxDifficulty)
        m_MaxDifficulty = a_Difficulty;
}

void CPatternLoader::SetMinMaxPriority(const size_t a_Priority)
{
    if (m_HasSetPriority == false)
    {
        m_MinPriority = a_Priority;
        m_MaxPriority = a_Priority;
        m_HasSetPriority = true;
        return;
    }

    if (a_Priority < m_MinPriority)
        m_MinPriority = a_Priority;

    if (a_Priority > m_MaxPriority)
        m_MaxPriority = a_Priority;
}
