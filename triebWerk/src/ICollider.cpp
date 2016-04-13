#include <ICollider.h>

triebWerk::ICollider::ICollider() :
    m_CheckCollision(true),
    m_IsTrigger(false),
    m_pTransform(nullptr),
    m_pBody(nullptr),
    m_ID(0)
{
}

triebWerk::ICollider::~ICollider()
{
}

size_t triebWerk::ICollider::GetID() const
{
    return m_ID;
}

void triebWerk::ICollider::SetID(const size_t a_ID)
{
    m_ID = a_ID;
}
