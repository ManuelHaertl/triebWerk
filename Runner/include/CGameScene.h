#pragma once
#include <CDifficultyChanger.h>
#include <CEnvironmentCreator.h>
#include <CPatternManager.h>
#include <CPlayer.h>
#include <CInGameUI.h>

class CGameScene : public triebWerk::IScene
{
public:
    static float PointsPerMeter;

private:
    CDifficultyChanger m_DifficultyChanger;
    CEnvironmentCreator m_EnvironmentCreator;
    CPatternManager m_PatternManager;
    CInGameUI m_IngameUI;
	CPlayer* m_pPlayerScript;
    float m_LastPlayerPos;

	//Audio
	std::vector<triebWerk::CSound*> m_Music;
	int m_LastAudioIndex;

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
	void PlayRandomSong(bool a_FadeIn);
};
