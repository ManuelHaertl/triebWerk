#pragma once
#include <chrono>

namespace triebWerk
{
    class CTime
    {
    private:
        std::chrono::high_resolution_clock::time_point m_StartupTime;
        std::chrono::high_resolution_clock::time_point m_LastTime;
        float m_DeltaTime;
        float m_UnscaledDeltaTime;
        float m_TimeSinceStartup;
        float m_TimeScale;

    public:
        CTime();
        ~CTime();

    public:
        void Update();

        float GetDeltaTime();
        float GetUnscaledDeltaTime();

        float GetTimeSinceStartup();

        float GetTimeScale();
        void SetTimeScale(float a_TimeScale);
    };
}