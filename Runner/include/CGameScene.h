#pragma once
#include <CDifficultyChanger.h>
#include <CEnvironmentCreator.h>
#include <CPatternManager.h>
#include <CPlayer.h>

class CGameScene : public triebWerk::IScene
{
public:
    static float PointsPerMeter;

private:
    CDifficultyChanger m_DifficultyChanger;
    CEnvironmentCreator m_EnvironmentCreator;
    CPatternManager m_PatternManager;
	CPlayer* m_pPlayerScript;
    float m_LastPlayerPos;

public:
    CGameScene();
    ~CGameScene();

    void Start() final;
    void Update() final;
    void End() final;
    void Resume() final;

private:
    void CreatePlayer();
    void CreatePostEffects();
};
