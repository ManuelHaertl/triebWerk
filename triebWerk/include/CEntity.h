#pragma once
#include <CTransform.h>
#include <CPhysicEntity.h>
#include <IBehaviour.h>

namespace triebWerk
{
    class CEntity
    {
    public:
        CTransform m_Transform;
        CPhysicEntity* m_pPhysicEntity;
        IBehaviour* m_pBehaviour;

    public:
        CEntity();
        ~CEntity();
    };
}