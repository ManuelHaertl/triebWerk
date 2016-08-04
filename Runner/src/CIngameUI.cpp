#include <CIngameUI.h>

#include <CPauseMenu.h>
#include <CEngine.h>

CInGameUI::CInGameUI()
    : m_UIInput()
    , m_pPauseMenu(nullptr)
{
}

CInGameUI::~CInGameUI()
{
}

void CInGameUI::Start()
{
    twActiveUIWorld->SetReferenceResolution(1920, 1080.0f, triebWerk::CUIWorld::EScreenMatchState::Width);
    twFontManager->LoadFont(twResourceManager->GetFontFace("AGENCYB"), 30);

    m_pPauseMenu = new CPauseMenu();
    m_pPauseMenu->Start();
}

void CInGameUI::Update()
{
    CheckInput();
    m_pPauseMenu->Update(m_UIInput);
}

void CInGameUI::End()
{
    m_pPauseMenu->End();
    delete m_pPauseMenu;
    m_pPauseMenu = nullptr;
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
