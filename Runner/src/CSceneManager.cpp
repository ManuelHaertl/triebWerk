#include <CSceneManager.h>

CSceneManager::CSceneManager() :
    m_pActiveScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Initialize()
{
    twEngine.m_pResourceManager->LoadAllFilesInFolder("data");
    m_ValueUpdater.Start();
}

bool CSceneManager::Update()
{
    if (m_pActiveScene != nullptr)
        m_pActiveScene->Update();

    m_ValueUpdater.Update();
    return true;
}

void CSceneManager::Shutdown()
{
    m_ValueUpdater.End();
    EndActiveScene();
}

void CSceneManager::ChangeScene(const EScenes::Type a_SceneType)
{
    EndActiveScene();

    switch (a_SceneType)
    {
    case EScenes::Game:
        StartScene(new CGameScene());
        break;
    case EScenes::Debug:
        StartScene(new CDebugScene());
        break;
    default:
        break;
    }
}

void CSceneManager::StartScene(IScene* const a_pScene)
{
    m_pActiveScene = a_pScene;
    m_pActiveScene->Start();
}

void CSceneManager::EndActiveScene()
{
    if (m_pActiveScene != nullptr)
    {
        m_pActiveScene->End();
        delete m_pActiveScene;
        m_pActiveScene = nullptr;
    }
}
