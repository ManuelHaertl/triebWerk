#pragma once
#include <ICollider.h>
#include <CMesh.h>

namespace triebWerk
{
    class CSphereCollider : public ICollider
    {
    public:
        float m_Radius;

    public:
        CSphereCollider();
        ~CSphereCollider();

        ECollider::Type GetColliderType() final;
        void CreateFromVertices(const CMesh::SVertex* const a_pVertices, const size_t a_Count);
    };
}