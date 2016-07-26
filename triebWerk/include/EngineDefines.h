#pragma once
#define twEngine triebWerk::CEngine::Instance()

#define twInput triebWerk::CEngine::Instance().m_pInput
#define twGamepad triebWerk::CEngine::Instance().m_pInput->m_Gamepad
#define twKeyboard triebWerk::CEngine::Instance().m_pInput->m_Keyboard
#define twMouse triebWerk::CEngine::Instance().m_pInput->m_Mouse

#define twDebug triebWerk::CEngine::Instance().m_pDebug
#define twRenderer triebWerk::CEngine::Instance().m_pRenderer
#define twFontManager triebWerk::CEngine::Instance().m_pFontManager
#define twResourceManager triebWerk::CEngine::Instance().m_pResourceManager
#define twSceneManager triebWerk::CEngine::Instance().m_pSceneManager
#define twTime triebWerk::CEngine::Instance().m_pTime
#define twActivePhysic triebWerk::CEngine::Instance().m_pSceneManager->m_pActiveScene->m_pScene->m_pWorld->m_pPhysicWorld
#define twActiveWorld triebWerk::CEngine::Instance().m_pSceneManager->m_pActiveScene->m_pScene->m_pWorld
#define twActiveUIWorld triebWerk::CEngine::Instance().m_pSceneManager->m_pActiveScene->m_pScene->m_pWorld->m_pUIWorld
#define twGraphic triebWerk::CEngine::Instance().m_pGraphics
#define twAudio triebWerk::CEngine::Instance().m_pSoundEngine
#define twWindow triebWerk::CEngine::Instance().m_pWindow

#define twRandom triebWerk::CRandom