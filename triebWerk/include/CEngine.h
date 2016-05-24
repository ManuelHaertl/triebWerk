#pragma once
#include <EngineDefines.h>
#include <CInput.h>
#include <CTime.h>
#include <CWorld.h>
#include <CWindow.h>
#include <CResourceManager.h>
#include <CGraphics.h>
#include <CRandom.h>
#include <CRenderer.h>
#include <CDebug.h>
#include <SEngineConfiguration.h>

namespace triebWerk
{
    class CEngine
    {
    public:
        CInput* m_pInput;
        CTime* m_pTime;
        CWorld* m_pWorld;
		CWindow* m_pWindow;
		CGraphics* m_pGraphics;
		CResourceManager* m_pResourceManager;
		CRenderer* m_pRenderer;
		CDebug* m_pDebug;

	private:
		bool m_IsRunning;

    private:
        CEngine();
        ~CEngine();

    public:
        static CEngine& Instance();

    public:
        bool Initialize();
        bool Initialize(SEngineConfiguration a_Config);
        bool Run();
        void Shutdown();

	private:
		void ProcessMessage(const MSG a_WindowEvent);
    };
}