#include <CPlayer.h>

#include <iostream>
#include <CCheckpoint.h>
#include <CGameInfo.h>
#include <CMeshDrawable.h>
#include <CPoints.h>
#include <CPlayerDangerHitbox.h>

CPlayer::CPlayer()
    : m_CurrentResource(MaxResource)
    , m_InFullControlMode(false)
    , m_InBoostMode(false)
    , m_pTrailMesh(nullptr)
    , m_pMainCamera(nullptr)
    , m_IsDead(false)
    , m_MetersFlewn(0.0f)
    , m_LastZ(0.0f)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
    m_pMainCamera = twEngine.m_pRenderer->GetCurrentActiveCamera();
    m_LastZ = m_pEntity->m_Transform.GetPosition().m128_f32[2];

    CreateTrail();
	CreateFloorEffect();
	CreatePlayerDangerHitbox();
}

void CPlayer::Update()
{
    CheckInput();
    CheckResource();
    SetSpeed();
    CalculateDistanceFlewn();
    UpdateTrail();
	UpdateFloorEffect();
}

void CPlayer::LateUpdate()
{
    m_pTrail->m_Transform.SetPosition(m_pEntity->m_Transform.GetPosition());
    m_pTrail->m_Transform.SetRotation(m_pEntity->m_Transform.GetRotation());

    CGameInfo::Instance().m_PlayerPosition = m_pEntity->m_Transform.GetPosition().m128_f32[2];
	CGameInfo::Instance().m_PlayerPositionX = m_pEntity->m_Transform.GetPosition().m128_f32[0];

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
        CGameInfo::Instance().m_TotalPoints += points->GetPointAmount();
    }
    else if (entity->m_ID.GetHash() == triebWerk::StringHasher("Checkpoint"))
    {
        ((CCheckpoint*)entity->GetBehaviour())->Collected();
    }
    else if (entity->m_Tag.HasTag("Death"))
    {
        if (!GodMode)
        {
            if (m_IsDead == false)
                triebWerk::CDebugLogfile::Instance().LogfText(triebWerk::CDebugLogfile::ELogType::Text, false, entity->m_ID.GetDescribtion().c_str());
            m_IsDead = true;
        }
    }
}

void CPlayer::CollisionStay(triebWerk::CCollisionEvent a_Collision)
{
    CheckSideWall(a_Collision);
}

void CPlayer::Reset()
{
    m_CurrentResource = MaxResource;
    m_InFullControlMode = false;
    m_InBoostMode = false;
    m_IsDead = false;
    m_MetersFlewn = 0.0f;
    m_LastZ = 0.0f;

    m_pEntity->m_Transform.SetPosition(0.0f, 1.0f, 0.0f);
    CGameInfo::Instance().m_PlayerPosition = 0.0f;
}

float CPlayer::GetMetersFlewn() const
{
    return m_MetersFlewn;
}

bool CPlayer::HasDied() const
{
    return m_IsDead;
}

void CPlayer::CreateTrail()
{
    m_pTrail = twActiveWorld->CreateEntity();

    m_pTrailMesh = twRenderer->CreateMeshDrawable();
    m_pTrailMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_effect_trail");
    m_pTrailMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("PlayerTrail"));
    m_pTrailMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_effect_trail_red"));
	m_pTrailMesh->m_Material.m_pPixelShader.SetTexture(2, twResourceManager->GetTexture2D("T_effect_trail_blue"));
	m_pTrailMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
	float blend = 0.0f;
	m_pTrailMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &blend);
    m_pTrail->SetDrawable(m_pTrailMesh);

    twActiveWorld->AddEntity(m_pTrail);
}

void CPlayer::CreateFloorEffect()
{
	auto entity = twActiveWorld->CreateEntity();
	DirectX::XMVECTOR pos = m_pEntity->m_Transform.GetPosition();
	pos.m128_f32[1] -= 1.8f;
	pos.m128_f32[2] -= 0.5f;
	entity->m_Transform.SetPosition(pos);
	entity->m_Transform.SetScale(5, 5, 5);

	m_pEntity->m_Transform.AddChild(&entity->m_Transform);

	triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("TransparentScrolling"));
	mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_floor_emissve_grid"));
	mesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("T_grid_cutout_circle"));
	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	mesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &DirectX::XMFLOAT2(0.0f, -1.0f));
	m_pFloorEffectMaterial = &mesh->m_Material;
	entity->SetDrawable(mesh);

	twActiveWorld->AddEntity(entity);
}

void CPlayer::CreatePlayerDangerHitbox()
{
	m_pDangerHitbox = twActiveWorld->CreateEntity();
	m_pDangerHitbox->m_Transform.SetPosition(0.0f, 0.0f, 0.0f);
	m_pEntity->m_Transform.AddChild(&m_pDangerHitbox->m_Transform);

	auto hitBoxBehavior = new CPlayerDangerHitbox();
	m_pDangerHitbox->SetBehaviour(hitBoxBehavior);

	auto physicEntity = twActiveWorld->m_pPhysicWorld->CreatePhysicEntity();

	auto collbox = twActiveWorld->m_pPhysicWorld->CreateAABBCollider();
	collbox->SetSize(0.93f * 2.0f, 0.34f * 2.0f, 40.0f);
	collbox->m_CheckCollision = true;
	physicEntity->AddCollider(collbox);

	auto body = twActiveWorld->m_pPhysicWorld->CreateBody();
	body->m_GravityFactor = 0.0f;
	physicEntity->SetBody(body);

	m_pDangerHitbox->SetPhysicEntity(physicEntity);

	twActiveWorld->AddEntity(m_pDangerHitbox);
}

