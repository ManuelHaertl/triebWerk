#pragma once
#include <math.h>
#include <vector>
#include <CAABBCollider.h>
#include <CEntity.h>

namespace triebWerk
{
    class CCollision
    {
    public:
        CCollision();
        ~CCollision();

        void CheckCollision(ICollider* const a_pA, ICollider* const a_pB) const;

    private:
        bool AABBAndAABBTrigger(CAABBCollider* const a_pA, CAABBCollider* const a_pB) const;
        bool SphereAndSphereTrigger(CSphereCollider* const a_pA, CSphereCollider* const a_pB) const;
        bool AABBAndSphereTrigger(CAABBCollider* const a_pA, CSphereCollider* const a_pB) const;
        void Collided(ICollider* const a_pA, ICollider* const a_pB) const;
    };
}