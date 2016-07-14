#pragma once
class CGameInfo
{
public:
    // Current game scores
    float m_FlySpeed;

    int m_Difficulty;
    float m_TotalPoints;
    float m_CurrentPoints;
    float m_Multiplier;

    // Const values
    float m_PointsPerMeter;
    float m_StartFlySpeed;

    // Effect Information
    bool m_EffectCheckpoint;
    bool m_EffectDodge;

private:
    CGameInfo();
    ~CGameInfo();

public:
    static CGameInfo& Instance();
    void Reset();
};