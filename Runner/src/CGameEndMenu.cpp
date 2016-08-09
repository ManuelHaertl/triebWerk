#include <CGameEndMenu.h>

#include <CGameInfo.h>
#include <CPostEffects.h>
#include <CHighscoreMenu.h>

CGameEndMenu::CGameEndMenu()
    : m_UpdateGraphics(false)
    , m_SelectedButton(1)
    , m_HoldValue(0)
    , m_LastState(false)
    , m_CurrentMainMenuTime(0.0f)
    , m_CurrentTryAgainTime(0.0f)
	, m_NewHighscore(false)
    , m_pSubScene(nullptr)
{
}

CGameEndMenu::~CGameEndMenu()
{
}

void CGameEndMenu::Start()
{
    auto font = twFontManager->GetFont(twResourceManager->GetFontFace("AGENCYB"), 30);
    auto fontBig = twFontManager->GetFont(twResourceManager->GetFontFace("AGENCYB"), 50);

    m_pTextureUnderlinedButton[0] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_normal");
    m_pTextureUnderlinedButton[1] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_hover");
    m_pTextureUnderlinedButton[2] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_pressed");

    // Background ----------------------------------------------------

    m_pBackground = twActiveUIWorld->CreateUIEntity();
    m_pBackground->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pBackground->m_Transform.SetPositionOffset(0.0f, 0.0f, 1.0f);
    m_pBackground->m_Transform.SetScale(100.0, 100.0, 0.0f);

    auto backgroundDrawable = twRenderer->CreateUIDrawable();
    backgroundDrawable->SetActive(false);
    backgroundDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("Vanish"));
    float value = 0.0f;
    backgroundDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
    backgroundDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_background"));

    m_pBackground->SetDrawable(backgroundDrawable);

    twActiveUIWorld->AddUIEntity(m_pBackground);

    // Logo -------------------------------------------------------

    m_pLogo = twActiveUIWorld->CreateUIEntity();
    m_pLogo->m_Transform.SetAnchorPoint(0.0f, 0.75f);

    auto logoDrawable = twRenderer->CreateUIDrawable();
    logoDrawable->SetActive(false);
    logoDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    logoDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_gametitel"));

    m_pLogo->SetDrawable(logoDrawable);

    twActiveUIWorld->AddUIEntity(m_pLogo);

    // ScoreBoard -------------------------------------------------------

    m_pScoreBoard = twActiveUIWorld->CreateUIEntity();
    m_pScoreBoard->m_Transform.SetAnchorPoint(0.0f, 0.0f);
	m_pScoreBoard->m_Transform.SetPositionOffset(0, 0, 0.4f);

    auto scoreBoardDrawable = twRenderer->CreateUIDrawable();
    scoreBoardDrawable->SetActive(false);
    scoreBoardDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    scoreBoardDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_score_normal"));

    m_pScoreBoard->SetDrawable(scoreBoardDrawable);

    twActiveUIWorld->AddUIEntity(m_pScoreBoard);

	//Crown

	m_pNewHighscoreCrown = twActiveUIWorld->CreateUIEntity();
	m_pNewHighscoreCrown->m_Transform.SetAnchorPoint(0.0f, 0.32f);
	m_pNewHighscoreCrown->m_Transform.SetPositionOffset(0, 0, 0.2f);

	auto scorecrownDrawable = twRenderer->CreateUIDrawable();
	scorecrownDrawable->SetActive(false);
	scorecrownDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
	scorecrownDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_score_crown"));

	m_pNewHighscoreCrown->SetDrawable(scorecrownDrawable);

	twActiveUIWorld->AddUIEntity(m_pNewHighscoreCrown);

	// Font Highscore

	m_pHighscoreFontElement = twActiveUIWorld->CreateUIEntity();
	m_pHighscoreFontElement->m_Transform.SetAnchorPoint(0.0f, 0.16f);
	m_pHighscoreFontElement->m_Transform.SetPositionOffset(0, 0, 0.2f);

	auto fontHighscoreEDrawable = twRenderer->CreateUIDrawable();
	fontHighscoreEDrawable->SetActive(false);
	fontHighscoreEDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("UIHighscore"));
	fontHighscoreEDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_score_highscore"));

	m_pHighscoreFontElement->SetDrawable(fontHighscoreEDrawable);

	twActiveUIWorld->AddUIEntity(m_pHighscoreFontElement);

	// New Font
	m_pNewFont = twActiveUIWorld->CreateUIEntity();
	m_pNewFont->m_Transform.SetAnchorPoint(0.0f, 0.4f);
	m_pNewFont->m_Transform.SetPositionOffset(0, 0, 0.1f);

	auto newFontDrawable = twRenderer->CreateUIDrawable();
	newFontDrawable->SetActive(false);
	newFontDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("UIHighscore"));
	newFontDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_score_new"));

	m_pNewFont->SetDrawable(newFontDrawable);

	twActiveUIWorld->AddUIEntity(m_pNewFont);

	// Score Font

	m_pScoreFontElement = twActiveUIWorld->CreateUIEntity();
	m_pScoreFontElement->m_Transform.SetAnchorPoint(0.0f, 0.16f);

	auto scoreDrawable = twRenderer->CreateUIDrawable();
	scoreDrawable->SetActive(false);
	scoreDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
	scoreDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_score_score"));

	m_pScoreFontElement->SetDrawable(scoreDrawable);

	twActiveUIWorld->AddUIEntity(m_pScoreFontElement);

    // Font ScoreBoard -------------------------------------------

    m_pFontScoreBoard = twActiveUIWorld->CreateUIEntity();
    m_pFontScoreBoard->m_Transform.SetAnchorPoint(0.0f, -0.07f);
    m_pFontScoreBoard->m_Transform.SetPositionOffset(18.0f, -17.0f, -0.1f);

    auto scoreBoardText = twFontManager->CreateText();
    scoreBoardText->Set(fontBig, "0", 1.0f);

    auto scoreBoardTextDrawable = twRenderer->CreateFontDrawable();
    scoreBoardTextDrawable->SetActive(false);
    scoreBoardTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    scoreBoardTextDrawable->m_pText = scoreBoardText;
    scoreBoardTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontScoreBoard->SetDrawable(scoreBoardTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontScoreBoard);

    // Button Main Menu --------------------------------------------

    m_pButtonMainMenu = twActiveUIWorld->CreateUIEntity();
    m_pButtonMainMenu->m_Transform.SetAnchorPoint(-0.474f, -0.75f);
    m_pButtonMainMenu->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonMainMenuDrawable = twRenderer->CreateUIDrawable();
    buttonMainMenuDrawable->SetActive(false);
    buttonMainMenuDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    buttonMainMenuDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonMainMenu->SetDrawable(buttonMainMenuDrawable);

    // Font Main Menu ------------------------------------------- 

    m_pFontMainMenu = twActiveUIWorld->CreateUIEntity();
    m_pFontMainMenu->m_Transform.SetAnchorPoint(-0.474f, -0.75f);
    m_pFontMainMenu->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto mainMenuText = twFontManager->CreateText();
    mainMenuText->Set(font, "Main Menu", 1.0f);

    auto mainMenuTextDrawable = twRenderer->CreateFontDrawable();
    mainMenuTextDrawable->SetActive(false);
    mainMenuTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    mainMenuTextDrawable->m_pText = mainMenuText;
    mainMenuTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontMainMenu->SetDrawable(mainMenuTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontMainMenu);

    twActiveUIWorld->AddUIEntity(m_pButtonMainMenu);

    // Button Resume --------------------------------------------

    m_pButtonTryAgain = twActiveUIWorld->CreateUIEntity();
    m_pButtonTryAgain->m_Transform.SetAnchorPoint(0.0f, -0.75f);
    m_pButtonTryAgain->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonTryAgainDrawable = twRenderer->CreateUIDrawable();
    buttonTryAgainDrawable->SetActive(false);
    buttonTryAgainDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    buttonTryAgainDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1]);

    m_pButtonTryAgain->SetDrawable(buttonTryAgainDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonTryAgain);

    // Font Try Again ------------------------------------------- 

    m_pFontTryAgain = twActiveUIWorld->CreateUIEntity();
    m_pFontTryAgain->m_Transform.SetAnchorPoint(0.0f, -0.75f);
    m_pFontTryAgain->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto tryAgainText = twFontManager->CreateText();
    tryAgainText->Set(font, "Try Again", 1.0f);

    auto tryAgainTextDrawable = twRenderer->CreateFontDrawable();
    tryAgainTextDrawable->SetActive(false);
    tryAgainTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    tryAgainTextDrawable->m_pText = tryAgainText;
    tryAgainTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontTryAgain->SetDrawable(tryAgainTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontTryAgain);

    // Button Highscore --------------------------------------------

    m_pButtonHighscore = twActiveUIWorld->CreateUIEntity();
    m_pButtonHighscore->m_Transform.SetAnchorPoint(0.474f, -0.75f);
    m_pButtonHighscore->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonHighscoreDrawable = twRenderer->CreateUIDrawable();
    buttonHighscoreDrawable->SetActive(false);
    buttonHighscoreDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    buttonHighscoreDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonHighscore->SetDrawable(buttonHighscoreDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonHighscore);

    // Font Highscore ------------------------------------------- 

    m_pFontHighscore = twActiveUIWorld->CreateUIEntity();
    m_pFontHighscore->m_Transform.SetAnchorPoint(0.474f, -0.75f);
    m_pFontHighscore->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto highscoreText = twFontManager->CreateText();
    highscoreText->Set(font, "Highscore", 1.0f);

    auto highscoreTextDrawable = twRenderer->CreateFontDrawable();
    highscoreTextDrawable->SetActive(false);
    highscoreTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    highscoreTextDrawable->m_pText = highscoreText;
    highscoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontHighscore->SetDrawable(highscoreTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontHighscore);
}

