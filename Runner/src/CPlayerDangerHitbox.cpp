#include <CPlayerDangerHitbox.h>

CPlayerDangerHitbox::CPlayerDangerHitbox()
{
}

CPlayerDangerHitbox::~CPlayerDangerHitbox()
{
}

void CPlayerDangerHitbox::Start()
{
}

void CPlayerDangerHitbox::Update()
{
}

void CPlayerDangerHitbox::End()
{
}

void CPlayerDangerHitbox::CollisionEnter(triebWerk::CCollisionEvent a_Collision)
{

	if (a_Collision.m_pPartner->m_Tag.HasTag("Death"))
	{

		//a_Collision.m_pPartner.
	}
		
}
