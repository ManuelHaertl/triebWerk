#include <ICollider.h>

triebWerk::ICollider::ICollider() :
    m_CheckCollision(true),
    m_pEntity(nullptr)
{
}

triebWerk::ICollider::~ICollider()
{
}