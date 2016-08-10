#include <COptionsMenu.h>

#include <CGameInfo.h>
#include <CFileWriter.h>
#include <ShlObj.h>

COptionsMenu::COptionsMenu()
    : m_UpdateGraphics(true)
    , m_SelectedIndex(0)
    , m_PressedValue(0)
    , m_CurrentResolution(0)
    , m_CurrentFullscreen(0)
    , m_CurrentVSync(1)
    , m_CurrentMasterVolume(1.0f)
    , m_CurrentBGMVolume(1.0f)
    , m_CurrentSFXVolume(1.0f)
{
}

COptionsMenu::~COptionsMenu()
{
}

void COptionsMenu::Start()
{
    auto font = twFontManager->GetFont(twResourceManager->GetFontFace("AGENCYB"), 30);

    m_pTexturesCheckbox[0] = twResourceManager->GetTexture2D("T_checkbox_normal");
    m_pTexturesCheckbox[1] = twResourceManager->GetTexture2D("T_checkbox_hover");
    m_pTexturesCheckbox[2] = twResourceManager->GetTexture2D("T_checkbox_pressed");

    m_pTexturesArrowsLeft[0] = twResourceManager->GetTexture2D("T_ui_arrow_left_inactive");
    m_pTexturesArrowsLeft[1] = twResourceManager->GetTexture2D("T_ui_arrow_left");
    m_pTexturesArrowsRight[0] = twResourceManager->GetTexture2D("T_ui_arrow_right_inactive");
    m_pTexturesArrowsRight[1] = twResourceManager->GetTexture2D("T_ui_arrow_right");

    // Field BG -------------------------------------------------

    m_pFieldBG = twActiveUIWorld->CreateUIEntity();
    m_pFieldBG->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pFieldBG->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.0f);

    auto fieldBGDrawable = twRenderer->CreateUIDrawable();
    fieldBGDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    fieldBGDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_bg"));

    m_pFieldBG->SetDrawable(fieldBGDrawable);

    twActiveUIWorld->AddUIEntity(m_pFieldBG);

    // Resolution Box -------------------------------------------------

    m_pResolutionBox = twActiveUIWorld->CreateUIEntity();
    m_pResolutionBox->m_Transform.SetAnchorPoint(0.15f, 0.35f);
    m_pResolutionBox->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto resolutionBoxDrawable = twRenderer->CreateUIDrawable();
    resolutionBoxDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    resolutionBoxDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_resolution_hover"));

    m_pResolutionBox->SetDrawable(resolutionBoxDrawable);

    twActiveUIWorld->AddUIEntity(m_pResolutionBox);

    // Font Resolution -------------------------------------------

    m_pFontResolution = twActiveUIWorld->CreateUIEntity();
    m_pFontResolution->m_Transform.SetAnchorPoint(-0.2f, 0.35f);
    m_pFontResolution->m_Transform.SetPositionOffset(0.0f, -23.0f, -0.1f);

    auto resolutionText = twFontManager->CreateText();
    resolutionText->Set(font, "Resolution", 1.0f);
    resolutionText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto resolutionTextDrawable = twRenderer->CreateFontDrawable();
    resolutionTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    resolutionTextDrawable->m_pText = resolutionText;
    resolutionTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontResolution->SetDrawable(resolutionTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontResolution);

    // Font Current Resolution -------------------------------------------

    m_pFontCurrentResolution = twActiveUIWorld->CreateUIEntity();
    m_pFontCurrentResolution->m_Transform.SetAnchorPoint(0.15f, 0.35f);
    m_pFontCurrentResolution->m_Transform.SetPositionOffset(0.0f, -24.0f, -0.1f);

    auto currentResolutionText = twFontManager->CreateText();
    currentResolutionText->Set(font, "1600x1200", 1.0f);

    auto currentResolutionTextDrawable = twRenderer->CreateFontDrawable();
    currentResolutionTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    currentResolutionTextDrawable->m_pText = currentResolutionText;
    currentResolutionTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontCurrentResolution->SetDrawable(currentResolutionTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontCurrentResolution);

    // Arrow Left -------------------------------------------------

    m_pArrowLeft = twActiveUIWorld->CreateUIEntity();
    m_pArrowLeft->m_Transform.SetAnchorPoint(-0.13f, 0.35f);
    m_pArrowLeft->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto arrowLeftDrawable = twRenderer->CreateUIDrawable();
    arrowLeftDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    arrowLeftDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesArrowsLeft[0]);

    m_pArrowLeft->SetDrawable(arrowLeftDrawable);

    twActiveUIWorld->AddUIEntity(m_pArrowLeft);

    // Arrow Right -------------------------------------------------

    m_pArrowRight = twActiveUIWorld->CreateUIEntity();
    m_pArrowRight->m_Transform.SetAnchorPoint(0.43f, 0.35f);
    m_pArrowRight->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto arrowRightDrawable = twRenderer->CreateUIDrawable();
    arrowRightDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    arrowRightDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesArrowsRight[0]);

    m_pArrowRight->SetDrawable(arrowRightDrawable);

    twActiveUIWorld->AddUIEntity(m_pArrowRight);

    // Fullscreen -------------------------------------------------

    m_pFullscreen = twActiveUIWorld->CreateUIEntity();
    m_pFullscreen->m_Transform.SetAnchorPoint(-0.135f, 0.15f);
    m_pFullscreen->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto fullscreenDrawable = twRenderer->CreateUIDrawable();
    fullscreenDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    fullscreenDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesCheckbox[0]);

    m_pFullscreen->SetDrawable(fullscreenDrawable);

    twActiveUIWorld->AddUIEntity(m_pFullscreen);

    // Fullscreen Cross -------------------------------------------------

    m_pFullscreenCross = twActiveUIWorld->CreateUIEntity();
    m_pFullscreenCross->m_Transform.SetAnchorPoint(-0.135f, 0.15f);
    m_pFullscreenCross->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto fullscreenCrossDrawable = twRenderer->CreateUIDrawable();
    fullscreenCrossDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    fullscreenCrossDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_checkbox_cross"));

    m_pFullscreenCross->SetDrawable(fullscreenCrossDrawable);

    twActiveUIWorld->AddUIEntity(m_pFullscreenCross);

    // Font Fullscreen -------------------------------------------

    m_pFontFullscreen = twActiveUIWorld->CreateUIEntity();
    m_pFontFullscreen->m_Transform.SetAnchorPoint(-0.2f, 0.15f);
    m_pFontFullscreen->m_Transform.SetPositionOffset(0.0f, -23.0f, -0.1f);

    auto fullscreenText = twFontManager->CreateText();
    fullscreenText->Set(font, "Fullscreen", 1.0f);
    fullscreenText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto fullscreenTextDrawable = twRenderer->CreateFontDrawable();
    fullscreenTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    fullscreenTextDrawable->m_pText = fullscreenText;
    fullscreenTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontFullscreen->SetDrawable(fullscreenTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontFullscreen);

    // VSync -------------------------------------------------

    m_pVSync = twActiveUIWorld->CreateUIEntity();
    m_pVSync->m_Transform.SetAnchorPoint(0.15f, 0.15f);
    m_pVSync->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto vsyncDrawable = twRenderer->CreateUIDrawable();
    vsyncDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    vsyncDrawable->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesCheckbox[0]);

    m_pVSync->SetDrawable(vsyncDrawable);

    twActiveUIWorld->AddUIEntity(m_pVSync);

    // VSync Cross -------------------------------------------------

    m_pVSyncCross = twActiveUIWorld->CreateUIEntity();
    m_pVSyncCross->m_Transform.SetAnchorPoint(0.15f, 0.15f);
    m_pVSyncCross->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto vsyncCrossDrawable = twRenderer->CreateUIDrawable();
    vsyncCrossDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    vsyncCrossDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_checkbox_cross"));

    m_pVSyncCross->SetDrawable(vsyncCrossDrawable);

    twActiveUIWorld->AddUIEntity(m_pVSyncCross);

    // Font VSync -------------------------------------------

    m_pFontVSync = twActiveUIWorld->CreateUIEntity();
    m_pFontVSync->m_Transform.SetAnchorPoint(0.15f, 0.15f);
    m_pFontVSync->m_Transform.SetPositionOffset(-50.0f, -23.0f, -0.1f);

    auto vsyncText = twFontManager->CreateText();
    vsyncText->Set(font, "VSync", 1.0f);
    vsyncText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto vsyncTextDrawable = twRenderer->CreateFontDrawable();
    vsyncTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    vsyncTextDrawable->m_pText = vsyncText;
    vsyncTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontVSync->SetDrawable(vsyncTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontVSync);

    // Master Volume -------------------------------------------------

    m_pMasterVolume = twActiveUIWorld->CreateUIEntity();
    m_pMasterVolume->m_Transform.SetAnchorPoint(0.15f, -0.05f);
    m_pMasterVolume->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto masterVolumeDrawable = twRenderer->CreateUIDrawable();
    masterVolumeDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    masterVolumeDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_bar"));

    m_pMasterVolume->SetDrawable(masterVolumeDrawable);

    twActiveUIWorld->AddUIEntity(m_pMasterVolume);

    // Master Volume Bar -------------------------------------------------

    m_pMasterVolumeBar = twActiveUIWorld->CreateUIEntity();
    m_pMasterVolumeBar->m_Transform.SetAnchorPoint(0.15f, -0.05f);
    m_pMasterVolumeBar->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto masterVolumeBarDrawable = twRenderer->CreateUIDrawable();
    float value = 1.0f;
    masterVolumeBarDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("UIFill"));
    masterVolumeBarDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
    masterVolumeBarDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_fill"));

    m_pMasterVolumeBar->SetDrawable(masterVolumeBarDrawable);

    twActiveUIWorld->AddUIEntity(m_pMasterVolumeBar);

    // Master Volume Selected -------------------------------------------------

    m_pMasterVolumeSelected = twActiveUIWorld->CreateUIEntity();
    m_pMasterVolumeSelected->m_Transform.SetAnchorPoint(0.15f, -0.05f);
    m_pMasterVolumeSelected->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.01f);

    auto masterVolumeSelectedDrawable = twRenderer->CreateUIDrawable();
    masterVolumeSelectedDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    masterVolumeSelectedDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_hover"));

    m_pMasterVolumeSelected->SetDrawable(masterVolumeSelectedDrawable);

    twActiveUIWorld->AddUIEntity(m_pMasterVolumeSelected);

    // Font Master Volume -------------------------------------------

    m_pFontMasterVolume = twActiveUIWorld->CreateUIEntity();
    m_pFontMasterVolume->m_Transform.SetAnchorPoint(-0.2f, -0.05f);
    m_pFontMasterVolume->m_Transform.SetPositionOffset(0.0f, -23.0f, -0.1f);

    auto masterVolumeText = twFontManager->CreateText();
    masterVolumeText->Set(font, "Master Volume", 1.0f);
    masterVolumeText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto masterVolumeTextDrawable = twRenderer->CreateFontDrawable();
    masterVolumeTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    masterVolumeTextDrawable->m_pText = masterVolumeText;
    masterVolumeTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontMasterVolume->SetDrawable(masterVolumeTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontMasterVolume);

    // BGM Volume -------------------------------------------------

    m_pBGMVolume = twActiveUIWorld->CreateUIEntity();
    m_pBGMVolume->m_Transform.SetAnchorPoint(0.15f, -0.2f);
    m_pBGMVolume->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto bgmVolumeDrawable = twRenderer->CreateUIDrawable();
    bgmVolumeDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    bgmVolumeDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_bar"));

    m_pBGMVolume->SetDrawable(bgmVolumeDrawable);

    twActiveUIWorld->AddUIEntity(m_pBGMVolume);

    // BGM Volume Bar -------------------------------------------------

    m_pBGMVolumeBar = twActiveUIWorld->CreateUIEntity();
    m_pBGMVolumeBar->m_Transform.SetAnchorPoint(0.15f, -0.2f);
    m_pBGMVolumeBar->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto bgmVolumeBarDrawable = twRenderer->CreateUIDrawable();
    bgmVolumeBarDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("UIFill"));
    bgmVolumeBarDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
    bgmVolumeBarDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_fill"));

    m_pBGMVolumeBar->SetDrawable(bgmVolumeBarDrawable);

    twActiveUIWorld->AddUIEntity(m_pBGMVolumeBar);

    // BGM Volume Selected -------------------------------------------------

    m_pBGMVolumeSelected = twActiveUIWorld->CreateUIEntity();
    m_pBGMVolumeSelected->m_Transform.SetAnchorPoint(0.15f, -0.2f);
    m_pBGMVolumeSelected->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.01f);

    auto bgmVolumeSelectedDrawable = twRenderer->CreateUIDrawable();
    bgmVolumeSelectedDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    bgmVolumeSelectedDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_hover"));

    m_pBGMVolumeSelected->SetDrawable(bgmVolumeSelectedDrawable);

    twActiveUIWorld->AddUIEntity(m_pBGMVolumeSelected);

    // Font BGM Volume -------------------------------------------

    m_pFontBGMVolume = twActiveUIWorld->CreateUIEntity();
    m_pFontBGMVolume->m_Transform.SetAnchorPoint(-0.2f, -0.2f);
    m_pFontBGMVolume->m_Transform.SetPositionOffset(0.0f, -23.0f, -0.1f);

    auto bgmVolumeText = twFontManager->CreateText();
    bgmVolumeText->Set(font, "BGM Volume", 1.0f);
    bgmVolumeText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto bgmVolumeTextDrawable = twRenderer->CreateFontDrawable();
    bgmVolumeTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    bgmVolumeTextDrawable->m_pText = bgmVolumeText;
    bgmVolumeTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontBGMVolume->SetDrawable(bgmVolumeTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontBGMVolume);

    // SFX Volume -------------------------------------------------

    m_pSFXVolume = twActiveUIWorld->CreateUIEntity();
    m_pSFXVolume->m_Transform.SetAnchorPoint(0.15f, -0.35f);
    m_pSFXVolume->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.05f);

    auto sfxVolumeDrawable = twRenderer->CreateUIDrawable();
    sfxVolumeDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    sfxVolumeDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_bar"));

    m_pSFXVolume->SetDrawable(sfxVolumeDrawable);

    twActiveUIWorld->AddUIEntity(m_pSFXVolume);

    // SFX Volume Bar -------------------------------------------------

    m_pSFXVolumeBar = twActiveUIWorld->CreateUIEntity();
    m_pSFXVolumeBar->m_Transform.SetAnchorPoint(0.15f, -0.35f);
    m_pSFXVolumeBar->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto sfxVolumeBarDrawable = twRenderer->CreateUIDrawable();
    sfxVolumeBarDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("UIFill"));
    sfxVolumeBarDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
    sfxVolumeBarDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_fill"));

    m_pSFXVolumeBar->SetDrawable(sfxVolumeBarDrawable);

    twActiveUIWorld->AddUIEntity(m_pSFXVolumeBar);

    // SFX Volume Selected -------------------------------------------------

    m_pSFXVolumeSelected = twActiveUIWorld->CreateUIEntity();
    m_pSFXVolumeSelected->m_Transform.SetAnchorPoint(0.15f, -0.35f);
    m_pSFXVolumeSelected->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.01f);

    auto sfxVolumeSelectedDrawable = twRenderer->CreateUIDrawable();
    sfxVolumeSelectedDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    sfxVolumeSelectedDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_slider_hover"));

    m_pSFXVolumeSelected->SetDrawable(sfxVolumeSelectedDrawable);

    twActiveUIWorld->AddUIEntity(m_pSFXVolumeSelected);

    // Font SFX Volume -------------------------------------------

    m_pFontSFXVolume = twActiveUIWorld->CreateUIEntity();
    m_pFontSFXVolume->m_Transform.SetAnchorPoint(-0.2f, -0.35f);
    m_pFontSFXVolume->m_Transform.SetPositionOffset(0.0f, -23.0f, -0.1f);

    auto sfxVolumeText = twFontManager->CreateText();
    sfxVolumeText->Set(font, "SFX Volume", 1.0f);
    sfxVolumeText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto sfxVolumeTextDrawable = twRenderer->CreateFontDrawable();
    sfxVolumeTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    sfxVolumeTextDrawable->m_pText = sfxVolumeText;
    sfxVolumeTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pFontSFXVolume->SetDrawable(sfxVolumeTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pFontSFXVolume);

    GetOptions();
    UpdateGraphics();
}

