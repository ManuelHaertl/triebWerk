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

    m_pInput->Initialize();
    m_pWorld->Initialize();
	m_pWindow->Initialize(false, 800, 800, "Test");

    return true;
}

bool triebWerk::CEngine::Run()
{
    m_pInput->Update(m_pTime->GetUnscaledDeltaTime());
    m_pWorld->Update();
    m_pTime->Update();
	MSG msg = m_pWindow->GetWindowEvent();
	ProcessMessage(msg);
    return m_IsRunning;
}

void triebWerk::CEngine::Shutdown()
{
    m_pInput->Shutdown();
    m_pWorld->Shutdown();

    delete m_pInput;
    delete m_pTime;
    delete m_pWorld;
	delete m_pWindow;
}

void triebWerk::CEngine::ProcessMessage(const MSG a_WindowEvent)
{
	switch (a_WindowEvent.message)
	{
	case WM_QUIT:
		m_IsRunning = false;
		break;

	default:
		break;
	}
}
