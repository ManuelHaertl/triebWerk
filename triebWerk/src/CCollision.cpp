#include <CCollision.h>

triebWerk::CCollision::CCollision()
{
}

triebWerk::CCollision::~CCollision()
{
}

void triebWerk::CCollision::CheckCollision(ICollider* const a_pA, ICollider* const a_pB) const
{
    // don't perform a collision check if both collider are from the same physic entity
    if (a_pA->m_pEntity->GetPhysicEntity()->GetID() == a_pB->m_pEntity->GetPhysicEntity()->GetID())
        return;

    bool collisionHappened = false;

    // check which 2 collider types we have and then perform the right collision check
    switch (a_pA->GetColliderType())
    {
    case ECollider::AABB:
    {
        switch (a_pB->GetColliderType())
        {
        case ECollider::AABB:
            collisionHappened = AABBAndAABBTrigger((CAABBCollider*)a_pA, (CAABBCollider*)a_pB);
            break;
        case ECollider::Sphere:
            collisionHappened = AABBAndSphereTrigger((CAABBCollider*)a_pA, (CSphereCollider*)a_pB);
            break;
        }
        break;
    }
    case ECollider::Sphere:
    {
        switch (a_pB->GetColliderType())
        {
        case ECollider::AABB:
            collisionHappened = AABBAndSphereTrigger((CAABBCollider*)a_pB, (CSphereCollider*)a_pA);
            break;
        case ECollider::Sphere:
            collisionHappened = SphereAndSphereTrigger((CSphereCollider*)a_pA, (CSphereCollider*)a_pB);
            break;
        }
        break;
    }
    }

    if (collisionHappened)
    {
        // only gather collision event infos on those which shall do so
        if (a_pA->m_CheckCollision)
            Collided(a_pA, a_pB);
        if (a_pB->m_CheckCollision)
            Collided(a_pB, a_pA);
    }
}

bool triebWerk::CCollision::AABBAndAABBTrigger(CAABBCollider* const a_pA, CAABBCollider* a_pB) const
{
    CTransform& transA = a_pA->m_pEntity->m_Transform;
    CTransform& transB = a_pB->m_pEntity->m_Transform;

    // calculate the min and max positions including the entities position & scale
    DirectX::XMVECTOR aMin = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(a_pA->m_Min, transA.GetScale()), transA.GetPosition());
    DirectX::XMVECTOR aMax = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(a_pA->m_Max, transA.GetScale()), transA.GetPosition());

    DirectX::XMVECTOR bMin = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(a_pB->m_Min, transB.GetScale()), transB.GetPosition());
    DirectX::XMVECTOR bMax = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(a_pB->m_Max, transB.GetScale()), transB.GetPosition());

    // SAT test
    if (aMin.m128_f32[0] <= bMax.m128_f32[0] && aMax.m128_f32[0] >= bMin.m128_f32[0] &&
        aMin.m128_f32[1] <= bMax.m128_f32[1] && aMax.m128_f32[1] >= bMin.m128_f32[1] &&
        aMin.m128_f32[2] <= bMax.m128_f32[2] && aMax.m128_f32[2] >= bMin.m128_f32[2])
    {
        return true;
    }

    return false;
}

bool triebWerk::CCollision::SphereAndSphereTrigger(CSphereCollider* const a_pA, CSphereCollider* const a_pB) const
{
    CTransform& transA = a_pA->m_pEntity->m_Transform;
    CTransform& transB = a_pB->m_pEntity->m_Transform;

    // the minimum squared distance the spheres need to have to collide
    float radiusSquared = powf(a_pA->m_Radius + a_pB->m_Radius, 2);
    
    // the squared distance between the two spheres
    DirectX::XMVECTOR sub = DirectX::XMVectorSubtract(transA.GetPosition(), transB.GetPosition());
    float lengthSquared = DirectX::XMVector3LengthSq(sub).m128_f32[0];

    return lengthSquared <= radiusSquared;
}

bool triebWerk::CCollision::AABBAndSphereTrigger(CAABBCollider * const a_pA, CSphereCollider * const a_pB) const
{
    CTransform& transA = a_pA->m_pEntity->m_Transform;
    CTransform& transB = a_pB->m_pEntity->m_Transform;

    // calculate the min and max positions including the entities position & scale
    DirectX::XMVECTOR aMin = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(a_pA->m_Min, transA.GetScale()), transA.GetPosition());
    DirectX::XMVECTOR aMax = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(a_pA->m_Max, transA.GetScale()), transA.GetPosition());

    DirectX::XMVECTOR closestPointInAABB = DirectX::XMVectorMin(DirectX::XMVectorMax(transB.GetPosition(), aMin), aMax);
    
    DirectX::XMVECTOR sub = DirectX::XMVectorSubtract(closestPointInAABB, transB.GetPosition());
    float lengthSquared = DirectX::XMVector3LengthSq(sub).m128_f32[0];

    return lengthSquared < (a_pB->m_Radius * a_pB->m_Radius);
}

void triebWerk::CCollision::Collided(ICollider* const a_pA, ICollider* const a_pB) const
{
    // check if there has been a collision
    for (size_t i = 0; i < a_pA->m_CollisionEvents.size(); ++i)
    {
        if (a_pA->m_CollisionEvents[i].m_pPartner == a_pB->m_pEntity)
        {
            a_pA->m_CollisionEvents[i].m_CollisionState = ECollisionState::Stay;
            a_pA->m_CollisionEvents[i].m_Updated = true;
            return;
        }
    }

    // there hasn't been a collision before, so add an enter state
    CCollisionEvent collisionEvent;
    collisionEvent.m_CollisionState = ECollisionState::Enter;
    collisionEvent.m_pPartner = a_pB->m_pEntity;
    collisionEvent.m_Updated = true;
    a_pA->m_CollisionEvents.push_back(collisionEvent);
}
