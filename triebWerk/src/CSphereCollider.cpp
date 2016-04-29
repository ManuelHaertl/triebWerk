#include <CSphereCollider.h>
#include <CEntity.h>

triebWerk::CSphereCollider::CSphereCollider() :
    m_Radius(1.0f),
    m_WorldRadius(1.0f)
{
}

triebWerk::CSphereCollider::~CSphereCollider()
{
}

triebWerk::ECollider::Type triebWerk::CSphereCollider::GetColliderType()
{
    return ECollider::Sphere;
}

void triebWerk::CSphereCollider::UpdateWorldCollider()
{
    DirectX::XMVECTOR scale = m_pEntity->m_Transform.GetScale();

    // get the highest scale coordinate
    float sphereScale = scale.m128_f32[0];
    if (scale.m128_f32[1] > sphereScale)
        sphereScale = scale.m128_f32[1];
    if (scale.m128_f32[2] > sphereScale)
        sphereScale = scale.m128_f32[2];

    m_WorldRadius = m_Radius * sphereScale;
}

void triebWerk::CSphereCollider::CreateFromVertices(const CMesh::SVertex* const a_pVertices, const size_t a_Count)
{
    m_Radius = 0.0f;

    for (size_t i = 0; i < a_Count; ++i)
    {
        // calculate the length of a vertex
        DirectX::XMVECTOR vertex = DirectX::XMVectorSet(a_pVertices[i].position.x, a_pVertices[i].position.y, a_pVertices[i].position.z, 0.0f);
        float length = DirectX::XMVector3Length(vertex).m128_f32[0];

        if (length > m_Radius)
            m_Radius = length;
    }

    SafeUpdateWorldCollider();
}

void triebWerk::CSphereCollider::SetRadius(const float a_Radius)
{
    m_Radius = a_Radius;

    SafeUpdateWorldCollider();
}

float triebWerk::CSphereCollider::GetRadius() const
{
    return m_Radius;
}

float triebWerk::CSphereCollider::GetWorldRadius() const
{
    return m_WorldRadius;
}

void triebWerk::CSphereCollider::SafeUpdateWorldCollider()
{
    if (m_pEntity != nullptr)
        UpdateWorldCollider();
    else
        m_WorldRadius = m_Radius;
}
