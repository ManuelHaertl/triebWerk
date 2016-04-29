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
}

bool CSceneManager::Update()
{
    if (m_pActiveScene != nullptr)
        m_pActiveScene->Update();

    return true;
}

void CSceneManager::Shutdown()
{
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
