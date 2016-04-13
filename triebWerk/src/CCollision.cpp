#include <CCollision.h>

triebWerk::CCollision::CCollision()
{
}

triebWerk::CCollision::~CCollision()
{
}

void triebWerk::CCollision::CheckCollision(ICollider* a_pA, ICollider* a_pB)
{
    // don't perform a collision check if both collider are from the same physic entity
    if (a_pA->GetID() == a_pB->GetID())
        return;

    CAABBCollider* a = (CAABBCollider*)a_pA;
    CAABBCollider* b = (CAABBCollider*)a_pB;
    
    AABBAndAABB(a, b);
}

void triebWerk::CCollision::SolveAllCollisions()
{
}

void triebWerk::CCollision::AABBAndAABB(CAABBCollider* a_pA, CAABBCollider* a_pB)
{
    DirectX::XMVECTOR aMin = DirectX::XMVectorAdd(a_pA->m_Min, a_pA->m_pTransform->GetPosition());
    DirectX::XMVECTOR aMax = DirectX::XMVectorAdd(a_pA->m_Max, a_pA->m_pTransform->GetPosition());

    DirectX::XMVECTOR bMin = DirectX::XMVectorAdd(a_pB->m_Min, a_pB->m_pTransform->GetPosition());
    DirectX::XMVECTOR bMax = DirectX::XMVectorAdd(a_pB->m_Max, a_pB->m_pTransform->GetPosition());

    if (aMin.m128_f32[0] <= bMax.m128_f32[0] && aMax.m128_f32[0] >= bMin.m128_f32[0] &&
        aMin.m128_f32[1] <= bMax.m128_f32[1] && aMax.m128_f32[1] >= bMin.m128_f32[1] &&
        aMin.m128_f32[2] <= bMax.m128_f32[2] && aMax.m128_f32[2] >= bMin.m128_f32[2])
    {
        // collision happened
    }
}
