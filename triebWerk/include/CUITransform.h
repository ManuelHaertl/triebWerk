#pragma once
#include <DirectXMath.h>
#include <CElementContainer.h>
#include <SUIScreenInformation.h>

namespace triebWerk
{
    class CUITransform
    {
    private:
        bool m_Modified;

        DirectX::XMFLOAT2 m_AnchorPoint;
        DirectX::XMVECTOR m_PositionOffset;
        DirectX::XMVECTOR m_Scale;
        float m_Rotation;
        
        DirectX::XMVECTOR m_RealPosition;
        DirectX::XMVECTOR m_RealScale;

        DirectX::XMVECTOR m_Pivot;
        DirectX::XMMATRIX m_Transformation;

        static SUIScreenInformation m_ScreenInformation;

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

        void SetScreenInformation(const SUIScreenInformation& a_rScreenInformation);

    private:
        inline void Modified();
    };
}