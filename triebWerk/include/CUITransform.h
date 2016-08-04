#pragma once
#include <DirectXMath.h>
#include <CElementContainer.h>

namespace triebWerk
{
    class CUITransform
    {
    public:
        static float ResolutionWidth;
        static float ResolutionHeight;
        static float ReferenceWidth;
        static float ReferenceHeight;
        static float ReferenceScale;

    private:
        bool m_Modified;

        DirectX::XMFLOAT2 m_AnchorPoint;
        DirectX::XMVECTOR m_PositionOffset;
        DirectX::XMVECTOR m_Scale;
        DirectX::XMVECTOR m_Rotation;

        DirectX::XMVECTOR m_Pivot;
        DirectX::XMMATRIX m_Transformation;

    public:
        CUITransform();
        ~CUITransform();

        DirectX::XMFLOAT2 GetAnchorPoint() const;
        DirectX::XMVECTOR GetPositionOffset() const;
        DirectX::XMVECTOR GetScale() const;
        float GetRotation() const;

        DirectX::XMVECTOR GetPivot() const;
        DirectX::XMMATRIX& GetTransformation();

        void SetAnchorPoint(const float a_X, const float a_Y);
        void SetAnchorPoint(const DirectX::XMFLOAT2 a_AnchorPoint);

        void SetPositionOffset(const float a_X, const float a_Y, const float a_Z);
        void SetPositionOffset(const DirectX::XMVECTOR a_PositionOffset);

        void SetScale(const float a_X, const float a_Y, const float a_Z);
        void SetScale(const DirectX::XMVECTOR a_Scale);

        void SetRotationDegrees(const float a_Rotation);
        void SetRotationRadians(const float a_Rotation);

        void RotateDegrees(const float a_Degrees);

        void SetPivot(const float a_X, const float a_Y, const float a_Z);
        void SetPivot(const DirectX::XMVECTOR a_Pivot);

        void UpdateScreenInformation();

    private:
        inline void Modified();
    };
}