#pragma once
#include <string>
#include <vector>
#include <SPatternTile.h>
#include <EPatternCategories.h>

class CPattern
{
public:
    static const size_t MaxDifficulty = 6;
    static const size_t MaxPriorities = 4;
    static const size_t MaxCategories = 3;

    size_t m_Priority;
    size_t m_Difficulty;
    float m_Width;
    float m_Height;

    EPatternCategories::Type m_Category;
    bool m_ConnectedCategories[MaxCategories];

    std::vector<SPatternTile> m_Tiles;
    std::vector<CPattern*> m_ConnectedPattern[MaxDifficulty][MaxPriorities];
    std::vector<size_t> m_Priorities[MaxDifficulty];

    std::string m_Name;

public:
    CPattern();
    ~CPattern();
};