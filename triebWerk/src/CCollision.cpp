#include <CCollision.h>

triebWerk::CCollision::CCollision()
{
}

triebWerk::CCollision::~CCollision()
{
}

void triebWerk::CCollision::CheckCollision(ICollider* a_pA, ICollider* a_pB)
{
    CAABBCollider* a = (CAABBCollider*)a_pA;
    CAABBCollider* b = (CAABBCollider*)a_pB;
    
    AABBAndAABB(a, b);
}

void triebWerk::CCollision::SolveAllCollisions()
{
}

void triebWerk::CCollision::AABBAndAABB(CAABBCollider * a_pA, CAABBCollider * a_pB)
{
}
