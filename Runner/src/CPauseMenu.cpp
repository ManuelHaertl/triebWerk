#include <CPauseMenu.h>

#include <CGameInfo.h>

CPauseMenu::CPauseMenu()
    : m_IsPaused(false)
    , m_IsOnButtons(true)
    , m_ButtonIndex(1)
    , m_FieldIndex(0)
    , m_HoldValue(0)
{
}

CPauseMenu::~CPauseMenu()
{
}

void CPauseMenu::Start()
{
    m_pTextureUnderlinedButton[0] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_normal");
    m_pTextureUnderlinedButton[1] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_hover");
    m_pTextureUnderlinedButton[2] = twResourceManager->GetTexture2D("T_ui_regularbutton_underlined_pressed");

    m_pTextureArrowLeft[0] = twResourceManager->GetTexture2D("T_ui_arrow_left_inactive");
    m_pTextureArrowLeft[1] = twResourceManager->GetTexture2D("T_ui_arrow_left");
    m_pTextureArrowRight[0] = twResourceManager->GetTexture2D("T_ui_arrow_right_inactive");
    m_pTextureArrowRight[1] = twResourceManager->GetTexture2D("T_ui_arrow_right");

    auto font = twFontManager->GetFont(twResourceManager->GetFontFace("AGENCYB"), 30);

    // Background --------------------------------------------

    m_pBackground = twActiveUIWorld->CreateUIEntity();
    m_pBackground->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pBackground->m_Transform.SetPositionOffset(0.0f, 0.0f, 1.0f);
    m_pBackground->m_Transform.SetScale(100.0, 100.0, 0.0f);

    auto backgroundDrawable = twRenderer->CreateUIDrawable();
    backgroundDrawable->SetActive(false);
    backgroundDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    backgroundDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_background"));

    m_pBackground->SetDrawable(backgroundDrawable);

    twActiveUIWorld->AddUIEntity(m_pBackground);

    // Field BG --------------------------------------------

    m_pFieldBG = twActiveUIWorld->CreateUIEntity();
    m_pFieldBG->m_Transform.SetAnchorPoint(0.0f, 0.1f);

    auto fieldBGDrawable = twRenderer->CreateUIDrawable();
    fieldBGDrawable->SetActive(false);
    fieldBGDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    fieldBGDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_bg"));

    m_pFieldBG->SetDrawable(fieldBGDrawable);

    twActiveUIWorld->AddUIEntity(m_pFieldBG);

    // Button Main Menu --------------------------------------------

    m_pButtonMainMenu = twActiveUIWorld->CreateUIEntity();
    m_pButtonMainMenu->m_Transform.SetAnchorPoint(-0.474f, -0.6f);
    m_pButtonMainMenu->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonMainMenuDrawable = twRenderer->CreateUIDrawable();
    buttonMainMenuDrawable->SetActive(false);
    buttonMainMenuDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    buttonMainMenuDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonMainMenu->SetDrawable(buttonMainMenuDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonMainMenu);

    // Font Start ------------------------------------------- 

    m_pFontMainMenu = twActiveUIWorld->CreateUIEntity();
    m_pFontMainMenu->m_Transform.SetAnchorPoint(-0.474f, -0.6f);
    m_pFontMainMenu->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto startText = twFontManager->CreateText();
    startText->Set(font, "Main Menu", 1.0f);

    auto startTextDrawable = twRenderer->CreateFontDrawable();
    startTextDrawable->SetActive(false);
    startTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    startTextDrawable->m_pText = startText;
    startTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pFontMainMenu->SetDrawable(startTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontMainMenu);

    // Button Resume --------------------------------------------

    m_pButtonResume = twActiveUIWorld->CreateUIEntity();
    m_pButtonResume->m_Transform.SetAnchorPoint(0.0f, -0.6f);
    m_pButtonResume->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonResumeDrawable = twRenderer->CreateUIDrawable();
    buttonResumeDrawable->SetActive(false);
    buttonResumeDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    buttonResumeDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[1]);

    m_pButtonResume->SetDrawable(buttonResumeDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonResume);

    // Font Resume ------------------------------------------- 

    m_pFontResume = twActiveUIWorld->CreateUIEntity();
    m_pFontResume->m_Transform.SetAnchorPoint(0.0f, -0.6f);
    m_pFontResume->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto resumeText = twFontManager->CreateText();
    resumeText->Set(font, "Resume", 1.0f);

    auto resumeTextDrawable = twRenderer->CreateFontDrawable();
    resumeTextDrawable->SetActive(false);
    resumeTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    resumeTextDrawable->m_pText = resumeText;
    resumeTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pFontResume->SetDrawable(resumeTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontResume);

    // Button Options --------------------------------------------

    m_pButtonOptions = twActiveUIWorld->CreateUIEntity();
    m_pButtonOptions->m_Transform.SetAnchorPoint(0.474f, -0.6f);
    m_pButtonOptions->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.5f);

    auto buttonOptionsDrawable = twRenderer->CreateUIDrawable();
    buttonOptionsDrawable->SetActive(false);
    buttonOptionsDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    buttonOptionsDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[0]);

    m_pButtonOptions->SetDrawable(buttonOptionsDrawable);

    twActiveUIWorld->AddUIEntity(m_pButtonOptions);

    // Font Options ------------------------------------------- 

    m_pFontOptions = twActiveUIWorld->CreateUIEntity();
    m_pFontOptions->m_Transform.SetAnchorPoint(0.474f, -0.6f);
    m_pFontOptions->m_Transform.SetPositionOffset(10.0f, -11.0f, 0.0f);

    auto optionsText = twFontManager->CreateText();
    optionsText->Set(font, "Options", 1.0f);

    auto optionsTextDrawable = twRenderer->CreateFontDrawable();
    optionsTextDrawable->SetActive(false);
    optionsTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    optionsTextDrawable->m_pText = optionsText;
    optionsTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pFontOptions->SetDrawable(optionsTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontOptions);

    // Arrow Left --------------------------------------------

    m_pArrowLeft = twActiveUIWorld->CreateUIEntity();
    m_pArrowLeft->m_Transform.SetAnchorPoint(-0.57f, 0.1f);
    m_pArrowLeft->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto arrowLeftDrawable = twRenderer->CreateUIDrawable();
    arrowLeftDrawable->SetActive(false);
    arrowLeftDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    arrowLeftDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureArrowLeft[0]);

    m_pArrowLeft->SetDrawable(arrowLeftDrawable);

    twActiveUIWorld->AddUIEntity(m_pArrowLeft);

    // Arrow Right --------------------------------------------

    m_pArrowRight = twActiveUIWorld->CreateUIEntity();
    m_pArrowRight->m_Transform.SetAnchorPoint(0.57f, 0.1f);
    m_pArrowRight->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto arrowRightDrawable = twRenderer->CreateUIDrawable();
    arrowRightDrawable->SetActive(false);
    arrowRightDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    arrowRightDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTextureArrowRight[1]);

    m_pArrowRight->SetDrawable(arrowRightDrawable);

    twActiveUIWorld->AddUIEntity(m_pArrowRight);

    // Objectives --------------------------------------------

    m_pObjective = twActiveUIWorld->CreateUIEntity();
    m_pObjective->m_Transform.SetAnchorPoint(0.0f, 0.2f);
    m_pObjective->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto objectiveDrawable = twRenderer->CreateUIDrawable();
    objectiveDrawable->SetActive(false);
    objectiveDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    objectiveDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_checkpoint"));

    m_pObjective->SetDrawable(objectiveDrawable);

    twActiveUIWorld->AddUIEntity(m_pObjective);

    // Font Objectives 1 ------------------------------------------- 

    m_pFontObjective1 = twActiveUIWorld->CreateUIEntity();
    m_pFontObjective1->m_Transform.SetAnchorPoint(0.0f, -0.23f);
    m_pFontObjective1->m_Transform.SetPositionOffset(10.0f, -11.0f, -0.1f);

    auto objective1Text = twFontManager->CreateText();
    objective1Text->Set(font, "Collect Checkpoint to save your score", 1.0f);

    auto objective1TextDrawable = twRenderer->CreateFontDrawable();
    objective1TextDrawable->SetActive(false);
    objective1TextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    objective1TextDrawable->m_pText = objective1Text;
    objective1TextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pFontObjective1->SetDrawable(objective1TextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontObjective1);

    // Font Objectives 2 ------------------------------------------- 

    m_pFontObjective2 = twActiveUIWorld->CreateUIEntity();
    m_pFontObjective2->m_Transform.SetAnchorPoint(0.0f, -0.32f);
    m_pFontObjective2->m_Transform.SetPositionOffset(10.0f, -11.0f, -0.1f);

    auto objective2Text = twFontManager->CreateText();
    objective2Text->Set(font, "Skip Checkpoint to gain a multiplier", 1.0f);

    auto objective2TextDrawable = twRenderer->CreateFontDrawable();
    objective2TextDrawable->SetActive(false);
    objective2TextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    objective2TextDrawable->m_pText = objective2Text;
    objective2TextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pFontObjective2->SetDrawable(objective2TextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontObjective2);

    // Controls --------------------------------------------

    m_pControls = twActiveUIWorld->CreateUIEntity();
    m_pControls->m_Transform.SetAnchorPoint(0.0f, 0.1f);
    m_pControls->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto controlsDrawable = twRenderer->CreateUIDrawable();
    controlsDrawable->SetActive(false);
    controlsDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    controlsDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_controller"));

    m_pControls->SetDrawable(controlsDrawable);

    twActiveUIWorld->AddUIEntity(m_pControls);
}

