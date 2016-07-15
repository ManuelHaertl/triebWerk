#include <CGameInfo.h>

CGameInfo::CGameInfo()
    : m_Difficulty(1)
    , m_TotalPoints(0.0f)
    , m_CurrentPoints(0.0f)
    , m_Multiplier(1.0f)
    , m_PointsPerMeter(0.5f)
    , m_StartFlySpeed(60.0f)
    , m_EffectCheckpoint(false)
    , m_EffectDodge(false)
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
    m_FlySpeed = m_StartFlySpeed;
    m_Difficulty = 1;
    m_TotalPoints = 0;
    m_CurrentPoints = 0;
    m_Multiplier = 1.0f;
    m_EffectCheckpoint = false;
    m_EffectDodge = false;
}