#pragma once
#include <EngineDefines.h>
#include <CInput.h>
#include <CTime.h>
#include <CWindow.h>
#include <CResourceManager.h>
#include <CGraphics.h>
#include <CRandom.h>
#include <CRenderer.h>
#include <CSceneManager.h>
#include <CDebug.h>
#include <SEngineConfiguration.h>

namespace triebWerk
{
    class CEngine
    {
    public:
        CInput* m_pInput;
        CTime* m_pTime;
		CWindow* m_pWindow;
		CGraphics* m_pGraphics;
		CResourceManager* m_pResourceManager;
		CRenderer* m_pRenderer;
        CSceneManager* m_pSceneManager;
		CDebug* m_pDebug;

	private:
        const double SleepTimeDivisor = 10.0;

		bool m_IsRunning;
        float m_TimePerFrame;
        float m_CurrentTime;
        float m_PhysicTimeStamp;
        float m_CurrentPhysicTime;
        std::chrono::duration<long long, std::micro> m_SleepTime;

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
		void ProcessWindowMessages();
    };
}