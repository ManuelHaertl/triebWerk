#include <CEngine.h>
#include <iostream>

triebWerk::CEngine::CEngine() :
	m_IsRunning(true),
	m_pGraphics(nullptr),
	m_pInput(nullptr),
	m_pResourceManager(nullptr),
	m_pTime(nullptr),
	m_pWindow(nullptr),
	m_pWorld(nullptr),
	m_pDebug(nullptr)
{
}

triebWerk::CEngine::~CEngine()
{
}

triebWerk::CEngine & triebWerk::CEngine::Instance()
{
    static CEngine engine;
    return engine;
}

bool triebWerk::CEngine::Initialize()
{
    SEngineConfiguration config;
    config.m_Name = "triebWerk";
    config.m_Width = 800;
    config.m_Height = 600;
    config.m_Fullscreen = false;
    config.m_VSync = true;
    config.m_TargetFPS = 0;
    config.m_PhysicTimeStamp = 0.15f;

    return Initialize(config);
}

bool triebWerk::CEngine::Initialize(SEngineConfiguration a_Config)
{
    m_pTime = new CTime();
    m_pInput = new CInput();
    m_pWorld = new CWorld();
    m_pWindow = new CWindow();
    m_pResourceManager = new CResourceManager();
    m_pGraphics = new CGraphics();
    m_pRenderer = new CRenderer();
    m_pDebug = new CDebug();

    m_pWindow->Initialize(a_Config.m_Fullscreen, a_Config.m_Width, a_Config.m_Height, a_Config.m_Name);
    m_pGraphics->Initialize(m_pWindow->GetWindowHandle(), a_Config.m_Width, a_Config.m_Height, a_Config.m_Fullscreen, a_Config.m_VSync);
    m_pResourceManager->Initialize(m_pGraphics);
    m_pRenderer->Initialize(m_pGraphics, a_Config.m_Width, a_Config.m_Height);
    m_pWorld->Initialize(m_pRenderer, a_Config.m_TargetFPS, a_Config.m_PhysicTimeStamp);
    return true;
}

bool triebWerk::CEngine::Run()
{
	m_pTime->Update();

    m_pInput->Update(m_pTime->GetUnscaledDeltaTime());
    MSG msg = m_pWindow->GetWindowEvent();
    ProcessMessage(msg);
	m_pResourceManager->Update();

	m_pDebug->Update();
	m_pWindow->UpdateWindow();
    m_pWorld->Update(m_pTime->GetDeltaTime());

    return m_IsRunning;
}

void triebWerk::CEngine::Shutdown()
{
    m_pWorld->Shutdown();
	m_pResourceManager->CleanUp();
	m_pGraphics->Shutdown();
	m_pRenderer->Shutdown();

	delete m_pDebug;
    delete m_pInput;
    delete m_pTime;
    delete m_pWorld;
	delete m_pWindow;
	delete m_pResourceManager;
	delete m_pGraphics;
	delete m_pRenderer;
}

void triebWerk::CEngine::ProcessMessage(const MSG a_WindowEvent)
{
	switch (a_WindowEvent.message)
	{
	case WM_QUIT:
		m_IsRunning = false;
		break;

	//TODO: Listen only to finished resized
	case WM_SIZE:
		m_pGraphics->UpdateSwapchainConfiguration();
		break;

	default:
        m_pInput->UpdateMSG(a_WindowEvent);
		break;
	}
}
