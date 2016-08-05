#pragma once
#include <IMenu.h>
#include <CEngine.h>

class CMainMenu : public IMenu
{
private:
    const int ButtonCount = 5;
    const int ExtrasCount = 2;
    const float LerpTime = 0.3f;

    triebWerk::CUIEntity* m_pBackground;
    triebWerk::CUIEntity* m_pHeader;

    triebWerk::CUIEntity* m_pButtonStart;
    triebWerk::CUIEntity* m_pButtonHighscore;
    triebWerk::CUIEntity* m_pButtonOptions;
    triebWerk::CUIEntity* m_pButtonExtras;
    triebWerk::CUIEntity* m_pButtonQuit;
    triebWerk::CUIEntity* m_pButtonManual;
    triebWerk::CUIEntity* m_pButtonCredits;

    triebWerk::CUIEntity* m_pTextStart;
    triebWerk::CUIEntity* m_pTextHighscore;
    triebWerk::CUIEntity* m_pTextOptions;
    triebWerk::CUIEntity* m_pTextExtras;
    triebWerk::CUIEntity* m_pTextQuit;
    triebWerk::CUIEntity* m_pTextManual;
    triebWerk::CUIEntity* m_pTextCredits;

    // Textures ----------------------------------------------------

    triebWerk::CTexture2D* m_pTextureRegularButton[3];
    triebWerk::CTexture2D* m_pTextureUnderlinedButton[3];

    // Materials ----------------------------------------------------

    triebWerk::CMaterial* m_pMaterialStandardUI;
    triebWerk::CMaterial* m_pMaterialStandardFont;

    // Font -------------------------------------------------------

    triebWerk::CFont* m_pFontButton;

    bool m_UpdateGraphics;

    // current button states
    bool m_IsOnMainButtons;
    bool m_IsOnExtrasButtons;
    int m_SelectedButton;
    int m_SelectedExtrasButton;
    size_t m_HoldValue;

    // status for graphical effects
    bool m_GoingIntoGame;
    float m_CurrentTime;
    bool m_LerpToExtras;
    bool m_LerpFromExtras;
    float m_CurrentLerpTime;

public:
    CMainMenu();
    ~CMainMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
    void Resume() final;

private:
    void CheckInput(const SUIInput& a_rInput);
    void UpdateGraphics();
    void OpenExtras();
    void CloseExtras();
    void LerpToExtras();
    void LerpFromExtras();
};