#include <CPlayer.h>

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
    m_pEntity->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    m_pEntity->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
    m_pEntity->GetPhysicEntity()->GetBody()->m_GravityFactor = 0.2f;
    m_pEntity->GetPhysicEntity()->AddCollider(twPhysic->CreateAABBCollider());

    auto brumbrum = twWorld->CreateEntity();
    brumbrum->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    brumbrum->GetPhysicEntity()->AddCollider(twPhysic->CreateAABBCollider());
    twWorld->AddEntity(brumbrum);
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

}
