#pragma once
#include <ICollider.h>
#include <CMesh.h>

namespace triebWerk
{
    class CAABBCollider : public ICollider
    {
    private:
        DirectX::XMVECTOR m_Min;
        DirectX::XMVECTOR m_Max;
        DirectX::XMVECTOR m_WorldMin;
        DirectX::XMVECTOR m_WorldMax;

    public:
        CAABBCollider();
        ~CAABBCollider();

        ECollider::Type GetColliderType() final;
        void UpdateWorldCollider() final;
        void CreateFromVertices(const CMesh::SVertex* const a_pVertices, const size_t a_Count);

        void SetMin(const DirectX::XMVECTOR a_Min);
        void SetMax(const DirectX::XMVECTOR a_Max);

        DirectX::XMVECTOR& GetMin();
        DirectX::XMVECTOR& GetMax();
        DirectX::XMVECTOR& GetWorldMin();
        DirectX::XMVECTOR& GetWorldMax();

    private:
        void SafeUpdateWorldCollider();
    };
}