void COptionsMenu::Update(const SUIInput& a_rInput)
{
    CheckInput(a_rInput);
    UpdateGraphics();
}

void COptionsMenu::End()
{
    SaveOptions();

    twActiveUIWorld->RemoveUIEntity(m_pFieldBG);
    twActiveUIWorld->RemoveUIEntity(m_pArrowLeft);
    twActiveUIWorld->RemoveUIEntity(m_pArrowRight);
    twActiveUIWorld->RemoveUIEntity(m_pResolutionBox);
    twActiveUIWorld->RemoveUIEntity(m_pFullscreen);
    twActiveUIWorld->RemoveUIEntity(m_pFullscreenCross);
    twActiveUIWorld->RemoveUIEntity(m_pVSync);
    twActiveUIWorld->RemoveUIEntity(m_pVSyncCross);
    twActiveUIWorld->RemoveUIEntity(m_pMasterVolume);
    twActiveUIWorld->RemoveUIEntity(m_pMasterVolumeBar);
    twActiveUIWorld->RemoveUIEntity(m_pMasterVolumeSelected);
    twActiveUIWorld->RemoveUIEntity(m_pBGMVolume);
    twActiveUIWorld->RemoveUIEntity(m_pBGMVolumeBar);
    twActiveUIWorld->RemoveUIEntity(m_pBGMVolumeSelected);
    twActiveUIWorld->RemoveUIEntity(m_pSFXVolume);
    twActiveUIWorld->RemoveUIEntity(m_pSFXVolumeBar);
    twActiveUIWorld->RemoveUIEntity(m_pSFXVolumeSelected);
    twActiveUIWorld->RemoveUIEntity(m_pFontResolution);
    twActiveUIWorld->RemoveUIEntity(m_pFontCurrentResolution);
    twActiveUIWorld->RemoveUIEntity(m_pFontFullscreen);
    twActiveUIWorld->RemoveUIEntity(m_pFontVSync);
    twActiveUIWorld->RemoveUIEntity(m_pFontMasterVolume);
    twActiveUIWorld->RemoveUIEntity(m_pFontBGMVolume);
    twActiveUIWorld->RemoveUIEntity(m_pFontSFXVolume);
}

