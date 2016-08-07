#pragma once
#include <EMenus.h>

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
	float m_PlayerPositionX;
    float m_PlayerPositionZ;
    float m_PlayerResourcePercentage;

    // Effect Information
    bool m_EffectCheckpointCollected;
	bool m_EffectCheckpointPassed;
    bool m_EffectFullControl;
    float m_EffectFullControlStrength;
    bool m_EffectBoost;
    bool m_EffectGoingIntoGame;

    // UI Information
    bool m_IsGamePaused;
    bool m_ChangeMenu;
    EMenus m_Menu;

private:
    CGameInfo();
    ~CGameInfo();

public:
    static CGameInfo& Instance();
    void Reset();
};