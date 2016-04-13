#pragma once
#include <vector>
#include <CAABBCollider.h>
#include <CManifold.h>

namespace triebWerk
{
    class CCollision
    {
    private:
        std::vector<CManifold> m_Manifolds;

    public:
        CCollision();
        ~CCollision();

        void CheckCollision(ICollider* a_pA, ICollider* a_pB);
        void SolveAllCollisions();

    private:
        void AABBAndAABB(CAABBCollider* a_pA, CAABBCollider* a_pB);
    };
}