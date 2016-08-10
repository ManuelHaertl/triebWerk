#include <CEnvironmentCreator.h>
#include <CGameInfo.h>
#include <CBackground.h>
#include <CRoadBorder.h>
#include <CParticleSpawner.h>

CEnvironmentCreator::CEnvironmentCreator()
    : m_RoadAllLength(0.0f)
    , m_RoadMoveZone(-RoadMoveDistance)
    , m_RoadCount(0)
    , m_RoadEntities()
    , m_FeathersIsSpawnedTo(0.0f)
    , m_FeathersSpawnTo(SpawnDistance)
    , m_FeathersDeleteZone(-FeathersDeleteDistance)
    , m_FeathersEntities()
    , m_GridAllLength(0.0f)
    , m_GridMoveZone(-GridMoveDistance)
    , m_GridCount(0)
    , m_GridEntities()
    , m_pBGPlane(nullptr)
    , m_SnakeRotation1()
    , m_SnakeRotation2()
    , m_SnakeRotation3()
    , m_pSnake1(nullptr)
    , m_pSnake2(nullptr)
    , m_pSnake3(nullptr)
    , m_Fogs()
{
}

CEnvironmentCreator::~CEnvironmentCreator()
{
}

void CEnvironmentCreator::Start()
{
    m_RoadCount = static_cast<size_t>(SpawnDistance / RoadLength);
    m_RoadAllLength = m_RoadCount * RoadLength;

    m_GridCount = 2;
    m_GridAllLength = m_GridCount * GridLength;

    CreateRoad();
    CreateCollisionSideWalls();
    CreateBackground();
    CreateGrid();
    CreateSnakeLoops();
	CreateRoadBorder();
	CreateParticleSpawner();
    CreateFog();
	CreateBlackGround();
	CreateCurvedGrid();

    m_ObjectUpdater.Start(m_pSnake1, m_pSnake2, m_pSnake3);
}

void CEnvironmentCreator::Update(const float a_MetersFlewn)
{
    m_ObjectUpdater.Update();

	UpdateFeathers();

    m_FeathersSpawnTo += a_MetersFlewn;
    m_FeathersDeleteZone += a_MetersFlewn;


    while (m_FeathersIsSpawnedTo < m_FeathersSpawnTo)
        SpawnFeathers();
    DeleteFeathers();

    //MoveBackground();
    MoveRoad(a_MetersFlewn);
    MoveGrid(a_MetersFlewn);
    UpdateFog();
    //RotateSnakes();
}

void CEnvironmentCreator::End()
{
    // reset the values
    m_RoadAllLength = 0.0f;
    m_RoadMoveZone = -RoadMoveDistance;
    m_RoadCount = 0;

    m_FeathersSpawnTo = SpawnDistance;
    m_FeathersDeleteZone = -FeathersDeleteDistance;
    m_FeathersEntities.clear();

    m_GridAllLength = 0.0f;
    m_GridMoveZone = -GridMoveDistance;
    m_GridCount = 0;
    m_GridEntities.clear();

    m_Fogs.Clear();

    m_pBGPlane = nullptr;
    m_pSnake1 = nullptr;
    m_pSnake2 = nullptr;
    m_pSnake3 = nullptr;
}

void CEnvironmentCreator::Reset()
{
    m_RoadMoveZone = -RoadMoveDistance;

    m_FeathersIsSpawnedTo = 0.0f;
    m_FeathersSpawnTo = SpawnDistance;
    m_FeathersDeleteZone = -FeathersDeleteDistance;

    m_GridMoveZone = -GridMoveDistance;

    m_pBGPlane->m_Transform.SetPosition(0.0f, 200.0f, 500.0f);

    size_t roadEntitiesSize = m_RoadEntities.size();
    for (size_t i = 0; i < roadEntitiesSize; ++i)
    {
        twActiveWorld->RemoveEntity(m_RoadEntities.front());
        m_RoadEntities.erase(m_RoadEntities.begin());
    }

    size_t feathersEntitiesSize = m_FeathersEntities.size();
    for (size_t i = 0; i < feathersEntitiesSize; ++i)
    {
        twActiveWorld->RemoveEntity(m_FeathersEntities.front());
        m_FeathersEntities.erase(m_FeathersEntities.begin());
    }

    size_t groundEntitiesSize = m_GridEntities.size();
    for (size_t i = 0; i < groundEntitiesSize; ++i)
    {
        twActiveWorld->RemoveEntity(m_GridEntities.front());
        m_GridEntities.erase(m_GridEntities.begin());
    }

    CreateRoad();
    CreateGrid();
	CBackground* pBackground = reinterpret_cast<CBackground*>(m_pBGPlane->GetBehaviour());
	pBackground->ResetBackground();
}

