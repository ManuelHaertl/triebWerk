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

public:
    CGameScene();
    ~CGameScene();

    void Start() override;
    void Update() override;
    void End() override;

private:
    void LoadAllPattern();
};
