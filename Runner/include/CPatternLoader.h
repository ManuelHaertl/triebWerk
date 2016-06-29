#pragma once
#include <CEngine.h>
#include <CPattern.h>

class CPatternLoader
{
private:
    const std::string StringGame = "Game";
    const std::string StringDifficulty = "Difficulty";
    const std::string StringPriority = "Priority";
    const std::string StringFollowing = "Following";
    const std::string StringCategory = "Category";
    const std::string StringCategorySingle = "Single";
    const std::string StringCategoryTwice = "Twice";
    const std::string StringCategoryVary = "Vary";

    std::vector<CPattern*> m_AllPattern;
    std::vector<CPattern*> m_CategoriesPattern[CPattern::MaxCategories];

public:
    CPatternLoader();
    ~CPatternLoader();

    void LoadPattern(std::vector<CPattern*>(&a_pPattern)[CPattern::MaxDifficulty]);

private:
    void SetMapLayer(triebWerk::CMapLayer* const a_pLayer, CPattern* a_pPattern);
    void SetObjectLayer(triebWerk::CObjectLayer* const a_pLayer, CPattern* a_pPattern);
    void SetTile(const ETileType::Type a_Type, const float a_X, const float a_Y, CPattern* a_pPattern);
    void InsertPatternTile(const SPatternTile& a_rPatternTile, CPattern* a_pPattern);
    ETileType::Type GetTileType(const short a_Tile) const;
    ETileType::Type GetModelTileType(const int a_ModelWidth, const int a_ModelHeight) const;
    void SetPatternProperties(triebWerk::CObjectLayer* const a_pLayer, CPattern* a_pPattern);

    void SetConnectedPattern();
    void AddPriority(std::vector<size_t>& a_Priorities, const size_t a_Priority);
};