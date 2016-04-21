#pragma once
#include <ECollisionState.h>

namespace triebWerk
{
    class CEntity;

    class CCollisionEvent
    {
    public:
        ECollisionState::Type m_CollisionState;
        CEntity* m_pPartner;
        bool m_Updated;

    public:
        CCollisionEvent();
        ~CCollisionEvent();
    };
}