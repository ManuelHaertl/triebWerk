#pragma once
#include <vector>
#include <CAABBCollider.h>
#include <CCollision.h>
#include <CPhysicEntity.h>

namespace triebWerk
{
    class CPhysicWorld
    {
    public:
        DirectX::XMVECTOR m_GravityScale;

    private:
        size_t m_CurrentEntityID; // ID counter for creating entities

        std::vector<CPhysicEntity*> m_Entities;     // contains every entity
        std::vector<CBody*> m_Bodies;               // contains every body from all entities
        std::vector<ICollider*> m_StaticCollider;   // don't check any collision on those
        std::vector<ICollider*> m_DynamicCollider;  // perform a collision check on those

    public:
        CPhysicWorld();
        ~CPhysicWorld();

        CPhysicEntity* CreatePhysicEntity();
        CBody* CreateBody();
        CAABBCollider* CreateAABBCollider();
        void AddPhysicEntity(CPhysicEntity* a_pPhysicEntity);
        void AddBody(CBody* a_pBody);
        void AddCollider(ICollider* a_pCollider);
        void RemovePhysicEntity(CPhysicEntity* a_pPhysicEntity);
        void RemoveBody(CBody* a_pBody);
        void RemoveCollider(ICollider* a_pCollider);
        void Update(const float a_DeltaTime);
    };
}