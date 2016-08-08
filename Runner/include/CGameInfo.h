#pragma once
#include <CHighscore.h>
#include <EMenus.h>

class CGameInfo
{
public:
    // Current game scores
    CHighscore m_Highscore;
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
    bool m_IsPlayerDead;

    // Effect Information
    bool m_EffectCheckpointCollected;
	bool m_EffectCheckpointPassed;
    bool m_EffectFullControl;
    float m_EffectFullControlStrength;
    bool m_EffectBoost;
    bool m_EffectGoingIntoGame;
    bool m_EffectTryAgain;

    // UI Information
    bool m_IsGamePaused;
    bool m_ChangeMenu;
    EMenus m_Menu;
    bool m_RestartGame;

private:
    CGameInfo();
    ~CGameInfo();

public:
    static CGameInfo& Instance();
    void Reset();
};