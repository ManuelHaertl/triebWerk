#include <CTime.h>

triebWerk::CTime::CTime() :
    m_DeltaTime(0.0f),
    m_UnscaledDeltaTime(0.0f),
    m_TimeSinceStartup(0.0f),
    m_TimeScale(1.0f),
    m_FPS(0),
    m_CurrentFPSCalcTime(0.0f),
    m_CurrentFPSCounter(0)
{
    m_StartupTime = std::chrono::high_resolution_clock::now();;
    m_LastTime = m_StartupTime;
}

triebWerk::CTime::~CTime()
{
}

void triebWerk::CTime::Update()
{
    auto now = std::chrono::high_resolution_clock::now();

    // Calculate delta time
    auto dt = std::chrono::duration_cast<std::chrono::duration<float>>(now - m_LastTime);
    m_LastTime = now;
    
    m_UnscaledDeltaTime = dt.count();
    m_DeltaTime = m_UnscaledDeltaTime * m_TimeScale;

    // Calculate time since startup
    auto realTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - m_StartupTime);
    m_TimeSinceStartup = realTime.count();

    // Calculate FPS
    m_CurrentFPSCalcTime += m_DeltaTime;
    m_CurrentFPSCounter++;
    if (m_CurrentFPSCalcTime >= FPS_CALC_TIME)
    {
        m_FPS = m_CurrentFPSCounter / static_cast<int>(FPS_CALC_TIME);
        m_CurrentFPSCounter = 0;
        m_CurrentFPSCalcTime = 0.0f;
    }
}

float triebWerk::CTime::GetDeltaTime()
{
    return m_DeltaTime;
}

float triebWerk::CTime::GetUnscaledDeltaTime()
{
    return m_UnscaledDeltaTime;
}

float triebWerk::CTime::GetTimeSinceStartup()
{
    return m_TimeSinceStartup;
}

float triebWerk::CTime::GetTimeScale()
{
    return m_TimeScale;
}

void triebWerk::CTime::SetTimeScale(float a_TimeStamp)
{
    m_TimeScale = a_TimeStamp;
}

int triebWerk::CTime::GetFPS()
{
    return m_FPS;
}
