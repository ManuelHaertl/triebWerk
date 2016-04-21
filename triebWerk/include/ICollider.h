#pragma once
#include <vector>

#include <ECollider.h>
#include <CBody.h>
#include <CCollisionEvent.h>
#include <CTransform.h>

namespace triebWerk
{
    class CEntity;

    class ICollider
    {
    public:
        // determines wheiter this collider actively makes collision checks with other colliders
        bool m_CheckCollision;

        // a collider only can contain collision events if m_CheckCollision is true
        std::vector<CCollisionEvent> m_CollisionEvents;

        // the entity the collider belongs to
        CEntity* m_pEntity;

    public:
        ICollider();
        virtual ~ICollider();

        virtual ECollider::Type GetColliderType() = 0;
    };
}