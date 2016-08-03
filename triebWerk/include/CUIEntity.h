#pragma once
#include <CUITransform.h>
#include <CID.h>
#include <IBehaviour.h>
#include <IDrawable.h>

namespace triebWerk
{
	class CUIEntity
    {
    public:
        CUITransform m_Transform;
        CID m_ID;

    private:
        IBehaviour* m_pBehaviour;
        IDrawable* m_pDrawable;
        bool m_IsInWorld;

    public:
        CUIEntity();
        ~CUIEntity();

        IBehaviour* GetBehaviour() const;
        IDrawable* GetDrawable() const;

        void SetBehaviour(IBehaviour* a_pBehaviour);
        void SetDrawable(IDrawable* a_pDrawable);

        void RemoveBehaviour();
        void RemoveDrawable();

        bool IsInWorld() const;
        void SetInWorldState(const bool a_State);
    };
}