#pragma once
#include <ECombine.h>

namespace triebWerk
{
    struct SPhysicMaterial
    {
        float m_Bounciness;
        float m_DynamicFriction;
        float m_StaticFriction;
        ECombine::Type m_FrictionCombine;
        ECombine::Type m_BounceCombine;

        SPhysicMaterial() :
            m_Bounciness(0.0f),
            m_DynamicFriction(0.6f),
            m_StaticFriction(0.6f),
            m_FrictionCombine(ECombine::Average),
            m_BounceCombine(ECombine::Average)
        {

        }
    };
}