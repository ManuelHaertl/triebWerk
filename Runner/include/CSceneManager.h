#pragma once
#include <IScene.h>
#include <EScenes.h>
#include <CGameScene.h>

class CSceneManager
{
private:
    IScene* m_pActiveScene;

public:
    CSceneManager();
    ~CSceneManager();

    void Initialize();
    bool Update();
    void Shutdown();

    void ChangeScene(const EScenes::Type a_SceneType);

private:
    void StartScene(IScene* const a_pScene);
    void EndActiveScene();
};