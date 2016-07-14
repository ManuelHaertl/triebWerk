#include <CPoints.h>

#include <CCollectedPoint.h>

CPoints::CPoints()
    : m_RotateSpeedX(0.0f)
    , m_RotateSpeedY(0.0f)
    , m_RotateSpeedZ(0.0f)
    , m_pSphere(nullptr)
    , m_pSphereBuffer(nullptr)
{
}

CPoints::~CPoints()
{
}

void CPoints::Start()
{
    m_RotateSpeedX = twRandom::GetNumber(MinRotateSpeed, MaxRotateSpeed);
    m_RotateSpeedY = twRandom::GetNumber(MinRotateSpeed, MaxRotateSpeed);
    m_RotateSpeedZ = twRandom::GetNumber(MinRotateSpeed, MaxRotateSpeed);

    CreateSphere();
}

void CPoints::Update()
{
    const float dt = twTime->GetDeltaTime();
    float timeSinceStartup = twTime->GetTimeSinceStartup();
    
    m_pEntity->m_Transform.RotateDegrees(0.0f, 0.0f, dt * RotateSpeedZ);
    m_pSphere->m_Transform.RotateDegrees(dt * m_RotateSpeedX, dt * m_RotateSpeedY, dt * m_RotateSpeedZ);

    //m_pSphereBuffer->SetValueInBuffer(4, &timeSinceStartup);
}

void CPoints::End()
{
    twActiveWorld->RemoveEntity(m_pSphere);
}

void CPoints::Collected()
{
    // disable current entity
    m_pEntity->GetDrawable()->SetActive(false);
    m_pSphere->GetDrawable()->SetActive(false);
    m_pEntity->RemovePhysicEntity();

    // create a new one
    auto entity = twActiveWorld->CreateEntity();
    entity->m_Transform.SetPosition(m_pEntity->m_Transform.GetPosition());
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_pointsEffect");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("PointExplosion"));
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
    mesh->m_Material.m_pGeometryShader.SetTexture(0, twResourceManager->GetTexture2D("t_noise"));
	mesh->m_D3DStates.m_pRasterizerState = twEngine.m_pGraphics->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);

    DirectX::XMFLOAT3 color = { 1.0f, 1.0f, 0.0f };
    int speed = 0;
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &color);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);

    entity->SetDrawable(mesh);
    entity->SetBehaviour(new CCollectedPoint());
    twActiveWorld->AddEntity(entity);
}

void CPoints::CreateSphere()
{
    m_pSphere = twActiveWorld->CreateEntity();

    // Transform
    m_pSphere->m_Transform.SetPosition(m_pEntity->m_Transform.GetPosition());
    m_pSphere->m_Transform.SetScale(0.35f, 0.35f, 0.35f);
    m_pEntity->m_Transform.AddChild(&m_pSphere->m_Transform);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twResourceManager->GetMesh("ms_sphere");
    mesh->m_Material.SetMaterial(twResourceManager->GetMaterial("Sun"));
    mesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("t_whitenoise"));
    mesh->m_Material.m_pVertexShader.SetInstanceData(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), 12);
    m_pSphere->SetDrawable(mesh);

    m_pSphereBuffer = &mesh->m_Material.m_ConstantBuffer;

    twActiveWorld->AddEntity(m_pSphere);
}
