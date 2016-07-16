#pragma once
#include <CDifficultyChanger.h>
#include <CEnvironmentCreator.h>
#include <CPatternManager.h>
#include <CPlayer.h>
#include <CUI.h>
#include <CValueUpdater.h>

class CGameScene : public triebWerk::IScene
{
private:
    CValueUpdater m_ValueUpdater;
    CDifficultyChanger m_DifficultyChanger;
    CEnvironmentCreator m_EnvironmentCreator;
    CPatternManager m_PatternManager;
	CUI m_UI;
	CPlayer* m_pPlayer;
    float m_LastPlayerPos;

public:
    CGameScene();
    ~CGameScene();

    void Start();
    void Update();
    void End();
    void Resume();

private:
    void CreatePlayer();
    void CreateText();
};