void COptionsMenu::GetOptions()
{
    auto width = twWindow->GetScreenWidth();
    switch (width)
    {
    case 800:
        m_CurrentResolution = 0;
        break;
    case 1024:
        m_CurrentResolution = 1;
        break;
    case 1280:
        m_CurrentResolution = 2;
        break;
    case 1600:
        m_CurrentResolution = 3;
        break;
    case 1900:
        m_CurrentResolution = 4;
        break;
    case 1920:
        m_CurrentResolution = 5;
        break;
    default:
        m_CurrentResolution = 0;
        break;
    }
    m_CurrentFullscreen = twWindow->IsWindowFullscreen();
    m_CurrentVSync = twGraphic->IsVSynced();
    m_CurrentMasterVolume = twAudio->GetMasterVolume();
    m_CurrentBGMVolume = twAudio->GetBGMVolume();
    m_CurrentSFXVolume = twAudio->GetSFXVolume();
}

void COptionsMenu::SaveOptions()
{
    // Apply changes to engine

    bool sameSettings = twWindow->GetScreenWidth() == GetCurrentWidth() && twWindow->GetScreenHeight() == GetCurrentHeight() && twWindow->IsWindowFullscreen() == m_CurrentFullscreen;
    if (!sameSettings)
    {
        twWindow->ChangeWindowSettings(m_CurrentFullscreen, GetCurrentWidth(), GetCurrentHeight());
        std::cout << "graphics changed" << std::endl;
    }

    twGraphic->SetVSync(m_CurrentVSync);
    twAudio->SetMasterVolume(m_CurrentMasterVolume);
    twAudio->SetBGMVolume(m_CurrentBGMVolume);
    twAudio->SetSFXVolume(m_CurrentSFXVolume);

    // save in file
    CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
    std::string path = my_documents;
    path += "\\My Games\\AZ-Tec Racer\\config.twf";

    triebWerk::CFileWriter fileWriter;
    if (!fileWriter.CreateSaveFile(path.c_str()))
        return;

    fileWriter.SetParams("width", std::to_string(GetCurrentWidth()));
    fileWriter.SetParams("height", std::to_string(GetCurrentHeight()));
    fileWriter.SetParams("fullscreen", std::to_string(m_CurrentFullscreen));
    fileWriter.SetParams("vsync", std::to_string(m_CurrentVSync));
    fileWriter.SetParams("mastervolume", std::to_string(m_CurrentMasterVolume));
    fileWriter.SetParams("bgmvolume", std::to_string(m_CurrentBGMVolume));
    fileWriter.SetParams("sfxvolume", std::to_string(m_CurrentSFXVolume));
    fileWriter.SaveFile();
}

