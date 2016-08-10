#include <CMenuScene.h>

#include <CGameInfo.h>
#include <CMainMenu.h>
#include <CManualMenu.h>
#include <CHighscoreMenu.h>
#include <CCreditsMenu.h>
#include <COptionsMenu.h>
#include <CPostEffects.h>

CMenuScene::CMenuScene()
    : m_MenuBackgroundScene()
    , m_UIInput()
    , m_pMainMenu(nullptr)
    , m_pSecondMenu(nullptr)
{
}

CMenuScene::~CMenuScene()
{
}

void CMenuScene::Start()
{
    twActiveUIWorld->SetReferenceResolution(1920, 1080.0f, triebWerk::CUIWorld::EScreenMatchState::Height);
    CGameInfo::Instance().m_Menu = EMenus::Main;

    CreatePostEffects();
    m_pMainMenu = new CMainMenu();
    m_pMainMenu->Start();

    m_MenuBackgroundScene.Start();


	std::vector<triebWerk::CSound*> music;

	twResourceManager->GetAll("data//Audio//BGM//menu", &music);
	if (music.size() > 0)
		m_pBackgroundMusic = music[0];

	twAudio->PlayBGM(m_pBackgroundMusic, true, true);
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

    m_pMainMenu->Update(m_UIInput);
    if (m_pSecondMenu != nullptr)
        m_pSecondMenu->Update(m_UIInput);

    if (CGameInfo::Instance().m_ChangeMenu)
    {
        CGameInfo::Instance().m_ChangeMenu = false;

        switch (CGameInfo::Instance().m_Menu)
        {
        case EMenus::Main:
            RemoveSecondMenu();
            break;
        case EMenus::Highscore:
            SetCurrentMenu(new CHighscoreMenu());
            break;
        case EMenus::Options:
            SetCurrentMenu(new COptionsMenu());
            break;
        case EMenus::Credits:
            SetCurrentMenu(new CCreditsMenu());
            break;
        case EMenus::Manual:
            SetCurrentMenu(new CManualMenu());
            break;
        }
    }

    m_MenuBackgroundScene.Update();
}

void CMenuScene::End()
{
    if (m_pMainMenu != nullptr)
    {
        m_pMainMenu->End();
        delete m_pMainMenu;
        m_pMainMenu = nullptr;
    }

    if (m_pSecondMenu != nullptr)
    {
        m_pSecondMenu->End();
        delete m_pSecondMenu;
        m_pSecondMenu = nullptr;
    }

    m_MenuBackgroundScene.End();
}

void CMenuScene::Resume()
{
    CGameInfo::Instance().m_Menu = EMenus::Main;
    if (m_pMainMenu != nullptr)
    {
        m_pMainMenu->Resume();
    }
	twAudio->PlayBGM(m_pBackgroundMusic, true, true);

    twActiveUIWorld->SetReferenceResolution(1920, 1080.0f, triebWerk::CUIWorld::EScreenMatchState::Height);
}

void CMenuScene::CheckInput()
{
    if (twGamepad.IsConnected(0))
    {
        m_UIInput.m_Left = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogLeft, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_Right = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogRight, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_Up = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogUp, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_Down = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogDown, triebWerk::EButtonState::Down, 0);
        m_UIInput.m_LeftHold = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogLeft, triebWerk::EButtonState::Pressed, 0);
        m_UIInput.m_RightHold = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogRight, triebWerk::EButtonState::Pressed, 0);
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
        m_UIInput.m_LeftHold = twKeyboard.IsState(triebWerk::EKey::Left, triebWerk::EButtonState::Pressed);
        m_UIInput.m_RightHold = twKeyboard.IsState(triebWerk::EKey::Right, triebWerk::EButtonState::Pressed);
        m_UIInput.m_ButtonHold = twKeyboard.IsState(triebWerk::EKey::Return, triebWerk::EButtonState::Pressed);
        m_UIInput.m_Select = twKeyboard.IsState(triebWerk::EKey::Return, triebWerk::EButtonState::Up);
        m_UIInput.m_Back = twKeyboard.IsState(triebWerk::EKey::Back, triebWerk::EButtonState::Down);
        m_UIInput.m_Pause = twKeyboard.IsState(triebWerk::EKey::Escape, triebWerk::EButtonState::Down);
    }
}

void CMenuScene::SetCurrentMenu(IMenu* a_pMenu)
{
    if (m_pSecondMenu != nullptr)
    {
        m_pSecondMenu->End();
        delete m_pSecondMenu;
    }

    m_pSecondMenu = a_pMenu;
    m_pSecondMenu->Start();
}

void CMenuScene::RemoveSecondMenu()
{
    if (m_pSecondMenu != nullptr)
    {
        m_pSecondMenu->End();
        delete m_pSecondMenu;
        m_pSecondMenu = nullptr;
    }
}

void CMenuScene::CreatePostEffects()
{
    auto entity = twActiveWorld->CreateEntity();
    entity->SetBehaviour(new CPostEffects());
    twActiveWorld->AddEntity(entity);
}
