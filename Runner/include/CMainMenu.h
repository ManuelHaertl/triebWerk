#pragma once
#include <IMenu.h>
#include <CEngine.h>

class CMainMenu : public IMenu
{
private:
    const int ButtonCount = 5;

    triebWerk::CUIEntity* m_pBackground;
    triebWerk::CUIEntity* m_pHeader;

    triebWerk::CUIEntity* m_pButtonStart;
    triebWerk::CUIEntity* m_pButtonHighscore;
    triebWerk::CUIEntity* m_pButtonOptions;
    triebWerk::CUIEntity* m_pButtonExtras;
    triebWerk::CUIEntity* m_pButtonQuit;

    triebWerk::CUIEntity* m_pTextStart;
    triebWerk::CUIEntity* m_pTextHighscore;
    triebWerk::CUIEntity* m_pTextOptions;
    triebWerk::CUIEntity* m_pTextExtras;
    triebWerk::CUIEntity* m_pTextQuit;

    // Textures ----------------------------------------------------

    triebWerk::CTexture2D* m_pTextureRegularButton[3];
    triebWerk::CTexture2D* m_pTextureUnderlinedButton[3];

    // Materials ----------------------------------------------------

    triebWerk::CMaterial* m_pMaterialStandardUI;
    triebWerk::CMaterial* m_pMaterialStandardFont;

	// Sounds ----------------------------------------------------

	triebWerk::CSound* m_pBackgroundMusic;

    // Font -------------------------------------------------------

    triebWerk::CFont* m_pFontButton;

    int m_SelectedButton;
    size_t m_HoldValue;

    bool m_GoingIntoGame;
    float m_CurrentTime;

public:
    CMainMenu();
    ~CMainMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
    void Resume() final;

private:
    void UpdateGraphics();
};