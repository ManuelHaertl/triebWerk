#pragma once
#include <DirectXCollision.h>

namespace triebWerk
{
    class CCollider
    {
    public:
        bool m_CheckCollision;
        bool m_IsTrigger;
        DirectX::BoundingBox m_BoundingBox;

    public:
        CCollider();
        ~CCollider();
    };
}