#include <CSceneManager.h>

triebWerk::CSceneManager::CSceneManager() :
    m_pRenderer(nullptr),
    m_PhysicTimeStamp(0.0f),
    m_pActiveScene(nullptr)
{
}

triebWerk::CSceneManager::~CSceneManager()
{
}

void triebWerk::CSceneManager::Initialize(CRenderer* a_pRenderer, const float a_PhysicTimeStamp)
{
    Shutdown();

    m_pRenderer = a_pRenderer;
    m_PhysicTimeStamp = a_PhysicTimeStamp;
}

void triebWerk::CSceneManager::Update(const bool a_FrameUpdate, const bool a_PhysicUpdate)
{
    if (m_pActiveScene != nullptr)
        m_pActiveScene->Update(a_FrameUpdate, a_PhysicUpdate);
}

void triebWerk::CSceneManager::Shutdown()
{
    // go through all scenes
    size_t size = m_Scenes.size();
    for (size_t i = 0; i < size; ++i)
    {
        CSceneHolder* sceneHolder = m_Scenes[i];

        // shut them down
        sceneHolder->Shutdown();

        // and then delete them
        delete sceneHolder->m_pScene;
        delete sceneHolder;
    }

    m_Scenes.clear();
}

void triebWerk::CSceneManager::AddScene(triebWerk::IScene* a_pScene, const std::string a_Name)
{
    // check if the scene hasn't already been added
    size_t size = m_Scenes.size();
    for (size_t i = 0; i < size; ++i)
    {
        CSceneHolder* sceneHolder = m_Scenes[i];
        if (sceneHolder->m_pScene == a_pScene)
        {
            return;
        }
    }

    // add it
    CSceneHolder* sceneHolder = new CSceneHolder(a_pScene, a_Name);
    m_Scenes.push_back(sceneHolder);
}

void triebWerk::CSceneManager::RemoveScene(const std::string& a_Name)
{
    // search for the scene
    size_t size = m_Scenes.size();
    for (size_t i = 0; i < size; ++i)
    {
        CSceneHolder* sceneHolder = m_Scenes[i];
        if (sceneHolder->m_Name == a_Name)
        {
            // first shut it down
            sceneHolder->Shutdown();
            m_Scenes.erase(m_Scenes.begin() + i);
           
            // then delete it
            delete sceneHolder->m_pScene;
            delete sceneHolder;
        }
    }
}

void triebWerk::CSceneManager::SetActiveScene(const std::string& a_Name)
{
    // check if the scene isn't already the active scene
    if (m_pActiveScene != nullptr && m_pActiveScene->m_Name == a_Name)
        return;

    // check if the scene exists in the engine
    size_t size = m_Scenes.size();
    for (size_t i = 0; i < size; ++i)
    {
        CSceneHolder* sceneHolder = m_Scenes[i];
        if (sceneHolder->m_Name == a_Name)
        {
            // tell the old active scene that its now paused
            if (m_pActiveScene != nullptr)
                m_pActiveScene->Pause();

            // make it the active scene
            m_pActiveScene = sceneHolder;

            // initialize it if it hasn't been initalized yet
            if (!sceneHolder->IsInitialized())
                sceneHolder->Initialize(m_pRenderer, m_PhysicTimeStamp);
            else if (sceneHolder->HasBeenActive())
                sceneHolder->Resume();

            return;
        }
    }
}

void triebWerk::CSceneManager::InitializeScene(const std::string& a_Name)
{
    // check if the scene exists in the engine
    size_t size = m_Scenes.size();
    for (size_t i = 0; i < size; ++i)
    {
        CSceneHolder* sceneHolder = m_Scenes[i];
        if (sceneHolder->m_Name == a_Name && !sceneHolder->IsInitialized())
        {
            // initialize it
            sceneHolder->Initialize(m_pRenderer, m_PhysicTimeStamp);
            return;
        }
    }
}

void triebWerk::CSceneManager::ShutdownScene(const std::string& a_Name)
{
    // check if the scene exists in the engine
    size_t size = m_Scenes.size();
    for (size_t i = 0; i < size; ++i)
    {
        CSceneHolder* sceneHolder = m_Scenes[i];
        if (sceneHolder->m_Name == a_Name && sceneHolder->IsInitialized())
        {
            // shut it down
            sceneHolder->Shutdown();
            return;
        }
    }
}