triebWerk::CTransform* CEnvironmentCreator::GetBackground()
{
    return &m_pBGPlane->m_Transform;
}

void CEnvironmentCreator::SpawnFeathers()
{
    int randomNumber = twRandom::GetNumber(0, 99);
    if (randomNumber < FeatherSpawnProbability)
    {
        auto entity = twActiveWorld->CreateEntity();
        entity->m_Transform.SetPosition(0.0f, 0.0f, m_FeathersIsSpawnedTo);
        entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

        triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_feathers_01");
        mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Feathers"));
        mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("feather_diff_01"));
		float randomStart = twRandom::GetNumber(0.0f, 30.0f);

		mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &randomStart);

        entity->SetDrawable(mesh);

        twActiveWorld->AddEntity(entity);
        m_FeathersEntities.push_back(entity);
    }

    m_FeathersIsSpawnedTo += FeathersLength;
}

void CEnvironmentCreator::DeleteFeathers()
{
    for (;;)
    {
        if (m_FeathersEntities.size() == 0)
            break;

        auto entity = m_FeathersEntities.front();
        if (entity->m_Transform.GetPosition().m128_f32[2] < m_FeathersDeleteZone)
        {
            twActiveWorld->RemoveEntity(entity);
            m_FeathersEntities.erase(m_FeathersEntities.begin());
        }
        else
        {
            break;
        }
    }
}

void CEnvironmentCreator::CreateRoad()
{
    m_RoadEntities.clear();

    float position = 0.0f;
    for (size_t i = 0; i < m_RoadCount; ++i)
    {
        auto entity = twActiveWorld->CreateEntity();
        entity->m_Transform.SetPosition(0.0f, 0.0f, position);
        entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

        triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_course_01");
        mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
        mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_course_diff"));
        entity->SetDrawable(mesh);

        twActiveWorld->AddEntity(entity);
        m_RoadEntities.push_back(entity);

        position += RoadLength;
    }
}

void CEnvironmentCreator::CreateCollisionSideWalls()
{
    const float roadWidth = 48.0f;
    const float scaleX = 1000.0f;
    const float scaleY = 1000.0f;
    const float scaleZ = 100000000.0f;

    // left side wall
    auto wallLeft = twActiveWorld->CreateEntity();
    wallLeft->m_Transform.SetPosition((scaleX / 2.0f + roadWidth / 2.0f) * -1, 0.0f, 0.0f);
    wallLeft->m_Transform.SetScale(scaleX, scaleY, scaleZ);
    wallLeft->m_ID.SetName("SideLeft");

    auto physicEntityLeft = twActivePhysic->CreatePhysicEntity();
    auto collLeft = twActivePhysic->CreateAABBCollider();
    collLeft->SetSize(1.0f, 1.0f, 1.0f);
    collLeft->m_CheckCollision = false;
    physicEntityLeft->AddCollider(collLeft);
    wallLeft->SetPhysicEntity(physicEntityLeft);

    twActiveWorld->AddEntity(wallLeft);

    // right side wall
    auto wallRight = twActiveWorld->CreateEntity();
    wallRight->m_Transform.SetPosition(scaleX / 2.0f + roadWidth / 2.0f, 0.0f, 0.0f);
    wallRight->m_Transform.SetScale(scaleX, scaleY, scaleZ);
    wallRight->m_ID.SetName("SideRight");

    auto physicEntityRight = twActivePhysic->CreatePhysicEntity();
    auto collRight = twActivePhysic->CreateAABBCollider();
    collRight->SetSize(1.0f, 1.0f, 1.0f);
    collRight->m_CheckCollision = false;
    physicEntityRight->AddCollider(collRight);
    wallRight->SetPhysicEntity(physicEntityRight);

    twActiveWorld->AddEntity(wallRight);
}