void COptionsMenu::CheckInput(const SUIInput& a_rInput)
{
    if (a_rInput.m_Down)
    {
        if (m_SelectedIndex == 1)
            m_SelectedIndex++;

        m_SelectedIndex++;

        if (m_SelectedIndex == MaxIndex)
            m_SelectedIndex = 0;

        m_UpdateGraphics = true;
        twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
    }

    if (a_rInput.m_Up)
    {
        if (m_SelectedIndex == 2 || m_SelectedIndex == 3)
            m_SelectedIndex--;

        m_SelectedIndex--;

        if (m_SelectedIndex < 0)
            m_SelectedIndex = MaxIndex - 1;

        m_UpdateGraphics = true;
        twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
    }

    if (a_rInput.m_Left)
    {
        switch (m_SelectedIndex)
        {
        case 0:
            m_CurrentResolution--;
            if (m_CurrentResolution < 0)
                m_CurrentResolution = 0;
            else
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
            break;
        case 2:
            m_SelectedIndex--;
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
            break;
        }

        m_UpdateGraphics = true;
    }

    if ((a_rInput.m_LeftUp || a_rInput.m_RightUp) && m_SelectedIndex == 5)
        twAudio->PlaySFX(twResourceManager->GetSound("SFX_SFXChange"));

    // volume lower
    if (a_rInput.m_LeftHold)
    {
        switch (m_SelectedIndex)
        {
        case 3:
            m_CurrentMasterVolume -= SoundMoveSpeed * twTime->GetDeltaTime();
            if (m_CurrentMasterVolume < 0.0f)
                m_CurrentMasterVolume = 0.0f;

            twAudio->SetMasterVolume(m_CurrentMasterVolume);
            break;
        case 4:
            m_CurrentBGMVolume -= SoundMoveSpeed * twTime->GetDeltaTime();
            if (m_CurrentBGMVolume < 0.0f)
                m_CurrentBGMVolume = 0.0f;

            twAudio->SetBGMVolume(m_CurrentBGMVolume);
            break;
        case 5:
            m_CurrentSFXVolume -= SoundMoveSpeed * twTime->GetDeltaTime();
            if (m_CurrentSFXVolume < 0.0f)
                m_CurrentSFXVolume = 0.0f;

            twAudio->SetSFXVolume(m_CurrentSFXVolume);
            break;
        }

        m_UpdateGraphics = true;
    }

    if (a_rInput.m_Right)
    {
        switch (m_SelectedIndex)
        {
        case 0:
            m_CurrentResolution++;
            if (m_CurrentResolution == MaxResolutions)
                m_CurrentResolution = MaxResolutions - 1;
            else
                twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
            break;
        case 1:
            m_SelectedIndex++;
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonSelect"));
            break;
        }

        m_UpdateGraphics = true;
    }

    // volume higher
    if (a_rInput.m_RightHold)
    {
        switch (m_SelectedIndex)
        {
        case 3:
            m_CurrentMasterVolume += SoundMoveSpeed * twTime->GetDeltaTime();
            if (m_CurrentMasterVolume > 1.0f)
                m_CurrentMasterVolume = 1.0f;

            twAudio->SetMasterVolume(m_CurrentMasterVolume);
            break;
        case 4:
            m_CurrentBGMVolume += SoundMoveSpeed * twTime->GetDeltaTime();
            if (m_CurrentBGMVolume > 1.0f)
                m_CurrentBGMVolume = 1.0f;

            twAudio->SetBGMVolume(m_CurrentBGMVolume);
            break;
        case 5:
            m_CurrentSFXVolume += SoundMoveSpeed * twTime->GetDeltaTime();
            if (m_CurrentSFXVolume > 1.0f)
                m_CurrentSFXVolume = 1.0f;

            twAudio->SetSFXVolume(m_CurrentSFXVolume);
            break;
        }

        m_UpdateGraphics = true;
    }

    // Select
    if (a_rInput.m_Select)
    {
        switch (m_SelectedIndex)
        {
        case 1:
            m_CurrentFullscreen = !m_CurrentFullscreen;
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonConfirm"));
            break;
        case 2:
            m_CurrentVSync = !m_CurrentVSync;
            twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonConfirm"));
            break;
        }
    }

    // Back
    if (a_rInput.m_Back)
    {
        CGameInfo::Instance().m_ChangeMenu = true;
        CGameInfo::Instance().m_Menu = EMenus::Main;
        SaveOptions();
        twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonBack"));
    }

    // Button hold value
    int value = 0;
    a_rInput.m_ButtonHold ? value = 1 : value = 0;
    if (value != m_PressedValue)
    {
        m_PressedValue = value;
        m_UpdateGraphics = true;
    }
}

