#include <CMainMenu.h>

#include <CGameInfo.h>
#include <CPostEffects.h>

CMainMenu::CMainMenu()
    : m_UpdateGraphics(false)
    , m_IsOnMainButtons(true)
    , m_IsOnExtrasButtons(false)
    , m_SelectedButton(0)
    , m_SelectedExtrasButton(0)
    , m_HoldValue(0)
    , m_GoingIntoGame(false)
    , m_CurrentTime(0.0f)
    , m_LerpToExtras(false)
    , m_LerpFromExtras(false)
    , m_CurrentLerpTime(0.0f)
{
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::Start()
{
    m_pTextureRegularButton[0] = twResourceManager->GetTexture2D("T_ui_regularbutton_normal");
    m_pTextureRegularButton[1] = twResourceManager->GetTexture2D("T_ui_regularbutton_hover");
    m_pTextureRegularButton[2] = twResourceManager->GetTexture2D("T_ui_regularbutton_pressed");

    m_pTextureUnderlinedButton[0] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_normal");
    m_pTextureUnderlinedButton[1] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_hover");
    m_pTextureUnderlinedButton[2] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_pressed");

    m_pMaterialStandardUI = twResourceManager->GetMaterial("StandardUI");
    m_pMaterialStandardFont = twResourceManager->GetMaterial("StandardFont");

    m_pFontButton = twFontManager->GetFont(twResourceManager->GetFontFace("AGENCYB"), 30);

    // Background --------------------------------------------

    m_pBackground = twActiveUIWorld->CreateUIEntity();
    m_pBackground->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pBackground->m_Transform.SetPositionOffset(0.0f, 0.0f, 1.0f);
    m_pBackground->m_Transform.SetScale(100.0, 100.0, 0.0f);

    auto backgroundDrawable = twRenderer->CreateUIDrawable();
    backgroundDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("Vanish"));
    float value = 0.0f;
    backgroundDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
    backgroundDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_background"));

    m_pBackground->SetDrawable(backgroundDrawable);

    twActiveUIWorld->AddUIEntity(m_pBackground);

    // Header --------------------------------------------

    m_pHeader = twActiveUIWorld->CreateUIEntity();
    m_pHeader->m_Transform.SetAnchorPoint(0.0f, 0.8f);

    auto headerDrawable = twRenderer->CreateUIDrawable();
    headerDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    headerDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_gametitel"));

    m_pHeader->SetDrawable(headerDrawable);

    twActiveUIWorld->AddUIEntity(m_pHeader);

    // Button Start ----------------------------------------

    m_pButtonStart = twActiveUIWorld->CreateUIEntity();
    m_pButtonStart->m_Transform.SetAnchorPoint(-0.7f, -0.8f);
    m_pButtonStart->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);


    auto buttonStartDrawable = twRenderer->CreateUIDrawable();
    buttonStartDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    buttonStartDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1]);

    m_pButtonStart->SetDrawable(buttonStartDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonStart);

    // Font Start ------------------------------------------- 

    auto m_pTextStart = twActiveUIWorld->CreateUIEntity();
    m_pTextStart->m_Transform.SetAnchorPoint(-0.7f, -0.8f);
    m_pTextStart->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto startText = twFontManager->CreateText();
    startText->Set(m_pFontButton, "Start", 1.0f);

    auto startTextDrawable = twRenderer->CreateFontDrawable();
    startTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    startTextDrawable->m_pText = startText;
    startTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pTextStart->SetDrawable(startTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextStart);

    // Button Highscore ----------------------------------------

    m_pButtonHighscore = twActiveUIWorld->CreateUIEntity();
    m_pButtonHighscore->m_Transform.SetAnchorPoint(-0.35f, -0.8f);
    m_pButtonHighscore->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonHighscoreDrawable = twRenderer->CreateUIDrawable();
    buttonHighscoreDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    buttonHighscoreDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonHighscore->SetDrawable(buttonHighscoreDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonHighscore);

    // Font Highscore ------------------------------------------- 

    m_pTextHighscore = twActiveUIWorld->CreateUIEntity();
    m_pTextHighscore->m_Transform.SetAnchorPoint(-0.35f, -0.8f);
    m_pTextHighscore->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto highscoreText = twFontManager->CreateText();
    highscoreText->Set(m_pFontButton, "Highscore", 1.0f);

    auto highscoreTextDrawable = twRenderer->CreateFontDrawable();
    highscoreTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    highscoreTextDrawable->m_pText = highscoreText;
    highscoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pTextHighscore->SetDrawable(highscoreTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextHighscore);

    // Button Options ----------------------------------------

    m_pButtonOptions = twActiveUIWorld->CreateUIEntity();
    m_pButtonOptions->m_Transform.SetAnchorPoint(0.0f, -0.8f);
    m_pButtonOptions->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonOptionsDrawable = twRenderer->CreateUIDrawable();
    buttonOptionsDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    buttonOptionsDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonOptions->SetDrawable(buttonOptionsDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonOptions);

    // Font Options ------------------------------------------- 

    m_pTextOptions = twActiveUIWorld->CreateUIEntity();
    m_pTextOptions->m_Transform.SetAnchorPoint(0.0f, -0.8f);
    m_pTextOptions->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto optionsText = twFontManager->CreateText();
    optionsText->Set(m_pFontButton, "Options", 1.0f);

    auto optionsTextDrawable = twRenderer->CreateFontDrawable();
    optionsTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    optionsTextDrawable->m_pText = optionsText;
    optionsTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pTextOptions->SetDrawable(optionsTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextOptions);

    // Button Extras ----------------------------------------

    m_pButtonExtras = twActiveUIWorld->CreateUIEntity();
    m_pButtonExtras->m_Transform.SetAnchorPoint(0.35f, -0.8f);
    m_pButtonExtras->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonExtrasDrawable = twRenderer->CreateUIDrawable();
    buttonExtrasDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    buttonExtrasDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonExtras->SetDrawable(buttonExtrasDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonExtras);

    // Font Extras -------------------------------------------

    m_pTextExtras = twActiveUIWorld->CreateUIEntity();
    m_pTextExtras->m_Transform.SetAnchorPoint(0.35f, -0.8f);
    m_pTextExtras->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto extrasText = twFontManager->CreateText();
    extrasText->Set(m_pFontButton, "Extras", 1.0f);

    auto extrasTextDrawable = twRenderer->CreateFontDrawable();
    extrasTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    extrasTextDrawable->m_pText = extrasText;
    extrasTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pTextExtras->SetDrawable(extrasTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextExtras);

    // Button Quit ----------------------------------------

    m_pButtonQuit = twActiveUIWorld->CreateUIEntity();
    m_pButtonQuit->m_Transform.SetAnchorPoint(0.7f, -0.8f);
    m_pButtonQuit->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonQuitDrawable = twRenderer->CreateUIDrawable();
    buttonQuitDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    buttonQuitDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonQuit->SetDrawable(buttonQuitDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonQuit);

    // Font Quit -------------------------------------------

    m_pTextQuit = twActiveUIWorld->CreateUIEntity();
    m_pTextQuit->m_Transform.SetAnchorPoint(0.7f, -0.8f);
    m_pTextQuit->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto quitText = twFontManager->CreateText();
    quitText->Set(m_pFontButton, "Quit", 1.0f);

    auto quitTextDrawable = twRenderer->CreateFontDrawable();
    quitTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    quitTextDrawable->m_pText = quitText;
    quitTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pTextQuit->SetDrawable(quitTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextQuit);

    // Button Manual ----------------------------------------

    m_pButtonManual = twActiveUIWorld->CreateUIEntity();
    m_pButtonManual->m_Transform.SetAnchorPoint(0.35f, -0.8f);
    m_pButtonManual->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.7f);

    auto buttonManualDrawable = twRenderer->CreateUIDrawable();
    buttonManualDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    buttonManualDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureRegularButton[0]);

    m_pButtonManual->SetDrawable(buttonManualDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonManual);

    // Font Manual -------------------------------------------

    m_pTextManual = twActiveUIWorld->CreateUIEntity();
    m_pTextManual->m_Transform.SetAnchorPoint(0.35f, -0.8f);
    m_pTextManual->m_Transform.SetPositionOffset(10.0f, -25.0f, 0.6f);

    auto manualText = twFontManager->CreateText();
    manualText->Set(m_pFontButton, "Manual", 1.0f);

    auto manualTextDrawable = twRenderer->CreateFontDrawable();
    manualTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    manualTextDrawable->m_pText = manualText;
    manualTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pTextManual->SetDrawable(manualTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextManual);

    // Button Credits ----------------------------------------

    m_pButtonCredits = twActiveUIWorld->CreateUIEntity();
    m_pButtonCredits->m_Transform.SetAnchorPoint(0.35f, -0.8f);
    m_pButtonCredits->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.9f);

    auto buttonCreditsDrawable = twRenderer->CreateUIDrawable();
    buttonCreditsDrawable->m_Material.SetMaterial(m_pMaterialStandardUI);
    buttonCreditsDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureRegularButton[0]);

    m_pButtonCredits->SetDrawable(buttonCreditsDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonCredits);

    // Font Credits -------------------------------------------

    m_pTextCredits = twActiveUIWorld->CreateUIEntity();
    m_pTextCredits->m_Transform.SetAnchorPoint(0.35f, -0.8f);
    m_pTextCredits->m_Transform.SetPositionOffset(10.0f, -25.0f, 0.8f);

    auto creditsText = twFontManager->CreateText();
    creditsText->Set(m_pFontButton, "Credits", 1.0f);

    auto creditsTextDrawable = twRenderer->CreateFontDrawable();
    creditsTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    creditsTextDrawable->m_pText = creditsText;
    creditsTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pTextCredits->SetDrawable(creditsTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextCredits);
}

