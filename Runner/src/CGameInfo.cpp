#include <CGameInfo.h>

CGameInfo::CGameInfo() :
    m_Difficulty(1),
    m_TotalPoints(0.0f),
    m_CurrentPoints(0.0f),
    m_Multiplier(1.0f),
    m_PointsPerMeter(0.5f),
    m_AddedMultiplier(0.5f),
    m_HighestMultiplier(5.0f)
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
    m_Difficulty = 1;
    m_TotalPoints = 0;
    m_CurrentPoints = 0;
    m_Multiplier = 1.0f;
}
