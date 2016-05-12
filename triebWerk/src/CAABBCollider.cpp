#include "..\include\CAABBCollider.h"
#include "..\include\CAABBCollider.h"
#include <CAABBCollider.h>
#include <CEntity.h>

triebWerk::CAABBCollider::CAABBCollider()
{
    m_Min = DirectX::XMVectorSet(-0.5f, -0.5f, -0.5f, 0.0f);
    m_Max = DirectX::XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
    m_WorldMin = DirectX::XMVectorSet(-0.5f, -0.5f, -0.5f, 0.0f);
    m_WorldMax = DirectX::XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
}

triebWerk::CAABBCollider::~CAABBCollider()
{
}

triebWerk::ECollider::Type triebWerk::CAABBCollider::GetColliderType()
{
    return ECollider::Type::AABB;
}

void triebWerk::CAABBCollider::UpdateWorldCollider()
{
    DirectX::XMVECTOR position = m_pEntity->m_Transform.GetPosition();
    DirectX::XMVECTOR scale = m_pEntity->m_Transform.GetScale();

    m_WorldMin = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(m_Min, scale), position);
    m_WorldMax = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(m_Max, scale), position);
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

        SafeUpdateWorldCollider();
    }
}

void triebWerk::CAABBCollider::SetMin(const DirectX::XMVECTOR a_Min)
{
    m_Min = a_Min;

    SafeUpdateWorldCollider();
}

void triebWerk::CAABBCollider::SetMax(const DirectX::XMVECTOR a_Max)
{
    m_Max = a_Max;

    SafeUpdateWorldCollider();
}

void triebWerk::CAABBCollider::SetSize(const DirectX::XMVECTOR a_Size)
{
    SetSize(a_Size.m128_f32[0], a_Size.m128_f32[1], a_Size.m128_f32[2]);
}

void triebWerk::CAABBCollider::SetSize(const float a_X, const float a_Y, const float a_Z)
{
    float xHalf = a_X / 2.0f;
    float yHalf = a_Y / 2.0f;
    float zHalf = a_Z / 2.0f;

    m_Min.m128_f32[0] = -xHalf;
    m_Min.m128_f32[1] = -yHalf;
    m_Min.m128_f32[2] = -zHalf;

    m_Max.m128_f32[0] = xHalf;
    m_Max.m128_f32[1] = yHalf;
    m_Max.m128_f32[2] = zHalf;

    SafeUpdateWorldCollider();
}

DirectX::XMVECTOR& triebWerk::CAABBCollider::GetMin()
{
    return m_Min;
}

DirectX::XMVECTOR& triebWerk::CAABBCollider::GetMax()
{
    return m_Max;
}

DirectX::XMVECTOR& triebWerk::CAABBCollider::GetWorldMin()
{
    return m_WorldMin;
}

DirectX::XMVECTOR& triebWerk::CAABBCollider::GetWorldMax()
{
    return m_WorldMax;
}

void triebWerk::CAABBCollider::SafeUpdateWorldCollider()
{
    if (m_pEntity != nullptr)
    {
        UpdateWorldCollider();
    }
    else
    {
        m_WorldMin = m_Min;
        m_WorldMax = m_Max;
    }
}
