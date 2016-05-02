#include <CPatternLoader.h>

CPatternLoader::CPatternLoader() :
    m_pPattern(nullptr),
    m_PatternCount(0),
    m_MinDifficulty(0),
    m_MaxDifficulty(0)
{
    
}

CPatternLoader::~CPatternLoader()
{
    
}

void CPatternLoader::LoadPattern()
{
    if (m_pPattern != nullptr)
        delete[] m_pPattern;

    auto tilesets = twResourceManager->GetAllTilesets();

    m_PatternCount = tilesets.size();
    m_pPattern = new CPattern[m_PatternCount];

    SetDefaultValues();

    for (size_t i = 0; i < m_PatternCount; ++i)
    {
        auto& tileset = *tilesets[i];

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

void CPatternLoader::SetMapLayer(triebWerk::CMapLayer* const a_pLayer, const size_t a_Index)
{
    CPattern& pattern = m_pPattern[a_Index];
    size_t width = static_cast<size_t>(a_pLayer->m_LayerWidth);
    size_t height = static_cast<size_t>(a_pLayer->m_LayerHeight);

    for (size_t x = 0; x < width; ++x)
    {
        for (size_t y = 0; y < height; ++y)
        {
            size_t current = x * width + y;

            short tile = a_pLayer->m_Indices[current];
        }
    }
}

void CPatternLoader::SetObjectLayer(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index)
{
    if (a_pLayer->m_Name == StringGame)
    {
        SetPatternProperties(a_pLayer, a_Index);
        return;
    }
}

void CPatternLoader::SetPatternProperties(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index)
{
    CPattern& pattern = m_pPattern[a_Index];
    
    // TO DO
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
