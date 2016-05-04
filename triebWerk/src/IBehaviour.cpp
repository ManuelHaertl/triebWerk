#include <IBehaviour.h>

triebWerk::IBehaviour::IBehaviour() :
    m_pEntity(nullptr)
{
}

triebWerk::IBehaviour::~IBehaviour()
{
}

void triebWerk::IBehaviour::Start()
{
}

void triebWerk::IBehaviour::Update()
{
}

void triebWerk::IBehaviour::LateUpdate()
{
}

void triebWerk::IBehaviour::End()
{
}

void triebWerk::IBehaviour::CollisionEnter(CCollisionEvent a_Collision)
{
}

void triebWerk::IBehaviour::CollisionStay(CCollisionEvent a_Collision)
{
}

void triebWerk::IBehaviour::CollisionLeave(CCollisionEvent a_Collision)
{
}
