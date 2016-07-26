#pragma once
class CGameInfo
{
public:
    // Current game scores
    float m_FlyStandardSpeed;
    float m_FlyDifficultySpeed;
    float m_FlyBoostSpeed;

    int m_Difficulty;
    float m_TotalPoints;
    float m_CurrentPoints;
    float m_Multiplier;

    // Player Information
    float m_PlayerPosition;

    // Effect Information
    bool m_EffectCheckpoint;
    bool m_EffectFullControl;
    float m_EffectFullControlStrength;
	bool m_EffectShield;
    bool m_EffectBoost;

private:
    CGameInfo();
    ~CGameInfo();

public:
    static CGameInfo& Instance();
    void Reset();
};