void CMainMenu::Update(const SUIInput& a_rInput)
{
    if (m_GoingIntoGame)
    {
        float half = CPostEffects::GameStartTime / 2.0f;
        m_CurrentTime += twTime->GetDeltaTime();

        float value = m_CurrentTime / half;
        ((triebWerk::CUIDrawable*)(m_pBackground->GetDrawable()))->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);

        if (m_CurrentTime >= half)
        {
            twSceneManager->SetActiveScene("Game");
            m_GoingIntoGame = false;
            m_CurrentTime = 0.0f;
        }

        return;
    }

    else if (m_LerpToExtras) LerpToExtras();
    else if (m_LerpFromExtras) LerpFromExtras();

    if (CGameInfo::Instance().m_Menu == EMenus::Main)
        CheckInput(a_rInput);

    UpdateGraphics();
}

void CMainMenu::End()
{

}

void CMainMenu::Resume()
{
    float value = 0.0f;
    ((triebWerk::CUIDrawable*)(m_pBackground->GetDrawable()))->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
}

void CMainMenu::CheckInput(const SUIInput& a_rInput)
{
    m_UpdateGraphics = true;

    a_rInput.m_ButtonHold ? m_HoldValue = 1 : m_HoldValue = 0;



    // Main buttons
    if (m_IsOnMainButtons)
    {
        if (a_rInput.m_Right)
        {
            m_SelectedButton++;
            if (m_SelectedButton == ButtonCount)
                m_SelectedButton = 0;

            m_UpdateGraphics = true;
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
        }
        else if (a_rInput.m_Left)
        {
            m_SelectedButton--;
            if (m_SelectedButton < 0)
                m_SelectedButton = ButtonCount - 1;

            m_UpdateGraphics = true;
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
        }

        if (a_rInput.m_Select)
        {
            switch (m_SelectedButton)
            {
            case 0:
                CGameInfo::Instance().m_EffectGoingIntoGame = true;
                m_GoingIntoGame = true;
				twAudio->PlaySFX(twResourceManager->GetSound("SFX_StartGame"));
				twAudio->FadeOutBGM(1, false);
                break;
            case 1:
                CGameInfo::Instance().m_Menu = EMenus::Highscore;
                CGameInfo::Instance().m_ChangeMenu = true;
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonConfirm"));
                break;
            case 2:
                CGameInfo::Instance().m_Menu = EMenus::Options;
                CGameInfo::Instance().m_ChangeMenu = true;
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonConfirm"));
                break;
            case 3:
                OpenExtras();
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonConfirm"));
                break;
            case 4:
                twEngine.Stop();
                break;
            }
        }

        else if (a_rInput.m_Up && m_SelectedButton == 3)
        {
            OpenExtras();
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
        }
    }

    // extra buttons
    else if (m_IsOnExtrasButtons)
    {
        if (a_rInput.m_Select)
        {
            switch (m_SelectedExtrasButton)
            {
            case 0:
                CGameInfo::Instance().m_Menu = EMenus::Manual;
                CGameInfo::Instance().m_ChangeMenu = true;
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonConfirm"));
                CloseExtras();
                break;
            case 1:
                CGameInfo::Instance().m_Menu = EMenus::Credits;
                CGameInfo::Instance().m_ChangeMenu = true;
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonConfirm"));
                CloseExtras();
                break;
            }
        }
        else if (a_rInput.m_Back)
        {
            CloseExtras();
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonBack"));
        }

        if (a_rInput.m_Up)
        {
            if (m_SelectedExtrasButton != 1)
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));

            m_SelectedExtrasButton = 1;
        }
        else if (a_rInput.m_Down)
        {
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));

            m_SelectedExtrasButton--;
            if (m_SelectedExtrasButton < 0)
                CloseExtras();
        }
    }
}

