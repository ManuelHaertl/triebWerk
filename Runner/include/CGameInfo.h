#pragma once
class CGameInfo
{
public:
    // current game scores
    float m_FlySpeed;

    int m_Difficulty;
    float m_TotalPoints;
    float m_CurrentPoints;
    float m_Multiplier;

    // const values
    float m_PointsPerMeter;
    float m_StartFlySpeed;

private:
    CGameInfo();
    ~CGameInfo();

public:
    static CGameInfo& Instance();
    void Reset();
};