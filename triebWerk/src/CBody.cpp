#include <CBody.h>

triebWerk::CBody::CBody() :
    m_Mass(1.0f),
    m_Drag(0.0f),
    m_GravityFactor(1.0f),
    m_MassInverse(0.0f)
{
    m_Velocity.x = 0.0f;
    m_Velocity.y = 0.0f;
    m_Velocity.z = 0.0f;
}

triebWerk::CBody::~CBody()
{
}
