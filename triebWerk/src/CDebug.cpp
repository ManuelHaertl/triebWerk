#include <CDebug.h>
#include <CEngine.h>
#include <CDebugLogfile.h>
#include <iostream>

triebWerk::CDebug::CDebug() :
	m_DebugMode(false)
{
	CDebugLogfile::Instance().CreateLogfile("twLog.html");
}

triebWerk::CDebug::~CDebug()
{
}

void triebWerk::CDebug::Update()
{
	if (m_DebugMode)
	{
		m_DebugCamera.Update();
	}
}

void triebWerk::CDebug::Enable()
{
    if (m_DebugMode == false)
    {
        m_DebugMode = true;
        m_DebugCamera.StartDebugging();
    }
}

void triebWerk::CDebug::Disable()
{
    if (m_DebugMode == true)
    {
        m_DebugMode = false;
        m_DebugCamera.EndDebugging();
    }
}

bool triebWerk::CDebug::IsInDebug() const
{
    return m_DebugMode;
}
