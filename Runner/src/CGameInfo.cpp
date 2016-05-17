#include <CGameInfo.h>

CGameInfo::CGameInfo()
{
    m_Difficulty = 1;
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
}
