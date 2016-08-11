#pragma once
#include <IMenu.h>
#include <CEngine.h>

class CGameEndMenu : public IMenu
{
private:
    const int MaxButtonIndex = 3;
    const int MaxColorIndex = 5;
    const DirectX::XMFLOAT3 ScoreColors[5] = {
        DirectX::XMFLOAT3(0.0f, 0.804f, 0.855f),
        DirectX::XMFLOAT3(0.047f, 0.663f, 0.0f),
        DirectX::XMFLOAT3(0.55f, 0.0f, 0.282f),
        DirectX::XMFLOAT3(1.0f, 0.36f, 0.109f),
        DirectX::XMFLOAT3(0.0f, 0.294f, 0.737f)};

    triebWerk::CTexture2D* m_pTextureUnderlinedButton[3];
    triebWerk::CTexture2D* m_pTextureColorBox[5][3];

    triebWerk::CUIEntity* m_pBackground;
    triebWerk::CUIEntity* m_pLogo;
    triebWerk::CUIEntity* m_pScoreBoard;
	triebWerk::CUIEntity* m_pNewHighscoreCrown;
	triebWerk::CUIEntity* m_pNewFont;
	triebWerk::CUIEntity* m_pHighscoreFontElement;
	triebWerk::CUIEntity* m_pScoreFontElement;

    triebWerk::CUIEntity* m_pButtonMainMenu;
    triebWerk::CUIEntity* m_pButtonTryAgain;
    triebWerk::CUIEntity* m_pButtonHighscore;

    triebWerk::CUIEntity* m_pFontScoreBoard;

    triebWerk::CUIEntity* m_pFontMainMenu;
    triebWerk::CUIEntity* m_pFontTryAgain;
    triebWerk::CUIEntity* m_pFontHighscore;

    triebWerk::CUIEntity* m_pColor1;
    triebWerk::CUIEntity* m_pColor2;
    triebWerk::CUIEntity* m_pColor3;
    triebWerk::CUIEntity* m_pColor4;
    triebWerk::CUIEntity* m_pColor5;
    triebWerk::CUIEntity* m_pFontTop5;
    triebWerk::CUIEntity* m_pFontYourRank;
    triebWerk::CUIEntity* m_pFontPickAColor;

    bool m_UpdateGraphics;
    bool m_SelectingColor;

    int m_SelectedButton;
    int m_SelectedColorButton;
    int m_HoldValue;
    bool m_LastState;
	bool m_NewHighscore;

    // effects
    float m_CurrentMainMenuTime;
    float m_CurrentTryAgainTime;

    IMenu* m_pSubScene;

public:
    CGameEndMenu();
    ~CGameEndMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;

private:
    void CheckInput(const SUIInput& a_rInput);
    void UpdateGraphics();
    void DeleteSubScene();
};