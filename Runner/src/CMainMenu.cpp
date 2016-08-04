#include <CMainMenu.h>

#include <CGameInfo.h>
#include <CPostEffects.h>

CMainMenu::CMainMenu()
    : m_SelectedButton(0)
    , m_HoldValue(0)
    , m_GoingIntoGame(false)
    , m_CurrentTime(0.0f)
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
    m_pTextStart->m_Transform.SetPositionOffset(10.0f, -15.0f, 0.0f);

    auto startText = twFontManager->CreateText();
    startText->Set(m_pFontButton, "Start", 1.0f);

    auto startTextDrawable = twRenderer->CreateFontDrawable();
    startTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    startTextDrawable->m_pText = startText;
    startTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

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
    m_pTextHighscore->m_Transform.SetPositionOffset(10.0f, -15.0f, 0.0f);

    auto highscoreText = twFontManager->CreateText();
    highscoreText->Set(m_pFontButton, "Highscore", 1.0f);

    auto highscoreTextDrawable = twRenderer->CreateFontDrawable();
    highscoreTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    highscoreTextDrawable->m_pText = highscoreText;
    highscoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

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
    m_pTextOptions->m_Transform.SetPositionOffset(10.0f, -15.0f, 0.0f);

    auto optionsText = twFontManager->CreateText();
    optionsText->Set(m_pFontButton, "Options", 1.0f);

    auto optionsTextDrawable = twRenderer->CreateFontDrawable();
    optionsTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    optionsTextDrawable->m_pText = optionsText;
    optionsTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

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
    m_pTextExtras->m_Transform.SetPositionOffset(10.0f, -15.0f, 0.0f);

    auto extrasText = twFontManager->CreateText();
    extrasText->Set(m_pFontButton, "Extras", 1.0f);

    auto extrasTextDrawable = twRenderer->CreateFontDrawable();
    extrasTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    extrasTextDrawable->m_pText = extrasText;
    extrasTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

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
    m_pTextQuit->m_Transform.SetPositionOffset(10.0f, -15.0f, 0.0f);

    auto quitText = twFontManager->CreateText();
    quitText->Set(m_pFontButton, "Quit", 1.0f);

    auto quitTextDrawable = twRenderer->CreateFontDrawable();
    quitTextDrawable->m_Material.SetMaterial(m_pMaterialStandardFont);
    quitTextDrawable->m_pText = quitText;
    quitTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pTextQuit->SetDrawable(quitTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pTextQuit);

	// Audio

	m_pBackgroundMusic = twResourceManager->GetSound("A_BGM_nightland");

	twAudio->PlayBGM(m_pBackgroundMusic, true, true);
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

    bool updateGraphics = true;

    a_rInput.m_ButtonHold ? m_HoldValue = 1 : m_HoldValue = 0;

    if (a_rInput.m_Right)
    {
        m_SelectedButton++;
        if (m_SelectedButton == ButtonCount)
            m_SelectedButton = 0;

        updateGraphics = true;
    }
    else if (a_rInput.m_Left)
    {
        m_SelectedButton--;
        if (m_SelectedButton < 0)
            m_SelectedButton = ButtonCount - 1;

        updateGraphics = true;
    }

    if (a_rInput.m_Select)
    {
        switch (m_SelectedButton)
        {
        case 0:
            CGameInfo::Instance().m_EffectGoingIntoGame = true;
            m_GoingIntoGame = true;
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            twEngine.Stop();
            break;
        }
    }

    if (updateGraphics) UpdateGraphics();
}

void CMainMenu::End()
{

}

void CMainMenu::Resume()
{
    float value = 0.0f;
    ((triebWerk::CUIDrawable*)(m_pBackground->GetDrawable()))->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);

	twAudio->PlayBGM(m_pBackgroundMusic, true, true);
}

void CMainMenu::UpdateGraphics()
{
    (m_SelectedButton == 0) ?
        ((triebWerk::CUIDrawable*)m_pButtonStart->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1 + m_HoldValue]) :
        ((triebWerk::CUIDrawable*)m_pButtonStart->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    (m_SelectedButton == 1) ?
        ((triebWerk::CUIDrawable*)m_pButtonHighscore->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1 + m_HoldValue]) :
        ((triebWerk::CUIDrawable*)m_pButtonHighscore->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    (m_SelectedButton == 2) ?
        ((triebWerk::CUIDrawable*)m_pButtonOptions->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1 + m_HoldValue]) :
        ((triebWerk::CUIDrawable*)m_pButtonOptions->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    (m_SelectedButton == 3) ?
        ((triebWerk::CUIDrawable*)m_pButtonExtras->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1 + m_HoldValue]) :
        ((triebWerk::CUIDrawable*)m_pButtonExtras->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    (m_SelectedButton == 4) ?
        ((triebWerk::CUIDrawable*)m_pButtonQuit->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1 + m_HoldValue]) :
        ((triebWerk::CUIDrawable*)m_pButtonQuit->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);
}
