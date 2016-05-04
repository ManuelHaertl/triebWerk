#pragma once
#include <vector>
#include <DirectXMath.h>

namespace triebWerk
{
    class CTransform
    {
    private:
        CTransform* m_pParent;
        std::vector<CTransform*> m_Children;

    private:
		bool m_Modified;

        DirectX::XMVECTOR m_Position;
        DirectX::XMVECTOR m_Scale;
        DirectX::XMVECTOR m_Rotation;
        DirectX::XMVECTOR m_LocalPosition;
        DirectX::XMVECTOR m_LocalScale;
        DirectX::XMVECTOR m_LocalRotation;
        DirectX::XMVECTOR m_Forward;
        DirectX::XMVECTOR m_Up;
        DirectX::XMVECTOR m_Side;
		DirectX::XMVECTOR m_Pivot;
		DirectX::XMMATRIX m_Transformation;

    public:
        CTransform();
        ~CTransform();

        void SetParent(CTransform* const a_pParent);
        CTransform* GetParent() const;

        void AddChild(CTransform* const a_pChild);
        void RemoveChild(CTransform* const a_pChild);
        std::vector<CTransform*>* GetChildren();

        void DetachChildren();
        void DetachFromParent();

        DirectX::XMVECTOR GetPosition() const;
        DirectX::XMVECTOR GetLocalPosition() const;

        DirectX::XMVECTOR GetScale() const;
        DirectX::XMVECTOR GetLocalScale() const;

        DirectX::XMVECTOR GetRotation() const;
        DirectX::XMVECTOR GetLocalRotation() const;

        DirectX::XMVECTOR GetForward() const;
        DirectX::XMVECTOR GetUp() const;
        DirectX::XMVECTOR GetSide() const;

        DirectX::XMVECTOR GetPivot() const;
        DirectX::XMMATRIX& GetTransformation();

        void SetPosition(const float a_X, const float a_Y, const float a_Z);
        void SetPosition(const DirectX::XMVECTOR a_Position);
        void SetLocalPosition(const float a_X, const float a_Y, const float a_Z);
        void SetLocalPosition(const DirectX::XMVECTOR a_Position);

        void SetScale(const float a_X, const float a_Y, const float a_Z);
        void SetScale(const DirectX::XMVECTOR a_Scale);

        void SetRotation(const float a_X, const float a_Y, const float a_Z);
        void SetRotation(const DirectX::XMVECTOR a_Rotation);

        void SetRotationDegrees(const float a_X, const float a_Y, const float a_Z);
        void SetRotationDegrees(const DirectX::XMVECTOR a_Rotation);

        void RotateDegrees(const float a_X, const float a_Y, const float a_Z);
        void RotateDegrees(DirectX::XMVECTOR a_Rotation);

        void SetPivot(const float a_X, const float a_Y, const float a_Z);
        void SetPivot(const DirectX::XMVECTOR a_Pivot);

        bool IsModified() const;
        void SetModifiedStateFalse();

    private:
        void CalculateForwardUpAndSideVector();
        void UpdateChildPosition();
    };
}