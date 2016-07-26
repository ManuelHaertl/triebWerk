#pragma once
#include <CEngine.h>

class CCheckpoint : public triebWerk::IBehaviour
{
public:
    static float AddedMultiplier;
    static float HighestMultiplier;

	bool m_HasCollected;
	float m_RotationModifier;
	float m_Counter = 1.0f;
	triebWerk::CMaterial* m_pMaterial;

	triebWerk::CEntity* m_pCheckpointPlaneButtom;
	triebWerk::CEntity* m_pCheckpointPlaneMiddle;
	triebWerk::CEntity* m_pCheckpointPlaneTop;
	triebWerk::CEntity* m_pGodrayButtom;

public:
    CCheckpoint();
    ~CCheckpoint();

	void Collected();

    void Start();
    void Update();
    void End();
};