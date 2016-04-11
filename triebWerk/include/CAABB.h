#pragma once
#include <CCollider.h>

namespace triebWerk
{
    class CAABB : public CCollider
    {
    public:
        CAABB();
        virtual ~CAABB();
    };
}