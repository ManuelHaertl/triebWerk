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
    m_pEntity->GetPhysicEntity()->GetBody()->m_GravityFactor = 0.0f;
    auto coll = twPhysic->CreateAABBCollider();
    coll->CreateFromMesh(nullptr);
    m_pEntity->GetPhysicEntity()->AddCollider(coll);

    m_pBlock = twWorld->CreateEntity();
    m_pBlock->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    auto collider = twPhysic->CreateAABBCollider();
    collider->CreateFromMesh(nullptr);
    m_pBlock->GetPhysicEntity()->AddCollider(collider);
    m_pBlock->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
    twWorld->AddEntity(m_pBlock);
    m_pBlock->m_Transform.SetPosition(0.0f, 10.0f, 0.0f);
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
