#pragma once
#include <CEngine.h>
#include <CPattern.h>

class CPatternLoader
{
private:
    const std::string StringGame = "Game";

    CPattern* m_pPattern;
    size_t m_PatternCount;
    size_t m_MinDifficulty;
    size_t m_MaxDifficulty;

public:
    CPatternLoader();
    ~CPatternLoader();

    void LoadPattern();
    CPattern* GetPattern() const;
    size_t GetPatternCount() const;
    size_t GetMinDifficulty() const;
    size_t GetMaxDifficulty() const;

private:
    void SetMapLayer(triebWerk::CMapLayer* const a_pLayer, const size_t a_Index);
    void SetObjectLayer(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index);
    void SetPatternProperties(triebWerk::CObjectLayer* const a_pLayer, const size_t a_Index);
    void SetDefaultValues();
};