void COptionsMenu::UpdateGraphics()
{
    if (!m_UpdateGraphics)
        return;

    m_UpdateGraphics = false;

    std::string resText = std::to_string(GetCurrentWidth()) + "x" + std::to_string(GetCurrentHeight());
    ((triebWerk::CFontDrawable*)m_pFontCurrentResolution->GetDrawable())->m_pText->SetText(resText);

    (m_CurrentResolution == 0) ?
        ((triebWerk::CUIDrawable*)m_pArrowLeft->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesArrowsLeft[0]) :
        ((triebWerk::CUIDrawable*)m_pArrowLeft->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesArrowsLeft[1]);
    (m_CurrentResolution == (MaxResolutions - 1)) ?
        ((triebWerk::CUIDrawable*)m_pArrowRight->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesArrowsRight[0]) :
        ((triebWerk::CUIDrawable*)m_pArrowRight->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesArrowsRight[1]);


    size_t fullscreenIndex = 0, vsyncIndex = 0;
    switch (m_SelectedIndex)
    {
    case 1:
        fullscreenIndex++;
        fullscreenIndex += m_PressedValue;
        break;
    case 2:
        vsyncIndex++;
        vsyncIndex += m_PressedValue;
        break;
    }

    ((triebWerk::CUIDrawable*)m_pFullscreen->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesCheckbox[fullscreenIndex]);
    ((triebWerk::CUIDrawable*)m_pVSync->GetDrawable())->m_Material.m_pPixelShader.SetTexture(0, m_pTexturesCheckbox[vsyncIndex]);

    m_pResolutionBox->GetDrawable()->SetActive(m_SelectedIndex == 0);
    m_pFullscreenCross->GetDrawable()->SetActive(m_CurrentFullscreen);
    m_pVSyncCross->GetDrawable()->SetActive(m_CurrentVSync);
    m_pMasterVolumeSelected->GetDrawable()->SetActive(m_SelectedIndex == 3);
    m_pBGMVolumeSelected->GetDrawable()->SetActive(m_SelectedIndex == 4);
    m_pSFXVolumeSelected->GetDrawable()->SetActive(m_SelectedIndex == 5);

    ((triebWerk::CUIDrawable*)m_pMasterVolumeBar->GetDrawable())->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_CurrentMasterVolume);
    ((triebWerk::CUIDrawable*)m_pBGMVolumeBar->GetDrawable())->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_CurrentBGMVolume);
    ((triebWerk::CUIDrawable*)m_pSFXVolumeBar->GetDrawable())->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_CurrentSFXVolume);
}

size_t COptionsMenu::GetCurrentWidth()
{
    switch (m_CurrentResolution)
    {
    case 0:
        return 800;
    case 1:
        return 1024;
    case 2:
        return 1280;
    case 3:
        return 1600;
    case 4:
        return 1900;
    case 5:
        return 1920;
    }

    return 800;
}

size_t COptionsMenu::GetCurrentHeight()
{
    switch (m_CurrentResolution)
    {
    case 0:
        return 450;
    case 1:
        return 576;
    case 2:
        return 720;
    case 3:
        return 900;
    case 4:
        return 1024;
    case 5:
        return 1080;
    }

    return 450;
}
