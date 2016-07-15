#pragma once
#include <CCollisionEvent.h>

namespace triebWerk
{
    class CEntity;
    class CUIEntity;

    class IBehaviour
    {
    public:
        CEntity* m_pEntity;
        CUIEntity* m_pUIEntity;

    public:
        IBehaviour();
        virtual ~IBehaviour();

        virtual void Start();
        virtual void Update();
        virtual void LateUpdate();
        virtual void End();

        virtual void CollisionEnter(CCollisionEvent a_Collision);
        virtual void CollisionStay(CCollisionEvent a_Collision);
        virtual void CollisionLeave(CCollisionEvent a_Collision);
    };
}