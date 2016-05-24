#pragma once
#include <CEnvironmentCreator.h>
#include <CPatternManager.h>
#include <CPlayer.h>
#include <CValueUpdater.h>

class CGameScene : public triebWerk::IScene
{
private:
    CValueUpdater m_ValueUpdater;
    CEnvironmentCreator m_EnvironmentCreator;
    CPatternManager m_PatternManager;
    CPlayer* m_pPlayer;
    float m_LastPlayerPos;

public:
    CGameScene();
    ~CGameScene();

    void Start();
    void Update();
    void End();
    void Pause();
    void Resume();

private:
    void CreatePlayer();
};
