#pragma once
#include <IScene.h>
#include <EScenes.h>
#include <CGameScene.h>
#include <CValueUpdater.h>

class CSceneManager
{
private:
    IScene* m_pActiveScene;
    CValueUpdater m_ValueUpdater;

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