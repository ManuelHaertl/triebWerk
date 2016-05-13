#pragma once
#include <IScene.h>
#include <CPattern.h>
#include <CPatternManager.h>
#include <CPlayer.h>

class CGameScene : public IScene
{
private:
    CPatternManager m_PatternManager;
    CPlayer* m_pPlayer;

public:
    CGameScene();
    ~CGameScene();

    void Start() override;
    void Update() override;
    void End() override;

private:
    void CreateFloorAndSidewalls();
    void CreateTestCubes();
    void CreatePlayer();
};
