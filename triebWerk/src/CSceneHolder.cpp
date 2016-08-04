#include <CSceneHolder.h>

triebWerk::CSceneHolder::CSceneHolder(IScene* a_pScene, std::string m_Name) :
    m_pScene(a_pScene),
    m_Name(m_Name),
    m_IsInitialized(false)
{
    m_pScene->m_pWorld = &m_World;
}

triebWerk::CSceneHolder::~CSceneHolder()
{
}

void triebWerk::CSceneHolder::Initialize(CRenderer* a_pRenderer, const float a_PhysicTimeStamp)
{
    m_World.Initialize(a_pRenderer, a_PhysicTimeStamp);
    m_pScene->Start();
    m_IsInitialized = true;
	m_HasBeenActive = true;
}

void triebWerk::CSceneHolder::Update(const bool a_FrameUpdate, const bool a_PhysicUpdate)
{
    if (a_FrameUpdate)
        m_pScene->Update();

    m_World.Update(a_FrameUpdate, a_PhysicUpdate);
}

void triebWerk::CSceneHolder::Shutdown()
{
    m_pScene->End();
    m_World.Shutdown();
    m_IsInitialized = false;
    m_HasBeenActive = false;
}

void triebWerk::CSceneHolder::Pause()
{
    m_pScene->Pause();
}

void triebWerk::CSceneHolder::Resume()
{
    m_pScene->Resume();
}

bool triebWerk::CSceneHolder::IsInitialized() const
{
    return m_IsInitialized;
}

bool triebWerk::CSceneHolder::HasBeenActive() const
{
    return m_HasBeenActive;
}