void CEnvironmentCreator::CreateGrid()
{
   m_GridEntities.clear();
   //
   //float position = 0.0f;
   //for (size_t i = 0; i < m_GridCount; ++i)
   //{
   //    auto entity = twActiveWorld->CreateEntity();
   //    entity->m_Transform.SetPosition(0.0f, -10.0f, position);
   //    entity->m_Transform.SetScale(50.0f, 1.0f, 50.0f);
   //
   //    triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
   //    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_grid");
   //    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	//   mesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
   //    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("WireframeGrid"));
   //    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f));
   //    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
   //    entity->SetDrawable(mesh);
   //
   //    twActiveWorld->AddEntity(entity);
   //    m_GridEntities.push_back(entity);
   //
   //    position += GridLength;
   //}
}  //

void CEnvironmentCreator::CreateBlackGround()
{
	m_pBlackGround = twActiveWorld->CreateEntity();
	m_pBGPlane->m_Transform.AddChild(&m_pBlackGround->m_Transform);
	m_pBlackGround->m_Transform.SetPosition(0.0f, -40.0f, 0.0f);
	m_pBlackGround->m_Transform.SetScale(1800.0f, 1800.0f, 1800.0f);
	
	
	auto planeMesh = twRenderer->CreateMeshDrawable();
	planeMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	planeMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
	planeMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pBlackGround->SetDrawable(planeMesh);
	
	twActiveWorld->AddEntity(m_pBlackGround);
}

void CEnvironmentCreator::CreateBackground()
{
	// Plane
	const float planeWidth = 5000.0f;
	const float planeApectRatio = 0.519916f;

	m_pBGPlane = twActiveWorld->CreateEntity();
	m_pBGPlane->m_Transform.SetPosition(0.0f, 200.0f, BGPlaneDistanceZ);
	m_pBGPlane->m_Transform.SetScale(planeWidth, 0.0f, planeWidth * planeApectRatio);
	m_pBGPlane->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

	auto planeMesh = twRenderer->CreateMeshDrawable();
	planeMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	planeMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
	planeMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_background"));
	m_pBGPlane->SetDrawable(planeMesh);
	planeMesh->SetActive(false);

	//auto physicEntity = twActivePhysic->CreatePhysicEntity();
	//auto body = twActivePhysic->CreateBody();
	//body->m_GravityFactor = 0.0f;
	//body->m_Velocity.m128_f32[2] = CGameInfo::Instance().m_FlyBoostSpeed + CGameInfo::Instance().m_FlyDifficultySpeed + CGameInfo::Instance().m_FlyStandardSpeed;
	//physicEntity->SetBody(body);
	//m_pBGPlane->SetPhysicEntity(physicEntity);

	m_pBGPlane->SetBehaviour(new CBackground);

	twActiveWorld->AddEntity(m_pBGPlane);


	auto newbackground = twActiveWorld->CreateEntity();
	m_pBGPlane->m_Transform.AddChild(&newbackground->m_Transform);
	newbackground->m_Transform.SetPosition(0.0f, 600.0f, 1400.0f);
	newbackground->m_Transform.SetScale(planeWidth, 0.0f, planeWidth * planeApectRatio);
	newbackground->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

	auto planeMesh1 = twRenderer->CreateMeshDrawable();
	planeMesh1->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	planeMesh1->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
	planeMesh1->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_background"));
	newbackground->SetDrawable(planeMesh1);

	twActiveWorld->AddEntity(newbackground);
}

