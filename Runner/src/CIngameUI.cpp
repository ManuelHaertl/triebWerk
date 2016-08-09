#include <CIngameUI.h>

#include <CPauseMenu.h>
#include <CGameEndMenu.h>
#include <CEngine.h>
#include <CGameInfo.h>
#include <sstream>
#include <iomanip>

CInGameUI::CInGameUI()
    : m_UIInput()
    , m_pPauseMenu(nullptr)
    , m_pGameEndMenu(nullptr)
    , m_pCurrentPoints(nullptr)
    , m_pTotalPoints(nullptr)
    , m_pBarLeft(nullptr)
    , m_pBarRight(nullptr)
{
}

CInGameUI::~CInGameUI()
{
}

void CInGameUI::Start()
{
    twActiveUIWorld->SetReferenceResolution(1920, 1080.0f, triebWerk::CUIWorld::EScreenMatchState::Height);
    twFontManager->LoadFont(twResourceManager->GetFontFace("AGENCYB"), 30);
    twFontManager->LoadFont(twResourceManager->GetFontFace("AGENCYB"), 50);

    m_pPauseMenu = new CPauseMenu();
    m_pPauseMenu->Start();

    m_pGameEndMenu = new CGameEndMenu();
    m_pGameEndMenu->Start();

    CreateIngameUI();
}

void CInGameUI::Update()
{
    CheckInput();

    UpdateIngameUI();
    m_pPauseMenu->Update(m_UIInput);
    m_pGameEndMenu->Update(m_UIInput);
}

void CInGameUI::End()
{
    m_pPauseMenu->End();
    delete m_pPauseMenu;
    m_pPauseMenu = nullptr;

    m_pGameEndMenu->End();
    delete m_pGameEndMenu;
    m_pGameEndMenu = nullptr;
}

void CInGameUI::CreateIngameUI()
{
    auto font16 = twFontManager->LoadFont(twResourceManager->GetFontFace("AGENCYB"), 16);
    auto font24 = twFontManager->LoadFont(twResourceManager->GetFontFace("AGENCYB"), 24);

    // Counter Back -----------------------------------------------

    auto counterBack = twActiveUIWorld->CreateUIEntity();
    counterBack->m_Transform.SetAnchorPoint(0.0f, 1.0f);
    counterBack->m_Transform.SetPositionOffset(0.0f, -62.0f, 10.0f);

    auto counterBackDrawable = twRenderer->CreateUIDrawable();
    counterBackDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    counterBackDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_ingame_counter_mid"));

    counterBack->SetDrawable(counterBackDrawable);

    twActiveUIWorld->AddUIEntity(counterBack);

    // Bar Left -----------------------------------------------

    auto barLeftBack = twActiveUIWorld->CreateUIEntity();
    barLeftBack->m_Transform.SetAnchorPoint(0.0f, 1.0f);
    barLeftBack->m_Transform.SetPositionOffset(-275.0f, -19.0f, 10.0f);

    auto barLeftBackDrawable = twRenderer->CreateUIDrawable();
    barLeftBackDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    barLeftBackDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_ingame_bar_left"));

    barLeftBack->SetDrawable(barLeftBackDrawable);

    twActiveUIWorld->AddUIEntity(barLeftBack);

    // Bar Left Fill -----------------------------------------------

    auto barLeftFillBack = twActiveUIWorld->CreateUIEntity();
    barLeftFillBack->m_Transform.SetAnchorPoint(0.0f, 1.0f);
    barLeftFillBack->m_Transform.SetPositionOffset(-272.0f, -19.0f, 9.0f);
    barLeftFillBack->m_Transform.SetRotationDegrees(180.0f);

    m_pBarLeft = twRenderer->CreateUIDrawable();
    m_pBarLeft->m_Material.SetMaterial(twResourceManager->GetMaterial("UIFill"));
    float value = 1.0f;
    m_pBarLeft->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
    m_pBarLeft->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_ingame_bar_fill"));

    barLeftFillBack->SetDrawable(m_pBarLeft);

    twActiveUIWorld->AddUIEntity(barLeftFillBack);

    // Bar Right -----------------------------------------------

    auto barRightBack = twActiveUIWorld->CreateUIEntity();
    barRightBack->m_Transform.SetAnchorPoint(0.0f, 1.0f);
    barRightBack->m_Transform.SetPositionOffset(275.0f, -19.0f, 10.0f);

    auto barRightBackDrawable = twRenderer->CreateUIDrawable();
    barRightBackDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    barRightBackDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_ingame_bar_right"));

    barRightBack->SetDrawable(barRightBackDrawable);

    twActiveUIWorld->AddUIEntity(barRightBack);

    // Bar Right Fill -----------------------------------------------

    auto barRightFillBack = twActiveUIWorld->CreateUIEntity();
    barRightFillBack->m_Transform.SetAnchorPoint(0.0f, 1.0f);
    barRightFillBack->m_Transform.SetPositionOffset(275.0f, -19.0f, 9.0f);

    m_pBarRight = twRenderer->CreateUIDrawable();
    m_pBarRight->m_Material.SetMaterial(twResourceManager->GetMaterial("UIFill"));
    m_pBarRight->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &value);
    m_pBarRight->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_ingame_bar_fill"));

    barRightFillBack->SetDrawable(m_pBarRight);

    twActiveUIWorld->AddUIEntity(barRightFillBack);

    // Font Current Points -------------------------------------------------------------

    auto fontCurrentPoints = twActiveUIWorld->CreateUIEntity();
    fontCurrentPoints->m_Transform.SetAnchorPoint(0.0f, 1.0f);
    fontCurrentPoints->m_Transform.SetPositionOffset(9.0f, -33.0f, 5.0f);

    m_pCurrentPoints = twFontManager->CreateText();
    m_pCurrentPoints->Set(font16, "0 x1,00", 1.0f);

    auto currentPointsTextDrawable = twRenderer->CreateFontDrawable();
    currentPointsTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    currentPointsTextDrawable->m_pText = m_pCurrentPoints;
    currentPointsTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    fontCurrentPoints->SetDrawable(currentPointsTextDrawable);
    twActiveUIWorld->AddUIEntity(fontCurrentPoints);

    // Font Total Points -------------------------------------------------------------

    auto fontTotalPoints = twActiveUIWorld->CreateUIEntity();
    fontTotalPoints->m_Transform.SetAnchorPoint(0.0f, 1.0f);
    fontTotalPoints->m_Transform.SetPositionOffset(9.0f, -96.0f, 5.0f);

    m_pTotalPoints = twFontManager->CreateText();
    m_pTotalPoints->Set(font24, "0", 1.0f);

    auto totalPointsTextDrawable = twRenderer->CreateFontDrawable();
    totalPointsTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    totalPointsTextDrawable->m_pText = m_pTotalPoints;
    totalPointsTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    fontTotalPoints->SetDrawable(totalPointsTextDrawable);
    twActiveUIWorld->AddUIEntity(fontTotalPoints);
}

