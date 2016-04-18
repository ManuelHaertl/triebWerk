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
		DirectX::XMVECTOR m_Pivot;
		DirectX::XMMATRIX m_Transformation;

    public:
        CTransform();
        ~CTransform();

        void SetParent(CTransform* a_pParent);
        CTransform* GetParent();

        void AddChild(CTransform* a_pChild);
        void RemoveChild(CTransform* a_pChild);
        std::vector<CTransform*>* GetChildren();

        void DetachChildren();
        void DetachFromParent();

        DirectX::XMVECTOR GetPosition();
        DirectX::XMVECTOR GetLocalPosition();

        DirectX::XMVECTOR GetScale();
        DirectX::XMVECTOR GetLocalScale();

        DirectX::XMVECTOR GetRotation();
        DirectX::XMVECTOR GetLocalRotation();

        void SetPosition(float a_X, float a_Y, float a_Z);
        void SetPosition(DirectX::XMVECTOR a_Position);
        void SetLocalPosition(float a_X, float a_Y, float a_Z);
        void SetLocalPosition(DirectX::XMVECTOR a_Position);

        void SetScale(float a_X, float a_Y, float a_Z);
        void SetScale(DirectX::XMVECTOR a_Scale);
        //void SetLocalScale(float a_X, float a_Y, float a_Z);
        //void SetLocalScale(DirectX::XMVECTOR a_Scale);

        void SetRotation(float a_X, float a_Y, float a_Z);
        void SetRotation(DirectX::XMVECTOR a_Rotation);
        //void SetLocalRotation(float a_X, float a_Y, float a_Z);
        //void SetLocalRotation(DirectX::XMVECTOR a_Rotation);

		DirectX::XMMATRIX& GetTransformation();
    private:
        void UpdateChildPosition();
        //void UpdateChildScale();
        //void UpdateChildRotation();
    };
}