void CMainMenu::UpdateGraphics()
{
    if (!m_UpdateGraphics)
        return;

    // Main buttons
    size_t index[5] = { 0,0,0,0,0 };
    if (m_IsOnMainButtons)
    {
        index[m_SelectedButton]++;
        index[m_SelectedButton] += m_HoldValue;
    }

    ((triebWerk::CUIDrawable*)m_pButtonStart->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[0]]);
    ((triebWerk::CUIDrawable*)m_pButtonHighscore->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[1]]);
    ((triebWerk::CUIDrawable*)m_pButtonOptions->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[2]]);
    ((triebWerk::CUIDrawable*)m_pButtonExtras->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[3]]);
    ((triebWerk::CUIDrawable*)m_pButtonQuit->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[4]]);

    // Extra buttons
    size_t extraIndex[2] = { 0,0 };
    if (m_IsOnExtrasButtons)
    {
        index[m_SelectedExtrasButton]++;
        index[m_SelectedExtrasButton] += m_HoldValue;
    }

    ((triebWerk::CUIDrawable*)m_pButtonManual->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureRegularButton[index[0]]);
    ((triebWerk::CUIDrawable*)m_pButtonCredits->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureRegularButton[index[1]]);
}

void CMainMenu::OpenExtras()
{
    m_LerpToExtras = true;
    m_LerpFromExtras = false;

    m_CurrentLerpTime = 0.0f;
    m_SelectedExtrasButton = 0;

    m_IsOnMainButtons = false;
    m_IsOnExtrasButtons = true;
}

