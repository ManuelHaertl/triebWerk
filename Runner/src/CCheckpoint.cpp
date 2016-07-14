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
	m_pMaterial = &reinterpret_cast<triebWerk::CMeshDrawable*>(m_pEntity->GetDrawable())->m_Material;
}

void CCheckpoint::Update()
{
}

void CCheckpoint::End()
{
    if (!m_HasCollected)
    {
        CGameInfo& gameInfo = CGameInfo::Instance();
        gameInfo.m_Multiplier += AddedMultiplier;

        if (gameInfo.m_Multiplier > HighestMultiplier)
            gameInfo.m_Multiplier = HighestMultiplier;
    }
}
