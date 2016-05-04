#include <CPlayer.h>

CPlayer::CPlayer() :
    m_CurrentMaxSpeedValue(0.0f),
    m_pMainCamera(nullptr)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
    m_pMainCamera = twEngine.m_pRenderer->GetCurrentActiveCamera();
}

void CPlayer::Update()
{
    SetSpeed();
}

void CPlayer::LateUpdate()
{
    if (!twDebug->IsInDebug())
    {
        SetCamera();
        SetRotation();
    }
}

void CPlayer::CollisionEnter(triebWerk::CCollisionEvent a_Collision)
{
    std::cout << "Enter with: " << a_Collision.m_pPartner << std::endl;
    twWorld->RemoveEntity(a_Collision.m_pPartner);
}

void CPlayer::SetSpeed()
{
    DirectX::XMVECTOR velocity = m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity;

    bool left = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogLeft, triebWerk::EButtonState::Pressed, 0);
    bool right = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogRight, triebWerk::EButtonState::Pressed, 0);

    m_CurrentMaxSpeedValue = static_cast<float>(twGamepad.GetLeftAnalogX(0));
    float currentMaxSpeed = 0.0f;

    if (m_CurrentMaxSpeedValue != 0.0f)
    {
        float deadZone = static_cast<float>(triebWerk::CXboxController::DEADZONE_LEFT_ANALOG);

        if (m_CurrentMaxSpeedValue >= 0)
        {
            m_CurrentMaxSpeedValue -= deadZone;
            m_CurrentMaxSpeedValue /= (32767.0f - deadZone);
        }
        else
        {
            m_CurrentMaxSpeedValue += deadZone;
            m_CurrentMaxSpeedValue /= (32767.0f - deadZone);
        }

        currentMaxSpeed = MaxSpeed * m_CurrentMaxSpeedValue;
    }

    if (left)
    {
        if (velocity.m128_f32[0] >= currentMaxSpeed)
        {
            velocity.m128_f32[0] -= Acceleration * twTime->GetDeltaTime();
        }
    }
    else if (right)
    {
        if (velocity.m128_f32[0] <= currentMaxSpeed)
        {
            velocity.m128_f32[0] += Acceleration * twTime->GetDeltaTime();
        }
    }
    else
    {
        if (velocity.m128_f32[0] < 0.0f)
        {
            velocity.m128_f32[0] += Drag * twTime->GetDeltaTime();
            if (velocity.m128_f32[0] > 0.0f)
                velocity.m128_f32[0] = 0.0f;
        }
        else if (velocity.m128_f32[0] > 0.0f)
        {
            velocity.m128_f32[0] -= Drag * twTime->GetDeltaTime();
            if (velocity.m128_f32[0] < 0.0f)
                velocity.m128_f32[0] = 0.0f;
        }
    }

    m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity = velocity;
}

void CPlayer::SetCamera()
{
    DirectX::XMVECTOR camPos = m_pMainCamera->m_Transform.GetPosition();
    DirectX::XMVECTOR pos = m_pEntity->m_Transform.GetPosition();

    camPos.m128_f32[0] = pos.m128_f32[0];
    m_pMainCamera->m_Transform.SetPosition(camPos);
}

void CPlayer::SetRotation()
{
    DirectX::XMVECTOR rotationPlayer = DirectX::XMVectorSet(347.0f, 0.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR rotationCamera = DirectX::XMVectorSet(5.7f, 0.0f, 0.0f, 0.0f);

    float lrValue = -1.0f;
    float speed = m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity.m128_f32[0];
    if (speed < 0.0f)
    {
        lrValue = 1.0f;
        speed *= -1.0f;
    }

    // player rotation
    rotationPlayer.m128_f32[1] = 0.0f;

    if (speed == 0.0f)
        rotationPlayer.m128_f32[2] = 0.0f;
    else
        rotationPlayer.m128_f32[2] = MaxRotation * m_CurrentMaxSpeedValue * -1;

    // camera rotation
    if (speed != 0.0f)
    {
        float percent = speed / MaxSpeed;
        float rotationValue = percent * MaxRotation * lrValue;
        rotationCamera.m128_f32[2] = rotationValue * RotationCameraFactor;
    }
    else
    {
        rotationCamera.m128_f32[2] = 0.0f;
    }

    m_pEntity->m_Transform.SetRotationDegrees(rotationPlayer);
    m_pMainCamera->m_Transform.SetRotationDegrees(rotationCamera);
}
