#include <CEngine.h>
#include <iostream>

triebWerk::CEngine::CEngine() :
	m_IsRunning(true),
	m_pGraphics(nullptr),
	m_pInput(nullptr),
	m_pResourceManager(nullptr),
	m_pTime(nullptr),
	m_pWindow(nullptr),
	m_pWorld(nullptr)
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
    m_pTime = new CTime();
    m_pInput = new CInput();
    m_pWorld = new CWorld();
	m_pWindow = new CWindow();
	m_pResourceManager = new CResourceManager();
	m_pGraphics = new CGraphics();
	m_pRenderer = new CRenderer();

	m_pWindow->Initialize(false, 800, 800, "Test");
	m_pGraphics->Initialize(*m_pWindow->GetWindowHandle(), 800, 800, false, false);
	m_pResourceManager->Initialize(m_pGraphics);
	m_pRenderer->Initialize(m_pGraphics, 800, 800);
	m_pWorld->Initialize(m_pRenderer);
    return true;
}

bool triebWerk::CEngine::Run()
{
	m_pTime->Update();

    m_pInput->Update(m_pTime->GetUnscaledDeltaTime());
    MSG msg = m_pWindow->GetWindowEvent();
    ProcessMessage(msg);

	m_pWindow->UpdateWindow();
    m_pWorld->Update(m_pTime->GetDeltaTime());
	m_pRenderer->DrawScene();

    return m_IsRunning;
}

void triebWerk::CEngine::Shutdown()
{
    m_pWorld->Shutdown();
	m_pResourceManager->CleanUp();
	m_pGraphics->Shutdown();
	m_pRenderer->Shutdown();

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

	case WM_EXITSIZEMOVE:
		m_pGraphics->UpdateSwapchainConfiguration();
		break;

	default:
        m_pInput->UpdateMSG(a_WindowEvent);
		break;
	}
}
