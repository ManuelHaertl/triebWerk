#pragma once
#include <CTransform.h>

namespace triebWerk
{
    class CEntity
    {
    public:
        CTransform m_Transform;

    public:
        CEntity();
        ~CEntity();
    };
}