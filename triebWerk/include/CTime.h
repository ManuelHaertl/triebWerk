#pragma once
#include <chrono>

namespace triebWerk
{
    class CTime
    {
    private:
        const float FPS_CALC_TIME = 1.0f;

        std::chrono::high_resolution_clock::time_point m_StartupTime;
        std::chrono::high_resolution_clock::time_point m_LastTime;
        float m_DeltaTime;
        float m_UnscaledDeltaTime;
        float m_TimeSinceStartup;
        float m_TimeScale;

        int m_FPS;
        float m_CurrentFPSCalcTime;
        int m_CurrentFPSCounter;

    public:
        CTime();
        ~CTime();

    public:
        void Update();

        float GetDeltaTime() const;
        float GetUnscaledDeltaTime() const;

        float GetTimeSinceStartup() const;

        float GetTimeScale() const;
        void SetTimeScale(const float a_TimeScale);

        int GetFPS() const;
    };
}