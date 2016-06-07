#include <CCheckpoint.h>

#include <CGameInfo.h>

CCheckpoint::CCheckpoint() :
    m_HasCollected(false)
{
}

CCheckpoint::~CCheckpoint()
{
}

void CCheckpoint::Start()
{
}

void CCheckpoint::Update()
{
}

void CCheckpoint::End()
{
    if (!m_HasCollected)
    {
        CGameInfo& gameInfo = CGameInfo::Instance();
        gameInfo.m_Multiplier += gameInfo.m_AddedMultiplier;
    }
}
