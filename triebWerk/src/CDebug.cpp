#include <CDebug.h>
#include <CEngine.h>
#include <iostream>

triebWerk::CDebug::CDebug() :
	m_DebugMode(false)
{
}

triebWerk::CDebug::~CDebug()
{
}

void triebWerk::CDebug::Update()
{
	if(CEngine::Instance().m_pInput->m_Keyboard.IsState(triebWerk::EKey::F3, triebWerk::EButtonState::Down))
	{
		m_DebugMode = !m_DebugMode;
	}

	if (m_DebugMode)
	{
		m_DebugCamera.Update();
	}

}
