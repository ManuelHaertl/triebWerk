#pragma once
#include <CCollider.h>

namespace triebWerk
{
    class CAABB : public CCollider
    {
    public:
        CAABB();
        ~CAABB();

        ECollider::Type GetColliderType() final;
    };
}