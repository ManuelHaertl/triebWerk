#include <CEngine.h>

triebWerk::CEngine::CEngine()
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

    m_pInput->Initialize();
    m_pWorld->Initialize();
    return true;
}

bool triebWerk::CEngine::Run()
{
    m_pInput->Update();
    m_pWorld->Update();
    m_pTime->Update();
    return true;
}

void triebWerk::CEngine::Shutdown()
{
    m_pInput->Shutdown();
    m_pWorld->Shutdown();

    delete m_pInput;
    delete m_pTime;
    delete m_pWorld;
}
