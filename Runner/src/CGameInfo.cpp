#include <CGameInfo.h>

CGameInfo::CGameInfo()
    : m_FlyStandardSpeed(60.0f)
    , m_FlyDifficultySpeed(0.0f)
    , m_FlyBoostSpeed(0.0f)
    , m_Difficulty(1)
    , m_TotalPoints(0.0f)
    , m_CurrentPoints(0.0f)
    , m_Multiplier(1.0f)
    , m_PlayerPosition(0.0f)
    , m_EffectCheckpoint(false)
    , m_EffectDodge(false)
    , m_EffectDodgeStrength(1.0f)
	, m_EffectShield(false)
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
    m_EffectCheckpoint = false;
    m_EffectDodge = false;
    m_EffectDodgeStrength = 1.0f;
}