void CPauseMenu::Update(const SUIInput& a_rInput)
{
    bool changeGraphics = false;

    if (a_rInput.m_Pause)
        CGameInfo::Instance().m_IsGamePaused = !CGameInfo::Instance().m_IsGamePaused;

    if (m_IsPaused != CGameInfo::Instance().m_IsGamePaused)
    {
		if (CGameInfo::Instance().m_IsGamePaused)
			twAudio->PauseBGM();
		else if (!CGameInfo::Instance().m_IsGamePaused)
			twAudio->ContinueBGM();

        m_IsPaused = CGameInfo::Instance().m_IsGamePaused;
        m_IsOnButtons = true;
        m_FieldIndex = 0;
        m_ButtonIndex = 1;
        changeGraphics = true;
    }

    if (CGameInfo::Instance().m_IsGamePaused)
    {
        if (a_rInput.m_Up)
        {
            m_IsOnButtons = false;
            changeGraphics = true;
        }
        else if (a_rInput.m_Down)
        {
            m_IsOnButtons = true;
            changeGraphics = true;
        }
        a_rInput.m_ButtonHold ? m_HoldValue = 1 : m_HoldValue = 0;

        // If the field is selected
        if (!m_IsOnButtons)
        {
            if (a_rInput.m_Left)
            {
                m_FieldIndex--;
                if (m_FieldIndex < 0)
                    m_FieldIndex = 0;

                changeGraphics = true;
            }
            else if (a_rInput.m_Right)
            {
                m_FieldIndex++;
                if (m_FieldIndex == MaxFieldIndex)
                    m_FieldIndex = MaxFieldIndex - 1;

                changeGraphics = true;
            }
        }
        // if the buttons are selected
        else
        {
            if (a_rInput.m_Left)
            {
                m_ButtonIndex--;
                if (m_ButtonIndex < 0)
                    m_ButtonIndex = MaxButtonIndex - 1;

                changeGraphics = true;
            }
            else if (a_rInput.m_Right)
            {
                m_ButtonIndex++;
                if (m_ButtonIndex == MaxButtonIndex)
                    m_ButtonIndex = 0;

                changeGraphics = true;
            }

            if (a_rInput.m_Select)
            {
                switch (m_ButtonIndex)
                {
                case 0:
                    twSceneManager->SetActiveScene("Menu");
                    break;
                case 1:
                    CGameInfo::Instance().m_IsGamePaused = false;
                    break;
                case 2:
                    break;
                }
            }
        }
    }

    if (changeGraphics)
        UpdateGraphics();
}