void CGameEndMenu::Update(const SUIInput& a_rInput)
{
    if (m_CurrentMainMenuTime > 0.0f)
    {
        m_CurrentMainMenuTime -= twTime->GetDeltaTime();
        if (m_CurrentMainMenuTime <= 0.0f)
        {
            m_CurrentMainMenuTime = 0.0f;
            twSceneManager->SetActiveScene("Menu");
        }

        return;
    }
    else if (m_CurrentTryAgainTime > 0.0f)
    {
        m_CurrentTryAgainTime -= twTime->GetDeltaTime();
        if (m_CurrentTryAgainTime <= 0.0f)
        {
            m_CurrentTryAgainTime = 0.0f;
            CGameInfo::Instance().m_RestartGame = true;
        }

        return;
    }

	float t = twTime->GetTimeSinceStartup();
	reinterpret_cast<triebWerk::CUIDrawable*>(m_pHighscoreFontElement->GetDrawable())->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &t);
	reinterpret_cast<triebWerk::CUIDrawable*>(m_pNewFont->GetDrawable())->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &t);

	DirectX::XMFLOAT2 pos = m_pNewHighscoreCrown->m_Transform.GetAnchorPoint();
	pos.y = ((sin(t) * 0.2f + 0.4) * 0.1f) + 0.32f;
	m_pNewHighscoreCrown->m_Transform.SetAnchorPoint(pos);

	DirectX::XMFLOAT2 pos2 = m_pNewFont->m_Transform.GetAnchorPoint();
	pos2.y = ((sin(t) * 0.2f + 0.4) * 0.1f) + 0.4f;
	m_pNewFont->m_Transform.SetAnchorPoint(pos2);

    // check when the player died
    if (m_LastState != CGameInfo::Instance().m_IsPlayerDead)
    {
        m_LastState = CGameInfo::Instance().m_IsPlayerDead;
        m_SelectedButton = 1;
        m_UpdateGraphics = true;

    }

    if (!CGameInfo::Instance().m_IsPlayerDead)
    {
        UpdateGraphics();
        return;
    }
    
    // menu change
    if (CGameInfo::Instance().m_ChangeMenu)
    {
        CGameInfo::Instance().m_ChangeMenu = false;

        switch (CGameInfo::Instance().m_Menu)
        {
        case EMenus::Main:
            DeleteSubScene();

            m_pScoreBoard->GetDrawable()->SetActive(true);
            m_pFontScoreBoard->GetDrawable()->SetActive(true);
			m_pScoreFontElement->GetDrawable()->SetActive(!CGameInfo::Instance().m_Highscore.IsHighscore());
			m_pHighscoreFontElement->GetDrawable()->SetActive(CGameInfo::Instance().m_Highscore.IsHighscore());
			m_pNewFont->GetDrawable()->SetActive(CGameInfo::Instance().m_Highscore.IsHighscore());
			m_pNewHighscoreCrown->GetDrawable()->SetActive(CGameInfo::Instance().m_Highscore.IsHighscore());
            break;
        case EMenus::Highscore:
            m_pSubScene = new CHighscoreMenu();
            m_pSubScene->Start();

            m_pScoreBoard->GetDrawable()->SetActive(false);
            m_pFontScoreBoard->GetDrawable()->SetActive(false);
			m_pScoreFontElement->GetDrawable()->SetActive(false);
			m_pHighscoreFontElement->GetDrawable()->SetActive(false);
            break;
        }
    }

    if (m_pSubScene != nullptr)
        m_pSubScene->Update(a_rInput);
    else
        CheckInput(a_rInput);

    UpdateGraphics();
}

