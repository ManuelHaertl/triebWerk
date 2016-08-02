#pragma once
#include <CEngine.h>
#include <IMenu.h>
#include <CMenuBackgroundScene.h>

class CMenuScene : public triebWerk::IScene
{
private:
    CMenuBackgroundScene m_MenuBackgroundScene;
    SUIInput m_UIInput;
    IMenu* m_pCurrentMenu;

public:
    CMenuScene();
    ~CMenuScene();

    void Start() final;
    void Update() final;
    void End() final;
    void Resume() final;

private:
    void CheckInput();
    void SetCurrentMenu(IMenu* a_pMenu);
    void CreatePostEffects();
};