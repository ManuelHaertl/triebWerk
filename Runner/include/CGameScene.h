#pragma once
#include <IScene.h>
#include <CEnvironmentCreator.h>
#include <CPatternManager.h>
#include <CPlayer.h>

class CGameScene : public IScene
{
private:
    CEnvironmentCreator m_EnvironmentCreator;
    CPatternManager m_PatternManager;
    CPlayer* m_pPlayer;

public:
    CGameScene();
    ~CGameScene();

    void Start() override;
    void Update() override;
    void End() override;

private:
    void CreateTestCubes();
    void CreatePlayer();
};
