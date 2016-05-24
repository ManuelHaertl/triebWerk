#pragma once
namespace triebWerk
{
    struct SEngineConfiguration
    {
        const char* m_Name;
        unsigned short m_Width;
        unsigned short m_Height;
        bool m_Fullscreen;
        bool m_VSync;
        unsigned short m_TargetFPS;
        float m_PhysicTimeStamp;
    };
}