void CEnvironmentCreator::CreateSnakeLoops()
{
    // snake 1
    m_pSnake1 = twActiveWorld->CreateEntity();
    m_pBGPlane->m_Transform.AddChild(&m_pSnake1->m_Transform);
    m_pSnake1->m_Transform.SetPosition(-100.0f, -15.0f, 90.0f);
    m_pSnake1->m_Transform.SetScale(0.6f, 0.6f, 0.6f);
    m_SnakeRotation1.m128_f32[0] = 0.0f;
    m_SnakeRotation1.m128_f32[1] = 340.0f;
    m_SnakeRotation1.m128_f32[2] = 0.0f;
    m_pSnake1->m_Transform.SetRotationDegrees(m_SnakeRotation1);

    auto mesh1 = twRenderer->CreateMeshDrawable();
    mesh1->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_snakeloop_01");
    mesh1->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
    mesh1->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_snakeloop_diff"));
    m_pSnake1->SetDrawable(mesh1);

    twActiveWorld->AddEntity(m_pSnake1);

    // snake 2
    m_pSnake2 = twActiveWorld->CreateEntity();
    m_pBGPlane->m_Transform.AddChild(&m_pSnake2->m_Transform);
    m_pSnake2->m_Transform.SetPosition(120.0f, -20.0f, 170.0f);
    m_pSnake2->m_Transform.SetScale(0.8f, 0.8f, 0.8f);
    m_SnakeRotation2.m128_f32[0] = 0.0f;
    m_SnakeRotation2.m128_f32[1] = 90.0f;
    m_SnakeRotation2.m128_f32[2] = 350.0f;
    m_pSnake2->m_Transform.SetRotationDegrees(m_SnakeRotation2);

    auto mesh2 = twRenderer->CreateMeshDrawable();
    mesh2->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_snakeloop_01");
    mesh2->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
    mesh2->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_snakeloop_diff"));
    m_pSnake2->SetDrawable(mesh2);

    twActiveWorld->AddEntity(m_pSnake2);

    // snake 3
    m_pSnake3 = twActiveWorld->CreateEntity();
    m_pBGPlane->m_Transform.AddChild(&m_pSnake3->m_Transform);
    m_pSnake3->m_Transform.SetPosition(370.0f, 0.0f, 200.0f);
    m_pSnake3->m_Transform.SetScale(1.2f, 1.2f, 1.2f);
    m_SnakeRotation3.m128_f32[0] = 0.0f;
    m_SnakeRotation3.m128_f32[1] = 90.0f;
    m_SnakeRotation3.m128_f32[2] = 350.0f;
    m_pSnake3->m_Transform.SetRotationDegrees(m_SnakeRotation3);

    auto mesh3 = twRenderer->CreateMeshDrawable();
    mesh3->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_snakeloop_01");
    mesh3->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
    mesh3->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_snakeloop_diff"));
    m_pSnake3->SetDrawable(mesh3);

    twActiveWorld->AddEntity(m_pSnake3);
}

void CEnvironmentCreator::CreateCurvedGrid()
{
	m_pCurvedGrid = twActiveWorld->CreateEntity();
	m_pBGPlane->m_Transform.AddChild(&m_pCurvedGrid->m_Transform);
	m_pCurvedGrid->m_Transform.SetPosition(0.0f, SphereY, 550.0f);
	m_pCurvedGrid->m_Transform.SetScale(1.5f, 1.5f, 1.5f);
	
	triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_worldspere");
	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	//mesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("WorldSphere"));
	mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_worldsphere_mesh"));
	mesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("T_worldsphere_alpha"));
	m_pCurvedGrid->SetDrawable(mesh);
	
	twActiveWorld->AddEntity(m_pCurvedGrid);
}

void CEnvironmentCreator::CreateFog()
{
    const float size = 25.0f;
    
    for (size_t i = 0; i < FogCount; ++i)
    {
        auto fog = twActiveWorld->CreateEntity();
        m_pBGPlane->m_Transform.AddChild(&fog->m_Transform);
        fog->m_Transform.SetPosition(-50.0f, 0.0f, 50.0f);
        fog->m_Transform.SetScale(size, 1.0f, size);
        fog->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

		std::cout << "Fog" << std::endl;

        auto fogMesh = twRenderer->CreateMeshDrawable();
        fogMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
        fogMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
        fogMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Fog"));
        fogMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_fog_01"));
        fogMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
        fog->SetDrawable(fogMesh);

        twActiveWorld->AddEntity(fog);
        m_Fogs.Add(fog);
        m_ObjectUpdater.m_Fog.Add(fog);
    }
}

