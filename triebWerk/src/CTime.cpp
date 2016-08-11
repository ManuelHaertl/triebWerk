#include <CTime.h>
#include <Windows.h>

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
    m_LastLoopTime = m_StartupTime;
    m_LastTime = m_StartupTime;
}

triebWerk::CTime::~CTime()
{
}

float triebWerk::CTime::Update()
{
    auto now = std::chrono::high_resolution_clock::now();

    // Calculate Loop time
    auto dt = std::chrono::duration_cast<std::chrono::duration<float>>(now - m_LastLoopTime);
    m_LastLoopTime = now;

    return dt.count();
}

void triebWerk::CTime::NextFrame()
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

float triebWerk::CTime::GetDeltaTime() const
{
    return m_DeltaTime;
}

float triebWerk::CTime::GetUnscaledDeltaTime() const
{
    return m_UnscaledDeltaTime;
}

float triebWerk::CTime::GetTimeSinceStartup() const
{
    return m_TimeSinceStartup;
}

float triebWerk::CTime::GetTimeScale() const
{
    return m_TimeScale;
}

void triebWerk::CTime::SetTimeScale(const float a_TimeStamp)
{
    m_TimeScale = a_TimeStamp;
}

void triebWerk::CTime::ResetDeltaTime()
{
    m_LastTime = std::chrono::high_resolution_clock::now();
    m_LastLoopTime = m_LastTime;
    m_DeltaTime = 0;
    m_UnscaledDeltaTime = 0;
}

void triebWerk::CTime::StartPerformanceCounter()
{
    m_PerformanceStart = std::chrono::high_resolution_clock::now();
}

float triebWerk::CTime::EndPerformanceCounter()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - m_PerformanceStart);

    return elapsedTime.count();
}

std::string triebWerk::CTime::GetDateString()
{
	SYSTEMTIME  time;
	GetSystemTime(&time);

	std::string timeS;


	std::string day = std::to_string(time.wDay);
	if (day.size() == 1)
	{
		timeS += "0";
	}
	timeS += day;
	timeS += ".";
	std::string month = std::to_string(time.wMonth);
	if (month.size() == 1)
	{
		timeS += "0";
	}
	timeS += month;
	timeS += "." + std::to_string(time.wYear);
	timeS += " ";

	std::string hour = std::to_string(time.wHour + 2);
	if (hour.size() == 1)
	{
		timeS += "0";
	}
	timeS += hour;
	timeS += ":";
	std::string minute = std::to_string(time.wMinute);
	if (minute.size() == 1)
	{
		timeS += "0";
	}
	timeS += minute;

	return timeS;
}

int triebWerk::CTime::GetFPS() const
{
    return m_FPS;
}