void CInGameUI::UpdateIngameUI()
{
    // Current Points
    std::stringstream currentPoints;
    currentPoints << (size_t)CGameInfo::Instance().m_CurrentPoints << " x";
    currentPoints << std::fixed << std::setprecision(2) << CGameInfo::Instance().m_Multiplier;
    m_pCurrentPoints->SetText(currentPoints.str());

    // Total Points
    std::string totalPoints = std::to_string((size_t)CGameInfo::Instance().m_TotalPoints);
    m_pTotalPoints->SetText(totalPoints);

    // Resource bars
    float resource = CGameInfo::Instance().m_PlayerResourcePercentage;
    m_pBarLeft->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &resource);
    m_pBarRight->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &resource);
}

void CInGameUI::CheckInput()
{
    if (twGamepad.IsConnected(0))
    {
        m_UIInput.m_Left = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogLeft, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_Right = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogRight, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_Up = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogUp, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_Down = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogDown, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_ButtonHold = twGamepad.IsState(triebWerk::EGamepadButton::A, triebWerk::EButtonState::Pressed, 0);
        m_UIInput.m_Select = twGamepad.IsState(triebWerk::EGamepadButton::A, triebWerk::EButtonState::Up, 0);
        m_UIInput.m_Back = twGamepad.IsState(triebWerk::EGamepadButton::B, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_Pause = twGamepad.IsState(triebWerk::EGamepadButton::Start, triebWerk::EButtonState::Down, 0);
    }
    else
    {
        m_UIInput.m_Left = twKeyboard.IsState(triebWerk::EKey::Left, triebWerk::EButtonState::Down);
        m_UIInput.m_Right = twKeyboard.IsState(triebWerk::EKey::Right, triebWerk::EButtonState::Down);
        m_UIInput.m_Up = twKeyboard.IsState(triebWerk::EKey::Up, triebWerk::EButtonState::Down);
        m_UIInput.m_Down = twKeyboard.IsState(triebWerk::EKey::Down, triebWerk::EButtonState::Down);
        m_UIInput.m_Select = twKeyboard.IsState(triebWerk::EKey::Return, triebWerk::EButtonState::Down);
        m_UIInput.m_Back = twKeyboard.IsState(triebWerk::EKey::Back, triebWerk::EButtonState::Down);
        m_UIInput.m_Pause = twKeyboard.IsState(triebWerk::EKey::Escape, triebWerk::EButtonState::Down);
    }
}
