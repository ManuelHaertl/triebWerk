#pragma once
#include <CEngine.h>

class CPlayerDangerHitbox : public triebWerk::IBehaviour
{
public:
	CPlayerDangerHitbox();
	~CPlayerDangerHitbox();

public:
	void Start();
	void Update();
	void End();

	void CollisionEnter(triebWerk::CCollisionEvent a_Collision) final;

};