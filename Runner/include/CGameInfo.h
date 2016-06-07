#pragma once
class CGameInfo
{
public:
    // current game scores
    int m_Difficulty;
    float m_TotalPoints;
    float m_CurrentPoints;
    float m_Multiplier;

    // const values
    float m_PointsPerMeter;
    float m_AddedMultiplier;
    float m_HighestMultiplier;

public:
    CGameInfo();
    ~CGameInfo();

    static CGameInfo& Instance();
    void Reset();
};