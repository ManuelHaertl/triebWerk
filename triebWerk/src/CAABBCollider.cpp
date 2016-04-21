#include <CAABBCollider.h>

triebWerk::CAABBCollider::CAABBCollider()
{
    m_Min = DirectX::XMVectorSet(-0.5f, -0.5f, -0.5f, 0.0f);
    m_Max = DirectX::XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
}

triebWerk::CAABBCollider::~CAABBCollider()
{
}

triebWerk::ECollider::Type triebWerk::CAABBCollider::GetColliderType()
{
    return ECollider::Type::AABB;
}

void triebWerk::CAABBCollider::CreateFromVertices(const CMesh::SVertex* const a_pVertices, const size_t a_Count)
{
    if (a_Count > 0)
    {
        m_Min = DirectX::XMVectorZero();
        m_Max = DirectX::XMVectorZero();

        for (size_t i = 0; i < a_Count; ++i)
        {
            CMesh::SVertex vertex = a_pVertices[i];

            if (vertex.position.x < m_Min.m128_f32[0]) m_Min.m128_f32[0] = vertex.position.x;
            if (vertex.position.y < m_Min.m128_f32[1]) m_Min.m128_f32[1] = vertex.position.y;
            if (vertex.position.z < m_Min.m128_f32[2]) m_Min.m128_f32[2] = vertex.position.z;

            if (vertex.position.x > m_Max.m128_f32[0]) m_Max.m128_f32[0] = vertex.position.x;
            if (vertex.position.y > m_Max.m128_f32[1]) m_Max.m128_f32[1] = vertex.position.y;
            if (vertex.position.z > m_Max.m128_f32[2]) m_Max.m128_f32[2] = vertex.position.z;
        }
    }
}
