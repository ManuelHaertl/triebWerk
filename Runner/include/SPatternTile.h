#pragma once
#include <ETileType.h>

struct SPatternTile
{
    ETileType::Type m_Type;
    float m_X;
    float m_Y;
    bool m_Moving;
    float m_Distance;
    float m_PosStart;
    float m_PosEnd;
    float m_Time;

    SPatternTile()
        : m_Type()
        , m_X(0.0f)
        , m_Y(0.0f)
        , m_Moving(false)
        , m_Distance(0.0f)
        , m_PosStart(0.0f)
        , m_PosEnd(0.0f)
        , m_Time(0.0f)
    {

    }
};