#pragma once
#include <ICollider.h>
#include <CMesh.h>

namespace triebWerk
{
    class CSphereCollider : public ICollider
    {
    private:
        float m_Radius;
        float m_WorldRadius;

    public:
        CSphereCollider();
        ~CSphereCollider();

        ECollider::Type GetColliderType() final;
        void UpdateWorldCollider() final;
        void CreateFromVertices(const CMesh::SVertex* const a_pVertices, const size_t a_Count);

        void SetRadius(const float a_Radius);

        float GetRadius() const;
        float GetWorldRadius() const;

    private:
        void SafeUpdateWorldCollider();
    };
}