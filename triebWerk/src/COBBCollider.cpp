#include <COBBCollider.h>
#include <CEntity.h>

triebWerk::COBBCollider::COBBCollider()
{
    m_Rotation = DirectX::XMMatrixIdentity();
    m_HalfWidths = DirectX::XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
    m_WorldHalfWidths = m_HalfWidths;
}

triebWerk::COBBCollider::~COBBCollider()
{
}

triebWerk::ECollider::Type triebWerk::COBBCollider::GetColliderType()
{
    return ECollider::OBB;
}

void triebWerk::COBBCollider::UpdateWorldCollider()
{
    m_Rotation = DirectX::XMMatrixRotationQuaternion(m_pEntity->m_Transform.GetRotation());
    m_WorldHalfWidths = DirectX::XMVectorMultiply(m_HalfWidths, m_pEntity->m_Transform.GetScale());
}

void triebWerk::COBBCollider::CreateFromVertices(const CMesh::SVertex* const a_pVertices, const size_t a_Count)
{
    if (a_Count > 0)
    {
        m_HalfWidths = DirectX::XMVectorZero();

        for (size_t i = 0; i < a_Count; ++i)
        {
            float x = std::fabsf(a_pVertices[i].position.x);
            float y = std::fabsf(a_pVertices[i].position.y);
            float z = std::fabsf(a_pVertices[i].position.z);

            if (x > m_HalfWidths.m128_f32[0]) m_HalfWidths.m128_f32[0] = x;
            if (y > m_HalfWidths.m128_f32[1]) m_HalfWidths.m128_f32[1] = y;
            if (z > m_HalfWidths.m128_f32[2]) m_HalfWidths.m128_f32[2] = z;
        }

        SafeUpdateWorldCollider();
    }
}

void triebWerk::COBBCollider::SetHalfWidths(const DirectX::XMVECTOR a_HalfWidths)
{
    m_HalfWidths = a_HalfWidths;

    SafeUpdateWorldCollider();
}

DirectX::XMMATRIX& triebWerk::COBBCollider::GetRotation()
{
    return m_Rotation;
}

DirectX::XMVECTOR& triebWerk::COBBCollider::GetHalfWidths()
{
    return m_HalfWidths;
}

DirectX::XMVECTOR & triebWerk::COBBCollider::GetWorldHalfWidths()
{
    return m_WorldHalfWidths;
}

void triebWerk::COBBCollider::SafeUpdateWorldCollider()
{
    if (m_pEntity != nullptr)
        UpdateWorldCollider();
    else
        m_WorldHalfWidths = m_HalfWidths;
}