void CGameEndMenu::End()
{
    DeleteSubScene();
}

void CGameEndMenu::CheckInput(const SUIInput& a_rInput)
{
    // button hold down
    int value;
    a_rInput.m_ButtonHold ? value = 1 : value = 0;

    if (m_HoldValue != value)
    {
        m_HoldValue = value;
        m_UpdateGraphics = true;
    }

    // Left and right
    if (a_rInput.m_Left)
    {
        m_SelectedButton--;
        if (m_SelectedButton < 0)
            m_SelectedButton = MaxButtonIndex - 1;

        m_UpdateGraphics = true;
    }
    else if (a_rInput.m_Right)
    {
        m_SelectedButton++;
        if (m_SelectedButton == MaxButtonIndex)
            m_SelectedButton = 0;

        m_UpdateGraphics = true;
    }

    if (a_rInput.m_Select)
    {
        switch (m_SelectedButton)
        {
        case 0:
            m_CurrentMainMenuTime = CPostEffects::GameStartTime / 2.0f;
            CGameInfo::Instance().m_EffectGoingIntoGame = true;
            break;
        case 1:
            m_CurrentTryAgainTime = CPostEffects::TryAgainTime / 2.0f;
            CGameInfo::Instance().m_EffectTryAgain = true;
            break;
        case 2:
            CGameInfo::Instance().m_ChangeMenu = true;
            CGameInfo::Instance().m_Menu = EMenus::Highscore;
            break;
        }
    }
}

