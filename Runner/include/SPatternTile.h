#pragma once
#include <ETileType.h>

struct SPatternTile
{
    enum EMovingDirection
    {
        None = 0,
        Up = 1,
        Down = 2,
        Left = 3,
        Right = 4,
        Air = 5,
        To = 6,
        Back = 7
    };

    ETileType::Type m_Type;
    float m_X;
    float m_Y;
    EMovingDirection m_Moving;
    float m_Distance;
    float m_PosXEnd;
    float m_PosYStart;
    float m_PosYEnd;
    float m_PosZEnd;
    float m_Time;

    SPatternTile()
        : m_Type()
        , m_X(0.0f)
        , m_Y(0.0f)
        , m_Moving(EMovingDirection::None)
        , m_Distance(0.0f)
        , m_PosXEnd(0.0f)
        , m_PosYStart(0.0f)
        , m_PosYEnd(0.0f)
        , m_PosZEnd(0.0f)
        , m_Time(0.0f)
    {

    }
};