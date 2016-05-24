#include <CPlayer.h>

CPlayer::CPlayer() :
    m_CurrentMaxSpeedValue(0.0f),
    m_pMainCamera(nullptr),
    m_MetersFlewn(0.0f),
    m_LastZ(0.0f)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
    m_pMainCamera = twEngine.m_pRenderer->GetCurrentActiveCamera();
    m_LastZ = m_pEntity->m_Transform.GetPosition().m128_f32[2];
}

void CPlayer::Update()
{
    SetSpeed();

    float currentZ = m_pEntity->m_Transform.GetPosition().m128_f32[2];

    m_MetersFlewn = currentZ - m_LastZ;
    m_LastZ = currentZ;
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
    CheckSideWall(a_Collision);
}

void CPlayer::CollisionStay(triebWerk::CCollisionEvent a_Collision)
{
    CheckSideWall(a_Collision);
}

float CPlayer::GetMetersFlewn() const
{
    return m_MetersFlewn;
}

void CPlayer::SetSpeed()
{
    DirectX::XMVECTOR velocity = m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity;

    bool keyboardLeft = twKeyboard.IsState(triebWerk::EKey::Left, triebWerk::EButtonState::Pressed);
    bool keyboardRight = twKeyboard.IsState(triebWerk::EKey::Right, triebWerk::EButtonState::Pressed);

    bool left = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogLeft, triebWerk::EButtonState::Pressed, 0) | keyboardLeft;
    bool right = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogRight, triebWerk::EButtonState::Pressed, 0) |keyboardRight;

    if (keyboardLeft)
        m_CurrentMaxSpeedValue = -32768.0f;
    else if (keyboardRight)
        m_CurrentMaxSpeedValue = 32767.0f;
    else
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
            m_CurrentMaxSpeedValue /= (32768.0f - deadZone);
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

    velocity.m128_f32[2] = FlySpeed;
    m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity = velocity;
}

void CPlayer::SetCamera()
{
    DirectX::XMVECTOR camPos = m_pMainCamera->m_Transform.GetPosition();
    DirectX::XMVECTOR pos = m_pEntity->m_Transform.GetPosition();

    camPos.m128_f32[0] = pos.m128_f32[0];
    camPos.m128_f32[1] = CameraPosY;
    camPos.m128_f32[2] = pos.m128_f32[2] - CameraMinusPosZ;
    m_pMainCamera->m_Transform.SetPosition(camPos);
}

void CPlayer::SetRotation()
{
    DirectX::XMVECTOR rotationPlayer = DirectX::XMVectorSet(RotationX, 0.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR rotationCamera = DirectX::XMVectorSet(CameraRotationX, 0.0f, 0.0f, 0.0f);

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

void CPlayer::CheckSideWall(triebWerk::CCollisionEvent a_Collision)
{
    if (a_Collision.m_pPartner->m_ID.GetName() == "SideLeft")
    {
        DirectX::XMVECTOR pos = m_pEntity->m_Transform.GetPosition();
        triebWerk::CAABBCollider* coll = static_cast<triebWerk::CAABBCollider*>(a_Collision.m_pPartner->GetPhysicEntity()->m_Collider[0]);
        float boundary = coll->GetWorldMax().m128_f32[0];

        if (pos.m128_f32[0] < boundary)
        {
            pos.m128_f32[0] = boundary;
            m_pEntity->m_Transform.SetPosition(pos);
        }
    }
    else if (a_Collision.m_pPartner->m_ID.GetName() == "SideRight")
    {
        DirectX::XMVECTOR pos = m_pEntity->m_Transform.GetPosition();
        triebWerk::CAABBCollider* coll = static_cast<triebWerk::CAABBCollider*>(a_Collision.m_pPartner->GetPhysicEntity()->m_Collider[0]);
        float boundary = coll->GetWorldMin().m128_f32[0];

        if (pos.m128_f32[0] > boundary)
        {
            pos.m128_f32[0] = boundary;
            m_pEntity->m_Transform.SetPosition(pos);
        }
    }
}
