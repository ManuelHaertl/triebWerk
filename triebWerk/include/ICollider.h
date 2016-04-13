#pragma once
#include <DirectXCollision.h>
#include <ECollider.h>
#include <CBody.h>
#include <CTransform.h>
#include <SPhysicMaterial.h>

namespace triebWerk
{
    class ICollider
    {
    public:
        bool m_CheckCollision;
        bool m_IsTrigger;
        SPhysicMaterial m_PhysicMaterial;

        CTransform* m_pTransform;
        CBody* m_pBody;

    private:
        size_t m_ID;

    public:
        ICollider();
        virtual ~ICollider();

        virtual ECollider::Type GetColliderType() = 0;

        size_t GetID() const;
        void SetID(const size_t a_ID);
    };
}