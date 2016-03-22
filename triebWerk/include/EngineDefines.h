#pragma once
#define twEngine triebWerk::CEngine::Instance()
#define twInput triebWerk::CEngine::Instance().m_pInput
#define twGamepad triebWerk::CEngine::Instance().m_pInput->m_Gamepad
#define twTime triebWerk::CEngine::Instance().m_pTime
#define twWorld triebWerk::CEngine::Instance().m_pWorld