#include <CGameInfo.h>

CGameInfo::CGameInfo()
	: m_FlyStandardSpeed(60.0f)
	, m_FlyDifficultySpeed(0.0f)
	, m_FlyBoostSpeed(0.0f)
	, m_Difficulty(1)
	, m_TotalPoints(0.0f)
	, m_CurrentPoints(0.0f)
	, m_Multiplier(1.0f)
	, m_PlayerPositionZ(0.0f)
	, m_EffectCheckpointCollected(false)
	, m_EffectCheckpointPassed(false)
	, m_EffectFullControl(false)
	, m_EffectFullControlStrength(1.0f)
    , m_EffectGoingIntoGame(false)
    , m_IsGamePaused(false)
    , m_ChangeMenu(false)
    , m_Menu(EMenus::None)
{
    
}

CGameInfo::~CGameInfo()
{
}

CGameInfo& CGameInfo::Instance()
{
    static CGameInfo gameInfo;
    return gameInfo;
}

void CGameInfo::Reset()
{
    m_FlyDifficultySpeed = 0.0f;
    m_FlyBoostSpeed = 0.0f;
    m_Difficulty = 1;
    m_TotalPoints = 0;
    m_CurrentPoints = 0;
    m_Multiplier = 1.0f;
    m_EffectCheckpointCollected = false;
	m_EffectCheckpointPassed = false;
    m_EffectFullControl = false;
    m_EffectFullControlStrength = 1.0f;
    m_IsGamePaused = false;
    m_ChangeMenu = false;
}