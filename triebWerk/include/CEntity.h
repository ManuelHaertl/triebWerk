#pragma once
#include <CTransform.h>
#include <CPhysicEntity.h>
#include <CPhysicWorld.h>
#include <IBehaviour.h>
#include <IDrawable.h>

namespace triebWerk
{
    class CEntity
    {
    public:
        CTransform m_Transform;

    private:
        CPhysicEntity* m_pPhysicEntity;
        IBehaviour* m_pBehaviour;
		IDrawable* m_pDrawable;
        bool m_IsInWorld;

    public:
        CEntity();
        ~CEntity();

        CPhysicEntity* GetPhysicEntity() const;
        IBehaviour* GetBehaviour() const;
		IDrawable* GetDrawable() const;

        void SetPhysicEntity(CPhysicEntity* a_pPhysicEntity);
        void SetBehaviour(IBehaviour* a_pBehaviour);
		void SetDrawable(IDrawable* a_pDrawable);

        void RemovePhysicEntity();
        void RemoveBehaviour();
		void RemoveDrawable();

        bool IsInWorld() const;
        void SetInWorldState(const bool a_State);
    };
}