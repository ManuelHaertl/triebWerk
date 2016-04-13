#pragma once
#include <DirectXMath.h>
#include <CTransform.h>

namespace triebWerk
{
    class CBody
    {
    public:
        CTransform* m_pTransform;
        DirectX::XMVECTOR m_Velocity;
        float m_Mass;
        float m_Drag;
        float m_GravityFactor;

    private:
        float m_MassInverse;

    public:
        CBody();
        ~CBody();

        void ApplyImpulse(const DirectX::XMVECTOR& a_rImpulse);
        void SetMass(const float a_Mass);
    };
}