void CEnvironmentCreator::CreateRoadBorder()
{
	m_pRoadBorder = twActiveWorld->CreateEntity();
	m_pBGPlane->m_Transform.AddChild(&m_pRoadBorder->m_Transform);
	m_pRoadBorder->m_Transform.SetPosition(-24.9f, 5.0f, 0.0f);
	m_pRoadBorder->m_Transform.SetRotationDegrees(90.0f, 00.0f, -90.0f);
	m_pRoadBorder->m_Transform.SetScale(10.0f, 10.0f, 10.0f);

	auto borderMesh = twRenderer->CreateMeshDrawable();
	borderMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	borderMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	borderMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	borderMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("TransparentScrolling"));
	borderMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_border_emissve_grid"));
	borderMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("T_grid_cutout_circle"));
	float defaultValue = 0.0f;
	borderMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &defaultValue);
	borderMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &defaultValue);
	m_pRoadBorder->SetDrawable(borderMesh);

	m_pRoadBorder->SetBehaviour(new CRoadBorder());

	twActiveWorld->AddEntity(m_pRoadBorder);
}

void CEnvironmentCreator::CreateParticleSpawner()
{
	m_pParticleSpawner = twActiveWorld->CreateEntity();
	m_pBGPlane->m_Transform.AddChild(&m_pParticleSpawner->m_Transform);
	m_pParticleSpawner->m_Transform.SetPosition(0.0f, 25.0f, 400.0f);

	m_pParticleSpawner->SetBehaviour(new CParticleSpawner());

	twActiveWorld->AddEntity(m_pParticleSpawner);
}

void CEnvironmentCreator::MoveBackground()
{
    auto position = m_pBGPlane->m_Transform.GetPosition();
    position.m128_f32[2] = CGameInfo::Instance().m_PlayerPositionZ + BGPlaneDistanceZ;
    m_pBGPlane->m_Transform.SetPosition(position);
}

void CEnvironmentCreator::MoveRoad(const float a_MetersFlewn)
{
    // Road
    m_RoadMoveZone += a_MetersFlewn;

    triebWerk::CEntity* first = m_RoadEntities.front();
    DirectX::XMVECTOR pos = first->m_Transform.GetPosition();
    if (pos.m128_f32[2] < m_RoadMoveZone)
    {
        pos.m128_f32[2] += m_RoadAllLength;
        first->m_Transform.SetPosition(pos);

        m_RoadEntities.erase(m_RoadEntities.begin());
        m_RoadEntities.push_back(first);
    }
}

void CEnvironmentCreator::MoveGrid(const float a_MetersFlewn)
{
    // Grid
    //m_GridMoveZone += a_MetersFlewn;
	//
    //triebWerk::CEntity* first = m_GridEntities.front();
    //DirectX::XMVECTOR pos = first->m_Transform.GetPosition();
    //if (pos.m128_f32[2] < m_GridMoveZone)
    //{
    //    pos.m128_f32[2] += m_GridAllLength;
    //    first->m_Transform.SetPosition(pos);
	//
    //    m_GridEntities.erase(m_GridEntities.begin());
    //    m_GridEntities.push_back(first);
    //}
}

void CEnvironmentCreator::UpdateFog()
{
    float time = twTime->GetTimeSinceStartup();

    size_t size = m_Fogs.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        ((triebWerk::CMeshDrawable*)(m_Fogs[i]->GetDrawable()))->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &time);
    }
}

void CEnvironmentCreator::UpdateFeathers()
{
	float time = twTime->GetTimeSinceStartup();
	for (auto feather : m_FeathersEntities)
	{
		reinterpret_cast<triebWerk::CMeshDrawable*>(feather->GetDrawable())->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &time);
	}
}

void CEnvironmentCreator::RotateSnakes()
{
    float dt = twTime->GetDeltaTime();
    m_SnakeRotation1.m128_f32[0] += dt * SnakeRotateSpeed1;
    m_SnakeRotation2.m128_f32[0] += dt * SnakeRotateSpeed2;
    m_SnakeRotation3.m128_f32[0] += dt * SnakeRotateSpeed3;
    m_pSnake1->m_Transform.SetRotationDegrees(m_SnakeRotation1);
    m_pSnake2->m_Transform.SetRotationDegrees(m_SnakeRotation2);
    m_pSnake3->m_Transform.SetRotationDegrees(m_SnakeRotation3);
}
