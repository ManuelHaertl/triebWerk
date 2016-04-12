#pragma once
#include <DirectXMath.h>

namespace triebWerk
{
    class CBody
    {
    public:
        DirectX::XMFLOAT3 m_Velocity;
        float m_Mass;
        float m_Drag;
        float m_GravityFactor;

    private:
        float m_MassInverse;

    public:
        CBody();
        ~CBody();
    };
}