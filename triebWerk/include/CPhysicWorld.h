#pragma once
#include <vector>
#include <CPhysicEntity.h>
#include <CCollider.h>
#include <CAABB.h>

namespace triebWerk
{
    class CPhysicWorld
    {
    public:
        float m_GravityScale;

    private:
        size_t m_CurrentEntityID; // ID counter for creating entities

        std::vector<CPhysicEntity*> m_Entities;     // contains every entity
        std::vector<CBody*> m_Bodies;               // contains every body from all entities
        std::vector<CCollider*> m_StaticCollider;   // don't check any collision on those
        std::vector<CCollider*> m_DynamicCollider;  // perform a collision check on those

    public:
        CPhysicWorld();
        ~CPhysicWorld();

        CPhysicEntity* CreatePhysicEntity();
        CBody* CreateBody();
        CAABB* CreateAABB();
        void AddPhysicEntity(CPhysicEntity* a_pPhysicEntity);
        void AddBody(CBody* a_pBody);
        void AddCollider(CCollider* a_pCollider);
        void RemovePhysicEntity(CPhysicEntity* a_pPhysicEntity);
        void RemoveBody(CBody* a_pBody);
        void RemoveCollider(CCollider* a_pCollider);
        void Update(const float a_DeltaTime);
    };
}