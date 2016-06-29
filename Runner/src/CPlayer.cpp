#include <CPlayer.h>

#include <iostream>
#include <CCheckpoint.h>
#include <CGameInfo.h>
#include <CMeshDrawable.h>
#include <CPoints.h>

CPlayer::CPlayer() :
    m_IsDodging(false),
    m_DodgeSpeed(0.0f),
    m_CurrentDodgeCooldownTime(0.0f),
    m_CurrentDodgeTime(0.0f),
    m_pMainCamera(nullptr),
    m_IsDead(false),
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
    CheckInput();
    SetSpeed();
    CalculateDistanceFlewn();
    AddPointsForFlewnDistance();
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

    triebWerk::CEntity* entity = a_Collision.m_pPartner;
    if (entity->m_ID.GetHash() == triebWerk::StringHasher("Points"))
    {
        CPoints* points = (CPoints*)entity->GetBehaviour();
        points->Collected();

        // add a fixed amount to the total points
        CGameInfo::Instance().m_TotalPoints += points->m_Points;
    }
    else if (entity->m_ID.GetHash() == triebWerk::StringHasher("Checkpoint"))
    {
        entity->GetDrawable()->SetActive(false);
        entity->RemovePhysicEntity();

        ((CCheckpoint*)entity->GetBehaviour())->m_HasCollected = true;

        // Add the points you collected by flying
        CGameInfo& gameInfo = CGameInfo::Instance();
        gameInfo.m_TotalPoints += gameInfo.m_CurrentPoints * gameInfo.m_Multiplier;
        gameInfo.m_CurrentPoints = 0;
        gameInfo.m_Multiplier = 1.0f;
    }
    else if (entity->m_ID.GetHash() == triebWerk::StringHasher("Wall"))
    {
        if (m_IsDead == false)
            triebWerk::CDebugLogfile::Instance().LogfText(triebWerk::CDebugLogfile::ELogType::Warning, false, entity->m_ID.GetDescribtion().c_str());
        m_IsDead = true;
    }
}

void CPlayer::CollisionStay(triebWerk::CCollisionEvent a_Collision)
{
    CheckSideWall(a_Collision);
}

void CPlayer::Reset()
{
    m_IsDodging = false;
    m_DodgeSpeed = 0.0f;
    m_CurrentDodgeCooldownTime = 0.0f;
    m_CurrentDodgeTime = 0.0f;
    m_IsDead = false;
    m_MetersFlewn = 0.0f;
    m_LastZ = 0.0f;

    m_pEntity->m_Transform.SetPosition(0.0f, 1.0f, 0.0f);
}

float CPlayer::GetMetersFlewn() const
{
    return m_MetersFlewn;
}

bool CPlayer::HasDied() const
{
    return m_IsDead;
}

void CPlayer::CheckInput()
{
    // Gamepad Input
    if (twGamepad.IsConnected(0))
    {
        m_PlayerInput.m_Left = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogLeft, triebWerk::EButtonState::Pressed, 0);
        m_PlayerInput.m_Right = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogRight, triebWerk::EButtonState::Pressed, 0);

        m_PlayerInput.m_DodgeLeft =
            twGamepad.IsState(triebWerk::EGamepadButton::LT, triebWerk::EButtonState::Down, 0) ||
            twGamepad.IsState(triebWerk::EGamepadButton::LB, triebWerk::EButtonState::Down, 0);

        m_PlayerInput.m_DodgeRight =
            twGamepad.IsState(triebWerk::EGamepadButton::RT, triebWerk::EButtonState::Down, 0) ||
            twGamepad.IsState(triebWerk::EGamepadButton::RB, triebWerk::EButtonState::Down, 0);

        float xValue = static_cast<float>(twGamepad.GetLeftAnalogX(0));

        float deadZone = static_cast<float>(triebWerk::CXboxController::DEADZONE_LEFT_ANALOG);
        if (xValue > 0)
        {
            xValue -= deadZone;
            xValue /= (32767.0f - deadZone);
        }
        else if (xValue < 0)
        {
            xValue += deadZone;
            xValue /= (32768.0f - deadZone);
        }
        else
        {
            xValue = 0.0f;
        }

        m_PlayerInput.m_MoveKeyDistance = xValue;
    }

    //Keyboard Input
    else
    {
        m_PlayerInput.m_Left = twKeyboard.IsState(triebWerk::EKey::Left, triebWerk::EButtonState::Pressed);
        m_PlayerInput.m_Right = twKeyboard.IsState(triebWerk::EKey::Right, triebWerk::EButtonState::Pressed);

        m_PlayerInput.m_DodgeLeft = twKeyboard.IsState(triebWerk::EKey::Q, triebWerk::EButtonState::Down);
        m_PlayerInput.m_DodgeRight = twKeyboard.IsState(triebWerk::EKey::E, triebWerk::EButtonState::Down);
          
        if (m_PlayerInput.m_Left)
            m_PlayerInput.m_MoveKeyDistance = -1.0f;
        else if (m_PlayerInput.m_Right)
            m_PlayerInput.m_MoveKeyDistance = 1.0f;
        else
            m_PlayerInput.m_MoveKeyDistance = 0.0f;
    }
}

void CPlayer::SetSpeed()
{
    DirectX::XMVECTOR velocity = m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity;

    m_CurrentDodgeCooldownTime -= twTime->GetDeltaTime();
    if (m_IsDodging)
    {
        m_CurrentDodgeTime -= twTime->GetDeltaTime();
        if (m_CurrentDodgeTime <= 0.0f)
        {
            velocity.m128_f32[0] = 0.0f;
            m_IsDodging = false;
        }
    }

    if ((m_PlayerInput.m_DodgeLeft || m_PlayerInput.m_DodgeRight) && m_CurrentDodgeCooldownTime <= 0.0f)
    {
        m_CurrentDodgeCooldownTime = DodgeCooldown;
        m_CurrentDodgeTime = DodgeTime;
        m_IsDodging = true;

        m_DodgeSpeed = DodgeDistance / DodgeTime;
        if (m_PlayerInput.m_DodgeLeft)
            m_DodgeSpeed *= -1;
    }
    if (m_IsDodging)
    {
        if (DodgeTime == 0.0f)
            DodgeTime = 0.001f;
        
        velocity.m128_f32[0] = m_DodgeSpeed;
    }

    else
    {
        float currentMaxSpeed = MaxSpeed * m_PlayerInput.m_MoveKeyDistance;

        // move to left or right and don't go over the max speed
        if (m_PlayerInput.m_Left && velocity.m128_f32[0] >= currentMaxSpeed)
        {
            velocity.m128_f32[0] -= Acceleration * twTime->GetDeltaTime();
        }
        else if (m_PlayerInput.m_Right && velocity.m128_f32[0] <= currentMaxSpeed)
        {
            velocity.m128_f32[0] += Acceleration * twTime->GetDeltaTime();
        }
        // if there is no input, the spaceship shall deaccelerate faster (with a drag)
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
    }

    // set the new speed
    velocity.m128_f32[2] = FlySpeed;
    m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity = velocity;
}

void CPlayer::CalculateDistanceFlewn()
{
    float currentZ = m_pEntity->m_Transform.GetPosition().m128_f32[2];

    m_MetersFlewn = currentZ - m_LastZ;
    m_LastZ = currentZ;
}

void CPlayer::AddPointsForFlewnDistance()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    gameInfo.m_CurrentPoints += m_MetersFlewn * gameInfo.m_PointsPerMeter;
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
        rotationPlayer.m128_f32[2] = MaxRotation * m_PlayerInput.m_MoveKeyDistance * -1;

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