void CPauseMenu::End()
{
}

void CPauseMenu::UpdateGraphics()
{
    // Hide / show all elemenets depenging on if the game is paused
    bool active = CGameInfo::Instance().m_IsGamePaused;

    m_pBackground->GetDrawable()->SetActive(active);
    m_pFieldBG->GetDrawable()->SetActive(active);
    m_pButtonMainMenu->GetDrawable()->SetActive(active);
    m_pButtonOptions->GetDrawable()->SetActive(active);
    m_pButtonResume->GetDrawable()->SetActive(active);
    m_pFontMainMenu->GetDrawable()->SetActive(active);
    m_pFontResume->GetDrawable()->SetActive(active);
    m_pFontOptions->GetDrawable()->SetActive(active);
    m_pArrowLeft->GetDrawable()->SetActive(active);
    m_pArrowRight->GetDrawable()->SetActive(active);
    m_pObjective->GetDrawable()->SetActive(active);
    m_pControls->GetDrawable()->SetActive(active);
    m_pFontObjective1->GetDrawable()->SetActive(active);
    m_pFontObjective2->GetDrawable()->SetActive(active);

    // the 3 buttons' states
    size_t index[3] = { 0,0,0 };

    if (m_IsOnButtons)
    {
        index[m_ButtonIndex]++;
        index[m_ButtonIndex] += m_HoldValue;
    }

    ((triebWerk::CUIDrawable*)m_pButtonMainMenu->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[0]]);
    ((triebWerk::CUIDrawable*)m_pButtonResume->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[1]]);
    ((triebWerk::CUIDrawable*)m_pButtonOptions->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureUnderlinedButton[index[2]]);

    // Arrow left & right
    (m_FieldIndex == 0) ?
        ((triebWerk::CUIDrawable*)m_pArrowLeft->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureArrowLeft[0]) :
        ((triebWerk::CUIDrawable*)m_pArrowLeft->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureArrowLeft[1]);

    (m_FieldIndex == 1) ?
        ((triebWerk::CUIDrawable*)m_pArrowRight->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureArrowRight[0]) :
        ((triebWerk::CUIDrawable*)m_pArrowRight->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTextureArrowRight[1]);

    // Current selected field
    if (active)
    {
        if (m_FieldIndex == 0)
        {
            m_pObjective->GetDrawable()->SetActive(true);
            m_pFontObjective1->GetDrawable()->SetActive(true);
            m_pFontObjective2->GetDrawable()->SetActive(true);
            m_pControls->GetDrawable()->SetActive(false);
        }
        else
        {
            m_pObjective->GetDrawable()->SetActive(false);
            m_pFontObjective1->GetDrawable()->SetActive(false);
            m_pFontObjective2->GetDrawable()->SetActive(false);
            m_pControls->GetDrawable()->SetActive(true);
        }
    }
}
