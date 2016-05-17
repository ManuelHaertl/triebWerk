#pragma once
#include <vector>
#include <SPatternTile.h>

class CPattern
{
public:
    static const size_t MaxDifficulty = 5;
    static const size_t MaxPriorities = 10;

    size_t m_Priority;
    size_t m_Difficulty;
    float m_Width;
    float m_Height;

    std::vector<SPatternTile> m_Tiles;
    std::vector<CPattern*> m_ConnectedPattern[MaxDifficulty][MaxPriorities];
    std::vector<size_t> m_Priorities[MaxDifficulty];

public:
    CPattern();
    ~CPattern();
};