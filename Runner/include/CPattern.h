#pragma once
#include <vector>
#include <SPatternTile.h>

class CPattern
{
public:
    size_t m_Priority;
    size_t m_Difficulty;
    std::vector<CPattern*> m_ConnectedPattern;
    std::vector<SPatternTile> m_Tiles;

public:
    CPattern();
    ~CPattern();
};