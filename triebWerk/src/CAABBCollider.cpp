#include <CAABBCollider.h>

triebWerk::CAABBCollider::CAABBCollider()
{
    m_Min = DirectX::XMVectorZero();
    m_Max = DirectX::XMVectorZero();
}

triebWerk::CAABBCollider::~CAABBCollider()
{
}

triebWerk::ECollider::Type triebWerk::CAABBCollider::GetColliderType()
{
    return ECollider::Type::AABB;
}

void triebWerk::CAABBCollider::CreateFromMesh(CMesh* a_pMesh)
{
    m_Min = DirectX::XMVectorSet(-0.5, -0.5f, -0.5f, 0.0f);
    m_Max = DirectX::XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
}
