#include <CPoints.h>

#include <CCollectedPoint.h>

DirectX::XMFLOAT3 CPoints::Color[3] = { DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) };

CPoints::CPoints(const size_t a_AmountID)
    : m_AmountID(a_AmountID)
    , m_RotateSpeedX(0.0f)
    , m_RotateSpeedY(0.0f)
    , m_RotateSpeedZ(0.0f)
    , m_pSphere(nullptr)
    , m_pSphereMaterial(nullptr)
	, m_pGodray(nullptr)
{
}

CPoints::~CPoints()
{
}

void CPoints::Start()
{
    static_cast<triebWerk::CMeshDrawable*>(m_pEntity->GetDrawable())->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &(Color[m_AmountID]));

    m_RotateSpeedX = twRandom::GetNumber(MinRotateSpeed, MaxRotateSpeed);
    m_RotateSpeedY = twRandom::GetNumber(MinRotateSpeed, MaxRotateSpeed);
    m_RotateSpeedZ = twRandom::GetNumber(MinRotateSpeed, MaxRotateSpeed);

    CreateSphere();
	
	//only set a godray if the point is rare
	if(m_AmountID == PointCountWithGodray)
		CreateGodray();

}

void CPoints::Update()
{
    const float dt = twTime->GetDeltaTime();
    float timeSinceStartup = twTime->GetTimeSinceStartup();
    
    m_pEntity->m_Transform.RotateDegrees(0.0f, 0.0f, dt * RotateSpeedZ);
    m_pSphere->m_Transform.RotateDegrees(dt * m_RotateSpeedX, dt * m_RotateSpeedY, dt * m_RotateSpeedZ);

	m_pSphereMaterial->m_pVertexShader.SetInstanceData(5, &timeSinceStartup, sizeof(float));
}

void CPoints::End()
{
    twActiveWorld->RemoveEntity(m_pSphere);
	if(m_pGodray != nullptr)
		twActiveWorld->RemoveEntity(m_pGodray);
}

void CPoints::Collected()
{
    // disable current entity
    m_pEntity->GetDrawable()->SetActive(false);
    m_pSphere->GetDrawable()->SetActive(false);
	m_pEntity->RemovePhysicEntity();

	if(m_pGodray != nullptr)
		m_pGodray->GetDrawable()->SetActive(false);


    // create a new one
    auto entity = twActiveWorld->CreateEntity();
    entity->m_Transform.SetPosition(m_pEntity->m_Transform.GetPosition());
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_pointsEffect");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("PointExplosion"));
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    mesh->m_Material.m_pGeometryShader.SetTexture(0, twResourceManager->GetTexture2D("t_noise"));
	mesh->m_D3DStates.m_pRasterizerState = twGraphic->GetDefaultWireframeRasterizerState();

    int speed = 0;
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &(Color[m_AmountID]));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);

    entity->SetDrawable(mesh);
    entity->SetBehaviour(new CCollectedPoint());
    twActiveWorld->AddEntity(entity);
}

int CPoints::GetPointAmount() const
{
    return Points[m_AmountID];
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
	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawInstanced;
    mesh->m_pMesh = twResourceManager->GetMesh("ms_sphere");
    mesh->m_Material.SetMaterial(twResourceManager->GetMaterial("Sun"));
    mesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("t_whitenoise"));
    mesh->m_Material.m_pVertexShader.SetInstanceData(4, &(Color[m_AmountID]), 12);
    m_pSphere->SetDrawable(mesh);

    m_pSphereMaterial = &mesh->m_Material;

    twActiveWorld->AddEntity(m_pSphere);
}

void CPoints::CreateGodray()
{
	m_pGodray = twActiveWorld->CreateEntity();
	DirectX::XMVECTOR positionGodBegin = m_pEntity->m_Transform.GetPosition();
	m_pGodray->m_Transform.SetPosition(positionGodBegin.m128_f32[0], 4.0f, positionGodBegin.m128_f32[2]);

	m_pGodray->m_Transform.SetParent(&m_pEntity->m_Transform);

	triebWerk::CMeshDrawable* pGodrayDrawable = twRenderer->CreateMeshDrawable();
	pGodrayDrawable->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	pGodrayDrawable->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	pGodrayDrawable->m_pMesh = twResourceManager->GetMesh("ms_godray");
	pGodrayDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardTransparentTexture"));
	pGodrayDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_godray_points"));
	m_pGodray->SetDrawable(pGodrayDrawable);

	twActiveWorld->AddEntity(m_pGodray);
}
