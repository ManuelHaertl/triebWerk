#pragma once
#include <IScene.h>
#include <CPattern.h>
#include <CPatternLoader.h>
#include <CPlayer.h>

class CGameScene : public IScene
{
private:
    CPattern* m_pPattern;
    size_t m_PatternCount;
    int m_MinDifficulty;
    int m_MaxDifficulty;
    int m_MinPriority;
    int m_MaxPriority;

public:
    CGameScene();
    ~CGameScene();

    void Start() override;
    void Update() override;
    void End() override;

private:
    void LoadAllPattern();
    void CreateFloorAndSidewalls();
    void CreatePattern();
    void CreateTestCubes();
    void CreatePlayer();
};
