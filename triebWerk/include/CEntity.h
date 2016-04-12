#pragma once
#include <CTransform.h>
#include <CPhysicEntity.h>
#include <CPhysicWorld.h>
#include <IBehaviour.h>

namespace triebWerk
{
    class CEntity
    {
    public:
        CTransform m_Transform;

    private:
        CPhysicEntity* m_pPhysicEntity;
        IBehaviour* m_pBehaviour;
        bool m_IsInWorld;

    public:
        CEntity();
        ~CEntity();

        CPhysicEntity* GetPhysicEntity() const;
        IBehaviour* GetBehaviour() const;
        
        void SetPhysicEntity(CPhysicEntity* a_pPhysicEntity);
        void SetBehaviour(IBehaviour* a_pBehaviour);

        void RemovePhysicEntity();
        void RemoveBehaviour();

        bool IsInWorld() const;
        void SetInWorldState(const bool a_State);
    };
}