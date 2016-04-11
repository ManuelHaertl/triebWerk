#pragma once
#include <vector>
#include <CBody.h>
#include <CCollider.h>

namespace triebWerk
{
    class CPhysicEntity
    {
    public:
        CBody* m_pBody;
        std::vector<CCollider*> m_Collider;

    private:
        size_t m_ID; // used so collider from the same entity don't collide with each other

    public:
        CPhysicEntity(size_t a_EntityID);
        ~CPhysicEntity();
    };
}