#pragma once
#include <vector>
#include <IScene.h>
#include <CRenderer.h>
#include <CSceneHolder.h>

namespace triebWerk
{
    class CSceneManager
    {
    public:
        CSceneHolder* m_pActiveScene;

    private:
        CRenderer* m_pRenderer;
        float m_PhysicTimeStamp;

        std::vector<CSceneHolder*> m_Scenes;

    public:
        CSceneManager();
        ~CSceneManager();

    public:
        void Initialize(CRenderer* a_pRenderer, const float a_PhysicTimeStamp);
        void Update(const bool a_FrameUpdate, const bool a_PhysicUpdate);
        void Shutdown();

        void AddScene(IScene* a_pScene, const std::string a_Name);
        void RemoveScene(const std::string& a_Name);

        void SetActiveScene(const std::string& a_Name);

        void InitializeScene(const std::string& a_Name);
        void ShutdownScene(const std::string& a_Name);
    };
}