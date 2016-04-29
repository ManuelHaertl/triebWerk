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
        case ECollider::OBB:
            collisionHappened = AABBAndOBBTrigger((CAABBCollider*)a_pA, (COBBCollider*)a_pB);
            break;
        case ECollider::Sphere:
            collisionHappened = AABBAndSphereTrigger((CAABBCollider*)a_pA, (CSphereCollider*)a_pB);
            break;
        }
        break;
    }
    case ECollider::OBB:
    {
        switch (a_pB->GetColliderType())
        {
        case ECollider::AABB:
            collisionHappened = AABBAndOBBTrigger((CAABBCollider*)a_pB, (COBBCollider*)a_pA);
            break;
        case ECollider::OBB:
            collisionHappened = OBBAndOBBTrigger((COBBCollider*)a_pA, (COBBCollider*)a_pB);
            break;
        case ECollider::Sphere:
            collisionHappened = SphereAndOBBTrigger((CSphereCollider*)a_pB, (COBBCollider*)a_pA);
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
        case ECollider::OBB:
            collisionHappened = SphereAndOBBTrigger((CSphereCollider*)a_pA, (COBBCollider*)a_pB);
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
    DirectX::XMVECTOR aMin = a_pA->GetWorldMin();
    DirectX::XMVECTOR aMax = a_pA->GetWorldMax();
    DirectX::XMVECTOR bMin = a_pB->GetWorldMin();
    DirectX::XMVECTOR bMax = a_pB->GetWorldMax();

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
    float radiusSquared = powf(a_pA->GetWorldRadius() + a_pB->GetWorldRadius(), 2);
    
    // the squared distance between the two spheres
    DirectX::XMVECTOR sub = DirectX::XMVectorSubtract(transA.GetPosition(), transB.GetPosition());
    float lengthSquared = DirectX::XMVector3LengthSq(sub).m128_f32[0];

    return lengthSquared <= radiusSquared;
}

bool triebWerk::CCollision::OBBAndOBBTrigger(COBBCollider* const a_pA, COBBCollider* const a_pB) const
{
    DirectX::XMMATRIX au = a_pA->GetRotation();
    DirectX::XMMATRIX bu = a_pB->GetRotation();

    DirectX::XMVECTOR ae = a_pA->GetWorldHalfWidths();
    DirectX::XMVECTOR be = a_pB->GetWorldHalfWidths();

    DirectX::XMVECTOR ac = a_pA->m_pEntity->m_Transform.GetPosition();
    DirectX::XMVECTOR bc = a_pB->m_pEntity->m_Transform.GetPosition();

    float ra, rb;
    DirectX::XMFLOAT3X3 R, AbsR;

    // Compute rotation matrix expressing b in a’s coordinate frame
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            R.m[i][j] = DirectX::XMVector3Dot(au.r[i], bu.r[j]).m128_f32[0];

    // Compute translation vector t
    DirectX::XMVECTOR t = DirectX::XMVectorSubtract(bc, ac);

    // Bring translation into a’s coordinate frame
    t = DirectX::XMVectorSet(
        DirectX::XMVector3Dot(t, au.r[0]).m128_f32[0],
        DirectX::XMVector3Dot(t, au.r[1]).m128_f32[0],
        DirectX::XMVector3Dot(t, au.r[2]).m128_f32[0],
        0.0f);

    // Compute common subexpressions. Add in an epsilon term to
    // counteract arithmetic errors when two edges are parallel and
    // their cross product is (near) null
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            AbsR.m[i][j] = std::fabsf(R.m[i][j]) + std::numeric_limits<float>::epsilon();

    // Test axes L = A0, L = A1, L = A2
    for (int i = 0; i < 3; ++i)
    {
        ra = ae.m128_f32[i];
        rb = be.m128_f32[0] * AbsR.m[i][0] + be.m128_f32[1] * AbsR.m[i][1] + be.m128_f32[2] * AbsR.m[i][2];
        if (std::fabsf(t.m128_f32[i]) > ra + rb)
            return false;
    }

    // Test axes L = B0, L = B1, L = B2
    for (int i = 0; i < 3; ++i)
    {
        ra = ae.m128_f32[0] * AbsR.m[0][i] + ae.m128_f32[1] * AbsR.m[1][i] + ae.m128_f32[2] * AbsR.m[2][i];
        rb = be.m128_f32[i];
        if (std::fabsf(t.m128_f32[0] * R.m[0][i] + t.m128_f32[1] * R.m[1][i] + t.m128_f32[2] * R.m[2][i]) > ra + rb)
            return false;
    }

    // Test axis L = A0 x B0
    ra = ae.m128_f32[1] * AbsR.m[2][0] + ae.m128_f32[2] * AbsR.m[1][0];
    rb = be.m128_f32[1] * AbsR.m[0][2] + be.m128_f32[2] * AbsR.m[0][1];
    if (std::fabsf(t.m128_f32[2] * R.m[1][0] - t.m128_f32[1] * R.m[2][0]) > ra + rb)
        return false;

    // Test axis L = A0 x B1
    ra = ae.m128_f32[1] * AbsR.m[2][1] + ae.m128_f32[2] * AbsR.m[1][1];
    rb = be.m128_f32[0] * AbsR.m[0][2] + be.m128_f32[2] * AbsR.m[0][0];
    if (std::fabsf(t.m128_f32[2] * R.m[1][1] - t.m128_f32[1] * R.m[2][1]) > ra + rb)
        return false;

    // Test axis L = A0 x B2
    ra = ae.m128_f32[1] * AbsR.m[2][2] + ae.m128_f32[2] * AbsR.m[1][2];
    rb = be.m128_f32[0] * AbsR.m[0][1] + be.m128_f32[1] * AbsR.m[0][0];
    if (std::fabsf(t.m128_f32[2] * R.m[1][2] - t.m128_f32[1] * R.m[2][2]) > ra + rb)
        return false;

    // Test axis L = A1 x B0
    ra = ae.m128_f32[0] * AbsR.m[2][0] + ae.m128_f32[2] * AbsR.m[0][0];
    rb = be.m128_f32[1] * AbsR.m[1][2] + be.m128_f32[2] * AbsR.m[1][1];
    if (std::fabsf(t.m128_f32[0] * R.m[2][0] - t.m128_f32[2] * R.m[0][0]) > ra + rb)
        return false;

    // Test axis L = A1 x B1
    ra = ae.m128_f32[0] * AbsR.m[2][1] + ae.m128_f32[2] * AbsR.m[0][1];
    rb = be.m128_f32[0] * AbsR.m[1][2] + be.m128_f32[2] * AbsR.m[1][0];
    if (std::fabsf(t.m128_f32[0] * R.m[2][1] - t.m128_f32[2] * R.m[0][1]) > ra + rb)
        return false;

    // Test axis L = A1 x B2
    ra = ae.m128_f32[0] * AbsR.m[2][2] + ae.m128_f32[2] * AbsR.m[0][2];
    rb = be.m128_f32[0] * AbsR.m[1][1] + be.m128_f32[1] * AbsR.m[1][0];
    if (std::fabsf(t.m128_f32[0] * R.m[2][2] - t.m128_f32[2] * R.m[0][2]) > ra + rb)
        return false;

    // Test axis L = A2 x B0
    ra = ae.m128_f32[0] * AbsR.m[1][0] + ae.m128_f32[1] * AbsR.m[0][0];
    rb = be.m128_f32[1] * AbsR.m[2][2] + be.m128_f32[2] * AbsR.m[2][1];
    if (std::fabsf(t.m128_f32[1] * R.m[0][0] - t.m128_f32[0] * R.m[1][0]) > ra + rb)
        return false;

    // Test axis L = A2 x B1
    ra = ae.m128_f32[0] * AbsR.m[1][1] + ae.m128_f32[1] * AbsR.m[0][1];
    rb = be.m128_f32[0] * AbsR.m[2][2] + be.m128_f32[2] * AbsR.m[2][0];
    if (std::fabsf(t.m128_f32[1] * R.m[0][1] - t.m128_f32[0] * R.m[1][1]) > ra + rb)
        return false;

    // Test axis L = A2 x B2
    ra = ae.m128_f32[0] * AbsR.m[1][2] + ae.m128_f32[1] * AbsR.m[0][2];
    rb = be.m128_f32[0] * AbsR.m[2][1] + be.m128_f32[1] * AbsR.m[2][0];
    if (std::fabsf(t.m128_f32[1] * R.m[0][2] - t.m128_f32[0] * R.m[1][2]) > ra + rb)
        return false;

    return true;
}

bool triebWerk::CCollision::AABBAndOBBTrigger(CAABBCollider * const a_pA, COBBCollider * const a_pB) const
{
    DirectX::XMVECTOR half = DirectX::XMVectorSet(2.0f, 2.0f, 2.0f, 0.0f);
    DirectX::XMVECTOR sub = DirectX::XMVectorSubtract(a_pA->GetMax(), a_pA->GetMin());
    DirectX::XMVECTOR halfWidths = DirectX::XMVectorDivide(sub, half);
    halfWidths = DirectX::XMVectorMultiply(halfWidths, a_pA->m_pEntity->m_Transform.GetScale());

    COBBCollider obbCollider;
    obbCollider.SetHalfWidths(halfWidths);
    obbCollider.m_pEntity = a_pA->m_pEntity;

    return OBBAndOBBTrigger(&obbCollider, a_pB);
}

bool triebWerk::CCollision::AABBAndSphereTrigger(CAABBCollider* const a_pA, CSphereCollider* const a_pB) const
{
    CTransform& transB = a_pB->m_pEntity->m_Transform;

    DirectX::XMVECTOR closestPointInAABB = DirectX::XMVectorMin(DirectX::XMVectorMax(transB.GetPosition(), a_pA->GetWorldMin()), a_pA->GetWorldMax());
    
    DirectX::XMVECTOR sub = DirectX::XMVectorSubtract(closestPointInAABB, transB.GetPosition());
    float lengthSquared = DirectX::XMVector3LengthSq(sub).m128_f32[0];

    return lengthSquared < (a_pB->GetWorldRadius() * a_pB->GetWorldRadius());
}

bool triebWerk::CCollision::SphereAndOBBTrigger(CSphereCollider* const a_pA, COBBCollider* const a_pB) const
{
    DirectX::XMVECTOR spherePos = a_pA->m_pEntity->m_Transform.GetPosition();
    DirectX::XMVECTOR obbPos = a_pB->m_pEntity->m_Transform.GetPosition();

    // Compute the square distance between sphere and OBB
    DirectX::XMMATRIX obbRotation = a_pB->GetRotation();
    DirectX::XMVECTOR obbExtents = a_pB->GetWorldHalfWidths();

    DirectX::XMVECTOR v = DirectX::XMVectorSubtract(spherePos, obbPos);
    float sqDist = 0.0f;

    for (size_t i = 0; i < 3; ++i)
    {
        float d = DirectX::XMVector3Dot(v, obbRotation.r[i]).m128_f32[0];
        float excess = 0.0f;

        if (d < -obbExtents.m128_f32[i])
            excess = d + obbExtents.m128_f32[i];
        else if (d > obbExtents.m128_f32[i])
            excess = d - obbExtents.m128_f32[i];

        sqDist += excess * excess;
    }

    return sqDist < (a_pA->GetWorldRadius() * a_pA->GetWorldRadius());
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
