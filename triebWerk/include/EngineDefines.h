#pragma once
#define twEngine triebWerk::CEngine::Instance()

#define twInput triebWerk::CEngine::Instance().m_pInput
#define twGamepad triebWerk::CEngine::Instance().m_pInput->m_Gamepad
#define twKeyboard triebWerk::CEngine::Instance().m_pInput->m_Keyboard
#define twMouse triebWerk::CEngine::Instance().m_pInput->m_Mouse

#define twDebug triebWerk::CEngine::Instance().m_pDebug
#define twRenderer triebWerk::CEngine::Instance().m_pRenderer
#define twResourceManager triebWerk::CEngine::Instance().m_pResourceManager
#define twTime triebWerk::CEngine::Instance().m_pTime
#define twPhysic triebWerk::CEngine::Instance().m_pWorld->m_pPhysicWorld
#define twWorld triebWerk::CEngine::Instance().m_pWorld

#define twRandom triebWerk::CRandom