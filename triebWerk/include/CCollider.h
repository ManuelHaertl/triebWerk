#pragma once
#include <DirectXCollision.h>
#include <ECollider.h>
#include <SPhysicMaterial.h>

namespace triebWerk
{
    class CCollider
    {
    public:
        bool m_CheckCollision;
        bool m_IsTrigger;
        SPhysicMaterial m_PhysicMaterial;
        DirectX::BoundingBox m_BoundingBox;

    public:
        CCollider();
        virtual ~CCollider();

        virtual ECollider::Type GetColliderType() = 0;
    };
}