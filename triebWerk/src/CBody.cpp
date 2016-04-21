#include <CBody.h>

triebWerk::CBody::CBody() :
    m_pTransform(nullptr),
    m_Mass(1.0f),
    m_GravityFactor(1.0f),
    m_MassInverse(1.0f)
{
}

triebWerk::CBody::~CBody()
{
    m_Velocity = DirectX::XMVectorZero();
}

void triebWerk::CBody::ApplyImpulse(const DirectX::XMVECTOR& a_rImpulse)
{
    m_Velocity = DirectX::XMVectorAdd(
        m_Velocity,
        DirectX::XMVectorScale(a_rImpulse, m_MassInverse));
}

void triebWerk::CBody::SetMass(const float a_Mass)
{
    m_Mass = a_Mass;

    if (a_Mass != 0.0f)
        m_MassInverse = 1.0f / a_Mass;

    else
        m_MassInverse = 0.0f;
}
