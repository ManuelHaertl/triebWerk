#pragma once
#include <CTransform.h>
#include <IBehaviour.h>

namespace triebWerk
{
    class CEntity
    {
    public:
        CTransform m_Transform;
        IBehaviour* m_pBehaviour;

    public:
        CEntity();
        ~CEntity();
    };
}