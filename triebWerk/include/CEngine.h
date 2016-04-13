#pragma once
#include <EngineDefines.h>
#include <CInput.h>
#include <CTime.h>
#include <CWorld.h>
#include <CWindow.h>
#include <CResourceManager.h>
#include <CGraphics.h>
#include <CRenderer.h>

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

	private:
		bool m_IsRunning;

    private:
        CEngine();
        ~CEngine();

    public:
        static CEngine& Instance();

    public:
        bool Initialize();
        bool Run();
        void Shutdown();

	private:
		void ProcessMessage(const MSG a_WindowEvent);
    };
}