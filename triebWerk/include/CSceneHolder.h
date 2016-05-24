#pragma once
#include <CWorld.h>
#include <CRenderer.h>
#include <IScene.h>

namespace triebWerk
{
    class CSceneHolder
    {
    public:
        IScene* m_pScene;
        std::string m_Name;

    private:
        bool m_IsInitialized;
        bool m_HasBeenActive;
        CWorld m_World;

    public:
        CSceneHolder(IScene* a_pScene, std::string m_Name);
        ~CSceneHolder();

        void Initialize(CRenderer* a_pRenderer, const float a_PhysicTimeStamp);
        void Update(const bool a_FrameUpdate, const bool a_PhysicUpdate);
        void Shutdown();
        void Pause();
        void Resume();

        bool IsInitialized() const;
        bool HasBeenActive() const;
    };
}