void CMainMenu::CloseExtras()
{
    m_LerpFromExtras = true;
    m_LerpToExtras = false;

    m_CurrentLerpTime = 0.0f;

    m_IsOnMainButtons = true;
    m_IsOnExtrasButtons = false;
}

void CMainMenu::LerpToExtras()
{
    const float StartPos = -0.8F;
    const float ManualEndPos = -0.53f;
    const float CreditsEndPos = -0.29f;

    m_CurrentLerpTime += twTime->GetDeltaTime();

    if (m_CurrentLerpTime >= LerpTime)
    {
        m_CurrentLerpTime = LerpTime;
        m_LerpToExtras = false;
    }

    float manualPos = StartPos + ((m_CurrentLerpTime / LerpTime) * (StartPos - ManualEndPos)) * -1;
    float creditsPos = StartPos + ((m_CurrentLerpTime / LerpTime) * (StartPos - CreditsEndPos)) * -1;

    m_pButtonManual->m_Transform.SetAnchorPoint(0.35f, manualPos);
    m_pTextManual->m_Transform.SetAnchorPoint(0.35f, manualPos);
    m_pButtonCredits->m_Transform.SetAnchorPoint(0.35f, creditsPos);
    m_pTextCredits->m_Transform.SetAnchorPoint(0.35f, creditsPos);
}

void CMainMenu::LerpFromExtras()
{
    const float ManualStartPos = -0.53f;
    const float CreditsStartPos = -0.29f;
    const float EndPos = -0.8F;

    m_CurrentLerpTime += twTime->GetDeltaTime();

    if (m_CurrentLerpTime >= LerpTime)
    {
        m_CurrentLerpTime = LerpTime;
        m_LerpFromExtras = false;
    }

    float manualPos = ManualStartPos + ((m_CurrentLerpTime / LerpTime) * (EndPos - ManualStartPos));
    float creditsPos = CreditsStartPos + ((m_CurrentLerpTime / LerpTime) * (EndPos - CreditsStartPos));

    m_pButtonManual->m_Transform.SetAnchorPoint(0.35f, manualPos);
    m_pTextManual->m_Transform.SetAnchorPoint(0.35f, manualPos);
    m_pButtonCredits->m_Transform.SetAnchorPoint(0.35f, creditsPos);
    m_pTextCredits->m_Transform.SetAnchorPoint(0.35f, creditsPos);
}
