#pragma once
#include <vector>
#include <SPatternTile.h>

class CPattern
{
public:
    size_t m_Priority;
    size_t m_Difficulty;
    float m_Width;
    float m_Height;

    std::vector<SPatternTile> m_Tiles;
    std::vector<CPattern*> m_ConnectedPattern;

    std::vector<size_t> m_Difficulties;
    std::vector<std::vector<size_t>> m_Priorities;
    std::vector<std::vector<CPattern*>> m_ConnectedDifficulty;

public:
    CPattern();
    ~CPattern();
};