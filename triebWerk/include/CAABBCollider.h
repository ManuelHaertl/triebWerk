#pragma once
#include <ICollider.h>
#include <CMesh.h>

namespace triebWerk
{
    class CAABBCollider : public ICollider
    {
    public:
        DirectX::XMVECTOR m_Min;
        DirectX::XMVECTOR m_Max;

    public:
        CAABBCollider();
        ~CAABBCollider();

        ECollider::Type GetColliderType() final;

        void CreateFromMesh(CMesh* a_pMesh);
    };
}