#include <CMenuScene.h>

#include <CGameInfo.h>
#include <CMainMenu.h>
#include <CPostEffects.h>

CMenuScene::CMenuScene()
    : m_MenuBackgroundScene()
    , m_UIInput()
    , m_pCurrentMenu(nullptr)
{
}

CMenuScene::~CMenuScene()
{
}

void CMenuScene::Start()
{
    twActiveUIWorld->SetReferenceResolution(1920, 1080.0f, triebWerk::CUIWorld::EScreenMatchState::Width);
    twFontManager->LoadFont(twResourceManager->GetFontFace("AGENCYB"), 30);

    CreatePostEffects();
    SetCurrentMenu(new CMainMenu());

    m_MenuBackgroundScene.Start();
}

void CMenuScene::Update()
{
    if (twKeyboard.IsState(triebWerk::EKey::F3, triebWerk::EButtonState::Down))
    {
        if (!twDebug->IsInDebug())
            twDebug->Enable();
        else
            twDebug->Disable();
    }

    CheckInput();

    if (m_pCurrentMenu != nullptr)
        m_pCurrentMenu->Update(m_UIInput);

    m_MenuBackgroundScene.Update();
}

void CMenuScene::End()
{
    if (m_pCurrentMenu != nullptr)
    {
        m_pCurrentMenu->End();
        delete m_pCurrentMenu;
        m_pCurrentMenu = nullptr;
    }

    m_MenuBackgroundScene.End();
}

void CMenuScene::Resume()
{
    if (m_pCurrentMenu != nullptr)
    {
        m_pCurrentMenu->Resume();
    }
}

void CMenuScene::CheckInput()
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

void CMenuScene::SetCurrentMenu(IMenu* a_pMenu)
{
    if (m_pCurrentMenu != nullptr)
    {
        m_pCurrentMenu->End();
        delete m_pCurrentMenu;
    }

    m_pCurrentMenu = a_pMenu;
    m_pCurrentMenu->Start();
}

void CMenuScene::CreatePostEffects()
{
    auto entity = twActiveWorld->CreateEntity();
    entity->SetBehaviour(new CPostEffects());
    twActiveWorld->AddEntity(entity);
}
