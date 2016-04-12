#include <CPlayer.h>

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
    std::cout << "Player start" << std::endl;
}

void CPlayer::Update()
{
    if (twKeyboard.IsState(triebWerk::EKey::Space, triebWerk::EButtonState::Down))
        std::cout << "Keyboard Space" << std::endl;

    if (twGamepad.IsState(triebWerk::EGamepadButton::A, triebWerk::EButtonState::Down, 0))
        std::cout << "Gamepad A" << std::endl;

    if (twMouse.IsState(triebWerk::EMouseButton::Left, triebWerk::EButtonState::Down))
        std::cout << "Mouse Left" << std::endl;
}

void CPlayer::End()
{
    std::cout << "Player end" << std::endl;
}