void CGameEndMenu::UpdateGraphics()
{
    if (!m_UpdateGraphics)
        return;

    m_UpdateGraphics = false;

    // Hide / show all elemenets depenging on if the game is paused
    bool active = CGameInfo::Instance().m_IsPlayerDead;

    m_pBackground->GetDrawable()->SetActive(active);
    m_pLogo->GetDrawable()->SetActive(active);
    m_pScoreBoard->GetDrawable()->SetActive(active);
    m_pButtonMainMenu->GetDrawable()->SetActive(active);
    m_pButtonTryAgain->GetDrawable()->SetActive(active);
    m_pButtonHighscore->GetDrawable()->SetActive(active);
    m_pFontScoreBoard->GetDrawable()->SetActive(active);
    m_pFontMainMenu->GetDrawable()->SetActive(active);
    m_pFontTryAgain->GetDrawable()->SetActive(active);
    m_pFontHighscore->GetDrawable()->SetActive(active);

	m_pScoreFontElement->GetDrawable()->SetActive(active && !CGameInfo::Instance().m_Highscore.IsHighscore());
	m_pHighscoreFontElement->GetDrawable()->SetActive(active && CGameInfo::Instance().m_Highscore.IsHighscore());
	m_pNewHighscoreCrown->GetDrawable()->SetActive(active && CGameInfo::Instance().m_Highscore.IsHighscore());
	m_pNewFont->GetDrawable()->SetActive(active && CGameInfo::Instance().m_Highscore.IsHighscore());

    // the 3 buttons' states
    size_t index[3] = { 0,0,0 };

    index[m_SelectedButton]++;
    index[m_SelectedButton] += m_HoldValue;

    ((triebWerk::CUIDrawable*)m_pButtonMainMenu->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[0]]);
    ((triebWerk::CUIDrawable*)m_pButtonTryAgain->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[1]]);
    ((triebWerk::CUIDrawable*)m_pButtonHighscore->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[2]]);

    // Score
    ((triebWerk::CFontDrawable*)m_pFontScoreBoard->GetDrawable())->m_pText->SetText(std::to_string((size_t)CGameInfo::Instance().m_TotalPoints));
}

void CGameEndMenu::DeleteSubScene()
{
    if (m_pSubScene != nullptr)
    {
        m_pSubScene->End();
        delete m_pSubScene;
        m_pSubScene = nullptr;
    }
}
