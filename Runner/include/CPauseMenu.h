#pragma once
#include <CEngine.h>
#include <IMenu.h>
class CPauseMenu : public IMenu
{
private:
    const int MaxFieldIndex = 2;
    const int MaxButtonIndex = 3;

    triebWerk::CUIEntity* m_pBackground;
    triebWerk::CUIEntity* m_pFieldBG;
    triebWerk::CUIEntity* m_pFieldBGHover;
    triebWerk::CUIEntity* m_pButtonMainMenu;
    triebWerk::CUIEntity* m_pButtonResume;
    triebWerk::CUIEntity* m_pButtonOptions;

    triebWerk::CUIEntity* m_pArrowLeft;
    triebWerk::CUIEntity* m_pArrowRight;
    triebWerk::CUIEntity* m_pObjective;
    triebWerk::CUIEntity* m_pControls;

    triebWerk::CUIEntity* m_pFontMainMenu;
    triebWerk::CUIEntity* m_pFontResume;
    triebWerk::CUIEntity* m_pFontOptions;
    triebWerk::CUIEntity* m_pFontObjective1;
    triebWerk::CUIEntity* m_pFontObjective2;

    triebWerk::CTexture2D* m_pTextureUnderlinedButton[3];
    triebWerk::CTexture2D* m_pTextureArrowLeft[2];
    triebWerk::CTexture2D* m_pTextureArrowRight[2];

    IMenu* m_pSubMenu;
    bool m_IsInSubMenu;

    bool m_UpdateGraphics;
    bool m_IsPaused;
    bool m_IsOnButtons;
    int m_FieldIndex;

    int m_ButtonIndex;
    size_t m_HoldValue;

    // effect
    float m_CurrentMainMenuTime;

public:
    CPauseMenu();
    ~CPauseMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;

private:
    void CheckInput(const SUIInput& a_rInput);
    void UpdateGraphics();
    void DeleteSubScene();
};