#include <CEngine.h>
#include <iostream>

triebWerk::CEngine::CEngine() :
	m_pGraphics(nullptr),
	m_pInput(nullptr),
	m_pResourceManager(nullptr),
	m_pTime(nullptr),
	m_pWindow(nullptr),
    m_pSceneManager(nullptr),
    m_pFontManager(nullptr),
	m_pDebug(nullptr),
    m_IsRunning(true),
    m_TimePerFrame(0.0f),
    m_CurrentTime(0.0f),
    m_PhysicTimeStamp(0.0f),
    m_CurrentPhysicTime(0.0f)
{
}

triebWerk::CEngine::~CEngine()
{
}

triebWerk::CEngine& triebWerk::CEngine::Instance()
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
	config.m_MasterVolume = 1.0f;
	config.m_BGMVolume = 1.0f;
	config.m_SFXVolume = 1.0f;

    return Initialize(config);
}

bool triebWerk::CEngine::Initialize(const SEngineConfiguration& a_Config)
{
	bool result = false;

    m_pTime = new CTime();
    m_pInput = new CInput();
    m_pDebug = new CDebug();

	m_pWindow = new CWindow();
    result = m_pWindow->Initialize(a_Config.m_Fullscreen, a_Config.m_Width, a_Config.m_Height, a_Config.m_Name);
	if (!result)
		return false;

	m_pGraphics = new CGraphics();
	result = m_pGraphics->Initialize(m_pWindow->GetWindowHandle(), a_Config.m_Width, a_Config.m_Height, a_Config.m_Fullscreen, a_Config.m_VSync);
	if (!result)
		return false;

	m_pFontManager = new CFontManager();
    unsigned int dpiX, dpiY;
    m_pWindow->GetDPIFromDisplay(&dpiX, &dpiY);
    result = m_pFontManager->Initialize(m_pGraphics, dpiX, dpiY);
	if (!result)
		return false;

	m_pSoundEngine = new CSoundEngine();
	m_pResourceManager = new CResourceManager();
	result = m_pResourceManager->Initialize(m_pGraphics, m_pFontManager->GetLibrary(), m_pSoundEngine);
	if (!result)
		return false;

	result = m_pSoundEngine->Initialize(m_pResourceManager, a_Config.m_MasterVolume, a_Config.m_BGMVolume, a_Config.m_SFXVolume);
	if (!result)
		return false;

	m_pRenderer = new CRenderer();
	m_pRenderer->Initialize(m_pGraphics, a_Config.m_Width, a_Config.m_Height);

	m_pSceneManager = new CSceneManager();
    m_pSceneManager->Initialize(m_pRenderer, a_Config.m_PhysicTimeStamp);


    if (a_Config.m_TargetFPS == 0)
        m_TimePerFrame = 0;
    else
        m_TimePerFrame = 1.0f / static_cast<float>(a_Config.m_TargetFPS);

    m_PhysicTimeStamp = a_Config.m_PhysicTimeStamp;

    return true;
}

bool triebWerk::CEngine::Run()
{
    bool frameUpdate = false;
    bool physicUpdate = false;

    while ((frameUpdate | physicUpdate) == false)
    {
        float dt = m_pTime->Update();
        m_CurrentTime += dt;
        m_CurrentPhysicTime += dt;

        if (m_CurrentTime >= m_TimePerFrame)
        {
            m_CurrentTime -= m_TimePerFrame;
            frameUpdate = true;
            m_pTime->NextFrame();
        }

        if (m_CurrentPhysicTime >= m_PhysicTimeStamp)
        {
            m_CurrentPhysicTime -= m_PhysicTimeStamp;
            physicUpdate = true;
        }            
    }

    if (frameUpdate)
    {
        m_pInput->Update(m_pTime->GetUnscaledDeltaTime());
        ProcessWindowMessages();
        m_pResourceManager->Update();
        m_pDebug->Update();
        m_pWindow->UpdateWindow();
        m_pSceneManager->Update(true, physicUpdate);
		m_pSoundEngine->Update();
    }
    else if (physicUpdate)
    {
        m_pSceneManager->Update(false, true);
    }

    return m_IsRunning;
}

void triebWerk::CEngine::Shutdown()
{
	if(m_pSceneManager != nullptr)
		m_pSceneManager->Shutdown();
	if (m_pResourceManager != nullptr)
		m_pResourceManager->CleanUp();
	if (m_pFontManager != nullptr)
		m_pFontManager->Shutdown();
	if (m_pGraphics != nullptr)
		m_pGraphics->Shutdown();
	if (m_pRenderer != nullptr)
		m_pRenderer->Shutdown();
	if (m_pSoundEngine != nullptr)
		m_pSoundEngine->CleanUp();

	if(m_pFontManager != nullptr)
	 delete m_pFontManager;
	if (m_pSceneManager != nullptr)
		delete m_pSceneManager;
	if (m_pDebug != nullptr)
		delete m_pDebug;
	if (m_pInput != nullptr)
		delete m_pInput;
	if (m_pTime != nullptr)
		delete m_pTime;
	if (m_pWindow != nullptr)
		delete m_pWindow;
	if (m_pResourceManager != nullptr)
		delete m_pResourceManager;
	if (m_pGraphics != nullptr)
		delete m_pGraphics;
	if (m_pRenderer != nullptr)
		delete m_pRenderer;
	if (m_pSoundEngine != nullptr)
		delete m_pSoundEngine;
}

void triebWerk::CEngine::Stop()
{
    m_IsRunning = false;
}

void triebWerk::CEngine::ProcessWindowMessages()
{
    size_t messageCount = m_pWindow->GetWindowEventCount();

    for (size_t i = 0; i < messageCount; ++i)
    {
        MSG msg = m_pWindow->GetWindowEvent();
        switch (msg.message)
        {
        case WM_QUIT:
            m_IsRunning = false;
            break;

            //TODO: Listen only to finished resized
        case WM_SIZE:
        {
            m_pGraphics->UpdateSwapchainConfiguration();
            m_pSceneManager->m_pActiveScene->m_pScene->m_pWorld->m_pUIWorld->SetScreenResolution(LOWORD(msg.lParam), HIWORD(msg.lParam));
            break;
        }

        default:
            m_pInput->UpdateMSG(msg);
            break;
        }
    }
}
