#pragma once
#include <ICollider.h>

namespace triebWerk
{
    class CAABBCollider : public ICollider
    {
    public:
        CAABBCollider();
        ~CAABBCollider();

        ECollider::Type GetColliderType() final;
    };
}