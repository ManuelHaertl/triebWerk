#include <CEngine.h>

triebWerk::CEngine::CEngine() : m_IsRunning(true)
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

    m_pWorld->Initialize();
	m_pWindow->Initialize(false, 800, 800, "Test");
	m_pResourceManager->Initialize();

    return true;
}

bool triebWerk::CEngine::Run()
{
    m_pInput->Update(m_pTime->GetUnscaledDeltaTime());
    MSG msg = m_pWindow->GetWindowEvent();
    ProcessMessage(msg);

    m_pTime->Update();
    m_pWorld->Update(m_pTime->GetDeltaTime());

    return m_IsRunning;
}

void triebWerk::CEngine::Shutdown()
{
    m_pWorld->Shutdown();
	m_pResourceManager->CleanUp();

    delete m_pInput;
    delete m_pTime;
    delete m_pWorld;
	delete m_pWindow;
	delete m_pResourceManager;
}

void triebWerk::CEngine::ProcessMessage(const MSG a_WindowEvent)
{
	switch (a_WindowEvent.message)
	{
	case WM_QUIT:
		m_IsRunning = false;
		break;

	default:
        m_pInput->UpdateMSG(a_WindowEvent);
		break;
	}
}