void CPlayer::CheckInput()
{
    // Gamepad Input
    if (twGamepad.IsConnected(0))
    {
        m_PlayerInput.m_Left = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogLeft, triebWerk::EButtonState::Pressed, 0);
        m_PlayerInput.m_Right = twGamepad.IsState(triebWerk::EGamepadButton::LAnalogRight, triebWerk::EButtonState::Pressed, 0);

        m_PlayerInput.m_FullControl =
            twGamepad.IsState(triebWerk::EGamepadButton::LT, triebWerk::EButtonState::Pressed, 0) ||
            twGamepad.IsState(triebWerk::EGamepadButton::LB, triebWerk::EButtonState::Pressed, 0);

        m_PlayerInput.m_Boost =
            twGamepad.IsState(triebWerk::EGamepadButton::RT, triebWerk::EButtonState::Pressed, 0) ||
            twGamepad.IsState(triebWerk::EGamepadButton::RB, triebWerk::EButtonState::Pressed, 0);

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

        m_PlayerInput.m_FullControl = twKeyboard.IsState(triebWerk::EKey::Q, triebWerk::EButtonState::Down);
        m_PlayerInput.m_Boost = twKeyboard.IsState(triebWerk::EKey::E, triebWerk::EButtonState::Down);

        if (m_PlayerInput.m_Left)
            m_PlayerInput.m_MoveKeyDistance = -1.0f;
        else if (m_PlayerInput.m_Right)
            m_PlayerInput.m_MoveKeyDistance = 1.0f;
        else
            m_PlayerInput.m_MoveKeyDistance = 0.0f;
    }
}

void CPlayer::CheckResource()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    bool gainResource = true;
    bool fullControlEffect = false;
    bool boostEffect = false;
    bool shieldEffect = false;

    // Full Control
    if (m_PlayerInput.m_FullControl)
    {
        gainResource = false;

        if (m_CurrentResource > 0.0f)
            fullControlEffect = true;
    }

    if (fullControlEffect)
    {
        m_CurrentResource -= FullControlCost * twTime->GetDeltaTime();
        m_InFullControlMode = true;
        gameInfo.m_EffectFullControl = true;
    }
    else
    {
        m_InFullControlMode = false;
        gameInfo.m_EffectFullControl = false;
    }

    // Boost
    if (m_PlayerInput.m_Boost)
    {
        gainResource = false;

        if (m_CurrentResource > 0.0f)
            boostEffect = true;
    }

    if (boostEffect)
    {
        m_CurrentResource -= BoostCost * twTime->GetDeltaTime();
        m_InBoostMode = true;
        gameInfo.m_EffectBoost = true;
        gameInfo.m_FlyBoostSpeed = BoostSpeed;
    }
    else
    {
        m_InBoostMode = false;
        gameInfo.m_EffectBoost = false;
        gameInfo.m_FlyBoostSpeed = 0.0f;
    }

    // Resource
    if (gainResource)
    {
        m_CurrentResource += ResourcePerSecond * twTime->GetDeltaTime();

        if (m_CurrentResource > MaxResource)
            m_CurrentResource = MaxResource;
    }
}

void CPlayer::SetSpeed()
{
    CGameInfo& gameInfo = CGameInfo::Instance();

    DirectX::XMVECTOR velocity = m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity;
    

    // Handles speed in X direction
    if (m_InFullControlMode == true)
    {
        if (m_PlayerInput.m_Left)
            velocity.m128_f32[0] = FullControlSpeed * m_PlayerInput.m_MoveKeyDistance;
        else if (m_PlayerInput.m_Right)
            velocity.m128_f32[0] = FullControlSpeed * m_PlayerInput.m_MoveKeyDistance;
        else
            velocity.m128_f32[0] = 0.0f;

        CGameInfo::Instance().m_EffectFullControlStrength = std::fabsf(m_PlayerInput.m_MoveKeyDistance);
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

    // Speed in Y Direction
    velocity.m128_f32[2] = gameInfo.m_FlyStandardSpeed + gameInfo.m_FlyDifficultySpeed + gameInfo.m_FlyBoostSpeed;

    // set the new speed
    m_pEntity->GetPhysicEntity()->GetBody()->m_Velocity = velocity;
}

void CPlayer::CalculateDistanceFlewn()
{
    float currentZ = m_pEntity->m_Transform.GetPosition().m128_f32[2];

    m_MetersFlewn = currentZ - m_LastZ;
    m_LastZ = currentZ;
}

void CPlayer::UpdateTrail()
{
    float dt = twTime->GetTimeSinceStartup();
    float curvature = m_PlayerInput.m_MoveKeyDistance;
    m_pTrailMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &dt);
    m_pTrailMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &curvature);
}

void CPlayer::UpdateFloorEffect()
{
	float time = twTime->GetTimeSinceStartup();
	m_pFloorEffectMaterial->m_ConstantBuffer.SetValueInBuffer(6, &time);
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
