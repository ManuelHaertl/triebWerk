#pragma once
#include <CEngine.h>
#include <CPattern.h>

class CPatternLoader
{
private:
    const std::string StringGame = "Game";
    const std::string StringDifficulty = "Difficulty";
    const std::string StringPriority = "Priority";

    CPattern* m_pPattern;
    size_t m_PatternCount;

    size_t m_MinDifficulty;
    size_t m_MaxDifficulty;
    bool m_HasSetDifficulty;

    size_t m_MinPriority;
    size_t m_MaxPriority;
    bool m_HasSetPriority;

public:
    CPatternLoader();
    ~CPatternLoader();

    void LoadPattern();
    CPattern* GetPattern() const;
    size_t GetPatternCount() const;
    size_t GetMinDifficulty() const;
    size_t GetMaxDifficulty() const;
    size_t GetMinPriority() const;
    size_t GetMaxPriority() const;

private:
    void SetMapLayer(triebWerk::CMapLayer* const a_pLayer, const size_t a_Index);
    void SetMapLayerTile(const short a_Tile, const float a_X, const float a_Y, const size_t a_Index);
    ETileType::Type GetTileType(const short a_Tile) const;
    void SetObjectLayer(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index);
    void InsertPatternTile(const SPatternTile& a_rPatternTile, const size_t a_Index);
    void SetPatternProperties(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index);
    void SetDefaultValues();
    void SetMinMaxDifficulty(const size_t a_Difficulty);
    void SetMinMaxPriority(const size_t a_Priority);
};