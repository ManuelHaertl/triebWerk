#pragma once
#include <CEngine.h>

class CCheckpoint : public triebWerk::IBehaviour
{
public:
    static float AddedMultiplier;
    static float HighestMultiplier;

	bool m_HasCollected;
	bool m_Deleted;
	float m_RotationModifier;
	float m_Counter = 1.0f;
	triebWerk::CMaterial* m_pMaterial;

	triebWerk::CEntity* m_pCheckpointPlaneButtom;
	triebWerk::CEntity* m_pCheckpointPlaneMiddle;
	triebWerk::CEntity* m_pCheckpointPlaneTop;
	triebWerk::CEntity* m_pGodrayButtom;

	triebWerk::CSound* m_pCollectSound;
	triebWerk::CSound* m_pPassSound;
	triebWerk::CSound* m_pFullMultiplierSound;

public:
    CCheckpoint();
    ~CCheckpoint();

	void Collected();

    void Start();
    void Update();
    void End();
};