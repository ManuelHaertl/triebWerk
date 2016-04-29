#pragma once
#include <cmath>
#include <ICollider.h>
#include <CMesh.h>

namespace triebWerk
{
    class COBBCollider : public ICollider
    {
    private:
        DirectX::XMMATRIX m_Rotation;
        DirectX::XMVECTOR m_HalfWidths;
        DirectX::XMVECTOR m_WorldHalfWidths;

    public:
        COBBCollider();
        ~COBBCollider();

        ECollider::Type GetColliderType() final;
        void UpdateWorldCollider() final;
        void CreateFromVertices(const CMesh::SVertex* const a_pVertices, const size_t a_Count);

        void SetHalfWidths(const DirectX::XMVECTOR a_HalfWidths);

        DirectX::XMMATRIX& GetRotation();
        DirectX::XMVECTOR& GetHalfWidths();
        DirectX::XMVECTOR& GetWorldHalfWidths();

    private:
        void SafeUpdateWorldCollider();
    };
}