#pragma once
#include <vector>
#include <CBody.h>
#include <CTransform.h>
#include <ICollider.h>

namespace triebWerk
{
    class CPhysicWorld;

    class CPhysicEntity
    {
    public:
        CTransform* m_pTransform;
        std::vector<ICollider*> m_Collider;

    private:
        CPhysicWorld* m_pPhysicWorld;
        CBody* m_pBody;
        bool m_IsInPhysicWorld;

    private:
        size_t m_ID; // used so collider from the same entity don't collide with each other

    public:
        CPhysicEntity(size_t a_EntityID, CPhysicWorld* a_pPhysicWorld);
        ~CPhysicEntity();

        size_t GetID() const;
        CPhysicWorld* GetPhysicWorld() const;
        CBody* GetBody() const;
        std::vector<ICollider*>* GetCollider() const;

        void SetBody(CBody* a_pBody);
        void AddCollider(ICollider* a_pCollider);
        
        void RemoveBody();
        void RemoveCollider(ICollider* a_pCollider);
        void RemoveAllCollider();

        bool IsInPhysicWorld() const;
        void SetInPhysicWorldState(const bool a_State);
    };
}