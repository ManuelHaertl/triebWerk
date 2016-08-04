#include <CPatternTileCreator.h>

#include <CCheckpoint.h>
#include <CPatternManager.h>
#include <CMovingObstacle.h>
#include <CPoints.h>
#include <CGameInfo.h>

CPatternTileCreator::CPatternTileCreator()
    : m_Entities()
    , m_Tile()
    , m_PatternSpawnBegin(0.0f)
{
    m_pCheckPoint = twResourceManager->GetMesh("ms_checkpoint_prisma");
    m_pPoints = twResourceManager->GetMesh("ms_points");
    m_pBlock1x1 = twResourceManager->GetMesh("ms_cube");
    m_pBlock2x2 = twResourceManager->GetMesh("ms_cube");

    m_pObstacle05[0] = twResourceManager->GetMesh("ms_obs_05x05x08_base");
    m_pObstacle05[1] = twResourceManager->GetMesh("ms_obs_05x05x12_base");
    m_pObstacle05Dekos[0][0] = twResourceManager->GetMesh("ms_obs_05x05x08_deko_01");
    m_pObstacle05Dekos[0][1] = twResourceManager->GetMesh("ms_obs_05x05x08_deko_02");
    m_pObstacle05Dekos[0][2] = twResourceManager->GetMesh("ms_obs_05x05x08_deko_03");
    m_pObstacle05Dekos[1][0] = twResourceManager->GetMesh("ms_obs_05x05x12_deko_01");
    m_pObstacle05Dekos[1][1] = twResourceManager->GetMesh("ms_obs_05x05x12_deko_02");
    m_pObstacle05Dekos[1][2] = twResourceManager->GetMesh("ms_obs_05x05x12_deko_03");

    m_pObstacle10[0] = twResourceManager->GetMesh("ms_obs_05x10x08_base");
    m_pObstacle10[1] = twResourceManager->GetMesh("ms_obs_05x10x12_base");
    m_pObstacle10Dekos[0][0] = twResourceManager->GetMesh("ms_obs_05x10x08_deko_01");
    m_pObstacle10Dekos[0][1] = twResourceManager->GetMesh("ms_obs_05x10x08_deko_02");
    m_pObstacle10Dekos[0][2] = twResourceManager->GetMesh("ms_obs_05x10x08_deko_03");
    m_pObstacle10Dekos[1][0] = twResourceManager->GetMesh("ms_obs_05x10x12_deko_01");
    m_pObstacle10Dekos[1][1] = twResourceManager->GetMesh("ms_obs_05x10x12_deko_02");
    m_pObstacle10Dekos[1][2] = twResourceManager->GetMesh("ms_obs_05x10x12_deko_03");

    m_pObstacle20[0] = twResourceManager->GetMesh("ms_obs_05x20x08_base");
    m_pObstacle20[1] = twResourceManager->GetMesh("ms_obs_05x20x12_base");
    m_pObstacle20Dekos[0][0] = twResourceManager->GetMesh("ms_obs_05x20x08_deko_01");
    m_pObstacle20Dekos[0][1] = twResourceManager->GetMesh("ms_obs_05x20x08_deko_02");
    m_pObstacle20Dekos[0][2] = twResourceManager->GetMesh("ms_obs_05x20x08_deko_03");
    m_pObstacle20Dekos[1][0] = twResourceManager->GetMesh("ms_obs_05x20x12_deko_01");
    m_pObstacle20Dekos[1][1] = twResourceManager->GetMesh("ms_obs_05x20x12_deko_02");
    m_pObstacle20Dekos[1][2] = twResourceManager->GetMesh("ms_obs_05x20x12_deko_03");

    m_pObstacle30[0] = twResourceManager->GetMesh("ms_obs_05x30x08_base");
    m_pObstacle30[1] = twResourceManager->GetMesh("ms_obs_05x30x12_base");
    m_pObstacle30Dekos[0][0] = twResourceManager->GetMesh("ms_obs_05x30x08_deko_01");
    m_pObstacle30Dekos[0][1] = twResourceManager->GetMesh("ms_obs_05x30x08_deko_02");
    m_pObstacle30Dekos[0][2] = twResourceManager->GetMesh("ms_obs_05x30x08_deko_03");
    m_pObstacle30Dekos[1][0] = twResourceManager->GetMesh("ms_obs_05x30x12_deko_01");
    m_pObstacle30Dekos[1][1] = twResourceManager->GetMesh("ms_obs_05x30x12_deko_02");
    m_pObstacle30Dekos[1][2] = twResourceManager->GetMesh("ms_obs_05x30x12_deko_03");

    m_pShadow05 = twResourceManager->GetMesh("ms_shadow_05x05");
    m_pShadow10 = twResourceManager->GetMesh("ms_shadow_05x10");
    m_pShadow20 = twResourceManager->GetMesh("ms_shadow_05x20");
    m_pShadow30 = twResourceManager->GetMesh("ms_shadow_05x30");

    m_pMoving05Up = twResourceManager->GetMesh("ms_obs_05x05x07_movable_up");
    m_pMoving05Down = twResourceManager->GetMesh("ms_obs_05x05x07_movable_down");
    m_pMoving05Left = twResourceManager->GetMesh("ms_obs_05x05x07_movable_left");
    m_pMoving05Right = twResourceManager->GetMesh("ms_obs_05x05x07_movable_right");
    m_pMoving05None = twResourceManager->GetMesh("ms_obs_05x05x07_movable_air");
    m_pMoving05To = twResourceManager->GetMesh("ms_obs_05x05x07_movable_air");
    m_pMoving05Back = twResourceManager->GetMesh("ms_obs_05x05x07_movable_forward");

    m_pMoving10Up = twResourceManager->GetMesh("ms_obs_05x10x07_movable_up");
    m_pMoving10Down = twResourceManager->GetMesh("ms_obs_05x10x07_movable_down");
    m_pMoving10Left = twResourceManager->GetMesh("ms_obs_05x10x07_movable_left");
    m_pMoving10Right = twResourceManager->GetMesh("ms_obs_05x10x07_movable_right");
    m_pMoving10None = twResourceManager->GetMesh("ms_obs_05x10x07_movable_air");
    m_pMoving10To = twResourceManager->GetMesh("ms_obs_05x10x07_movable_air");
    m_pMoving10Back = twResourceManager->GetMesh("ms_obs_05x10x07_movable_forward");

    m_pTextureObstacle[0][0] = twResourceManager->GetTexture2D("T_obs_01_blend1");
    m_pTextureObstacle[0][1] = twResourceManager->GetTexture2D("T_obs_01_blend2");
    m_pTextureObstacle[0][2] = twResourceManager->GetTexture2D("T_obs_01_blend3");
    m_pTextureObstacle[1][0] = twResourceManager->GetTexture2D("T_obs_02_blend1");
    m_pTextureObstacle[1][1] = twResourceManager->GetTexture2D("T_obs_02_blend2");
    m_pTextureObstacle[1][2] = twResourceManager->GetTexture2D("T_obs_02_blend3");
    m_pTextureObstacle[2][0] = twResourceManager->GetTexture2D("T_obs_03_blend1");
    m_pTextureObstacle[2][1] = twResourceManager->GetTexture2D("T_obs_03_blend2");
    m_pTextureObstacle[2][2] = twResourceManager->GetTexture2D("T_obs_03_blend3");

	m_pTextureEmissive[0] = twResourceManager->GetTexture2D("t_obs_all_emissive_blend1");
	m_pTextureEmissive[1] = twResourceManager->GetTexture2D("t_obs_all_emissive_blend2");
	m_pTextureEmissive[2] = twResourceManager->GetTexture2D("t_obs_all_emissive_blend3");
	m_pTextureEmissiveMoveable = twResourceManager->GetTexture2D("t_obs_movable_emissive");
	m_pTextureNoise = twResourceManager->GetTexture2D("t_noise");
	m_pTextureColorNoise = twResourceManager->GetTexture2D("t_noisecolor");

    m_pTexturePoints = twResourceManager->GetTexture2D("T_points_diff");
    m_pTextureShadow05 = twResourceManager->GetTexture2D("t_shadow_05x05");
    m_pTextureShadow10 = twResourceManager->GetTexture2D("t_shadow_05x10");
    m_pTextureShadow20 = twResourceManager->GetTexture2D("t_shadow_05x20");
    m_pTextureShadow30 = twResourceManager->GetTexture2D("t_shadow_05x30");

    m_pMaterialStandardColor = twResourceManager->GetMaterial("StandardColor");
    m_pMaterialStandardTexture = twResourceManager->GetMaterial("StandardTexture");
    m_pMaterialStandardTransparentTexture = twResourceManager->GetMaterial("StandardTransparentTexture");
	m_pMaterialObstacle = twResourceManager->GetMaterial("Wall");
    m_pMaterialWireframe = twResourceManager->GetMaterial("Wireframe");
}

CPatternTileCreator::~CPatternTileCreator()
{
}

void CPatternTileCreator::CreateEntity(const SPatternTile& a_rTile, const float a_PatternSpawnBegin)
{
    m_Tile = a_rTile;
    m_PatternSpawnBegin = a_PatternSpawnBegin;

    m_Entities.clear();

    switch (a_rTile.m_Type)
    {
    case ETileType::Checkpoint:
        CreateCheckpoint();
        break;
    case ETileType::Points1:
        CreatePoints(0);
        break;
    case ETileType::Points2:
        CreatePoints(1);
        break;
    case ETileType::Points3:
        CreatePoints(2);
        break;
    case ETileType::Shield:
        CreateShield();
        break;
    case ETileType::Block1x1:
        CreateBlock1x1();
        break;
    case ETileType::Block2x2:
        CreateBlock2x2();
        break;
    case ETileType::Model05x05:
        CreateModel05x05(false);
        break;
    case ETileType::Model05x05Flipped:
        CreateModel05x05(true);
        break;
    case ETileType::Model05x10:
        CreateModel05x10(false);
        break;
    case ETileType::Model05x10Flipped:
        CreateModel05x10(true);
        break;
    case ETileType::Model05x20:
        CreateModel05x20(false);
        break;
    case ETileType::Model05x20Flipped:
        CreateModel05x20(true);
        break;
    case ETileType::Model05x30:
        CreateModel05x30(false);
        break;
    case ETileType::Model05x30Flipped:
        CreateModel05x30(true);
        break;
    case ETileType::Moving05x05:
        CreateMoving05x05();
        break;
    case ETileType::Moving05x10:
        CreateMoving05x10(false);
        break;
    case ETileType::Moving05x10Flipped:
        CreateMoving05x10(true);
        break;
    }
}

void CPatternTileCreator::CreateCheckpoint()
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // ID
    entity->m_ID.SetName("Checkpoint");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.5f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetScale(1.3f, 1.3f, 1.3f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pCheckPoint;
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	mesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	mesh->m_D3DStates.m_pRasterizerState = twGraphic->GetDefaultCullNoneRasterizerState();
    mesh->m_Material.SetMaterial(m_pMaterialWireframe);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.0f, 1.0f, 1.0f));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
	auto t = collider->GetMax();
	auto e = collider->GetMin();
	t.m128_f32[1] = 5.0f;
	e.m128_f32[1] = -5.0f;
	collider->SetMax(t);
	collider->SetMin(e);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    // Behaviour
    entity->SetBehaviour(new CCheckpoint());

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreatePoints(const size_t a_Amount)
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // ID
    entity->m_ID.SetName("Points");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 1.85f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetScale(2.0f, 2.0f, 2.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pPoints;
	mesh->m_D3DStates.m_pRasterizerState = twGraphic->GetDefaultWireframeRasterizerState();
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    mesh->m_Material.SetMaterial(m_pMaterialStandardColor);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(0.8f, 0.8f, 0.8f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    // Behaviour
    entity->SetBehaviour(new CPoints(a_Amount));

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateShield()
{
    
}

void CPatternTileCreator::CreateBlock1x1()
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // ID
    entity->m_Tag.AddTag("Death");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 5.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetScale(1.0f, 10.0f, 1.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pBlock1x1;
    mesh->m_Material.SetMaterial(m_pMaterialStandardColor);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateBlock2x2()
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // ID
    entity->m_Tag.AddTag("Death");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 5.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetScale(2.0f, 10.0f, 2.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pBlock2x2;
    mesh->m_Material.SetMaterial(m_pMaterialStandardColor);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateModel05x05(const bool a_Rotated)
{
    const size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    const size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);
    const size_t texture = twRandom::GetNumber(0, MaxObstacleTextures - 1);
	
	//Building effect 
	float distanceToPlayer = (m_PatternSpawnBegin + m_Tile.m_Y) - CGameInfo::Instance().m_PlayerPositionZ;
	float startDistanceBuildValue = 0.0f;
	
	if (distanceToPlayer < CPatternManager::StartBuildDistance)
		startDistanceBuildValue = distanceToPlayer;
	else if (distanceToPlayer >= CPatternManager::StartBuildDistance)
		startDistanceBuildValue = CPatternManager::StartBuildDistance;

	float startBuild = (startDistanceBuildValue - CPatternManager::EndBuildDistance) / CPatternManager::BuildStrength;

	float rand =GetRandomSign();;

	float textureValueFull = 1.0f, textureValueNone = 0.0f;

    auto entity1 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity1);

    // ID
    entity1->m_Tag.AddTag("Death");
    entity1->m_Tag.AddTag("WallEffect");

    // Transform
    entity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    mesh->m_pMesh = m_pObstacle05[height];
    mesh->m_Material.SetMaterial(m_pMaterialObstacle);
	mesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	mesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
    mesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
    mesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	mesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	mesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	mesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(5.0f, 8.0f, 5.0f);
    else
        collider->SetSize(5.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity1->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity1);

    // --------- Deko ---------

    auto entity2 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity2);

    // ID
    entity2->m_Tag.AddTag("WallEffect");

    // Transform
    entity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto dekoMesh = twRenderer->CreateMeshDrawable();
    dekoMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    dekoMesh->m_pMesh = m_pObstacle05Dekos[height][deko];
    dekoMesh->m_Material.SetMaterial(m_pMaterialObstacle);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity2->SetDrawable(dekoMesh);

    twActiveWorld->AddEntity(entity2);

    CreateShadow05(a_Rotated);
}

void CPatternTileCreator::CreateModel05x10(const bool a_Rotated)
{
    const size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    const size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);
    const size_t texture = twRandom::GetNumber(0, MaxObstacleTextures - 1);
    float textureValueFull = 1.0f, textureValueNone = 0.0f;

	//Building effect 
	float distanceToPlayer = (m_PatternSpawnBegin + m_Tile.m_Y) - CGameInfo::Instance().m_PlayerPositionZ;
	float startDistanceBuildValue = 0.0f;

	if (distanceToPlayer < CPatternManager::StartBuildDistance)
		startDistanceBuildValue = distanceToPlayer;
	else if (distanceToPlayer >= CPatternManager::StartBuildDistance)
		startDistanceBuildValue = CPatternManager::StartBuildDistance;

	float startBuild = (startDistanceBuildValue - CPatternManager::EndBuildDistance) / CPatternManager::BuildStrength;

	float rand =GetRandomSign();;

    auto entity1 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity1);

    // ID
    entity1->m_Tag.AddTag("Death");
    entity1->m_Tag.AddTag("WallEffect");

    // Transform
    entity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    mesh->m_pMesh = m_pObstacle10[height];
	mesh->m_Material.SetMaterial(m_pMaterialObstacle);
	mesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	mesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	mesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	mesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	mesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	mesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	mesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(10.0f, 8.0f, 5.0f);
    else 
        collider->SetSize(5.0f, 8.0f, 10.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity1->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity1);

    // --------- Deko ---------

    auto entity2 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity2);

    // ID
    entity2->m_Tag.AddTag("WallEffect");

    // Transform
    entity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto dekoMesh = twRenderer->CreateMeshDrawable();
    dekoMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    dekoMesh->m_pMesh = m_pObstacle10Dekos[height][deko];
	dekoMesh->m_Material.SetMaterial(m_pMaterialObstacle);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity2->SetDrawable(dekoMesh);

    CreateShadow10(a_Rotated);

    twActiveWorld->AddEntity(entity2);
}

void CPatternTileCreator::CreateModel05x20(const bool a_Rotated)
{
    const size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    const size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);
    const size_t texture = twRandom::GetNumber(0, MaxObstacleTextures - 1);
    float textureValueFull = 1.0f, textureValueNone = 0.0f;

	//Building effect 
	float distanceToPlayer = (m_PatternSpawnBegin + m_Tile.m_Y) - CGameInfo::Instance().m_PlayerPositionZ;
	float startDistanceBuildValue = 0.0f;

	if (distanceToPlayer < CPatternManager::StartBuildDistance)
		startDistanceBuildValue = distanceToPlayer;
	else if (distanceToPlayer >= CPatternManager::StartBuildDistance)
		startDistanceBuildValue = CPatternManager::StartBuildDistance;

	float startBuild = (startDistanceBuildValue - CPatternManager::EndBuildDistance) / CPatternManager::BuildStrength;

    auto entity1 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity1);

	float rand =GetRandomSign();;

    // ID
    entity1->m_Tag.AddTag("Death");
    entity1->m_Tag.AddTag("WallEffect");

    // Transform
    entity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    mesh->m_pMesh = m_pObstacle20[height];
	mesh->m_Material.SetMaterial(m_pMaterialObstacle);
	mesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	mesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	mesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	mesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	mesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	mesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	mesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(20.0f, 8.0f, 5.0f);
    else
        collider->SetSize(5.0f, 8.0f, 20.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity1->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity1);

    // --------- Deko ---------

    auto entity2 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity2);

    // ID
    entity2->m_Tag.AddTag("WallEffect");

    // Transform
    entity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto dekoMesh = twRenderer->CreateMeshDrawable();
    dekoMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    dekoMesh->m_pMesh = m_pObstacle20Dekos[height][deko];
	dekoMesh->m_Material.SetMaterial(m_pMaterialObstacle);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity2->SetDrawable(dekoMesh);

    CreateShadow20(a_Rotated);

    twActiveWorld->AddEntity(entity2);
}

void CPatternTileCreator::CreateModel05x30(const bool a_Rotated)
{
    const size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    const size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);
    const size_t texture = twRandom::GetNumber(0, MaxObstacleTextures - 1);
    float textureValueFull = 1.0f, textureValueNone = 0.0f;

	//Building effect 
	float distanceToPlayer = (m_PatternSpawnBegin + m_Tile.m_Y) - CGameInfo::Instance().m_PlayerPositionZ;
	float startDistanceBuildValue = 0.0f;

	if (distanceToPlayer < CPatternManager::StartBuildDistance)
		startDistanceBuildValue = distanceToPlayer;
	else if (distanceToPlayer >= CPatternManager::StartBuildDistance)
		startDistanceBuildValue = CPatternManager::StartBuildDistance;

	float startBuild = (startDistanceBuildValue - CPatternManager::EndBuildDistance) / CPatternManager::BuildStrength;

	float rand =GetRandomSign();;

    auto entity1 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity1);

    // ID
    entity1->m_Tag.AddTag("Death");
    entity1->m_Tag.AddTag("WallEffect");

    // Transform
    entity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    mesh->m_pMesh = m_pObstacle30[height];
	mesh->m_Material.SetMaterial(m_pMaterialObstacle);
	mesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	mesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	mesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	mesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	mesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	mesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	mesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(30.0f, 8.0f, 5.0f);
    else
        collider->SetSize(5.0f, 8.0f, 30.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity1->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity1);

    // --------- Deko ---------

    auto entity2 = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity2);

    // ID
    entity2->m_Tag.AddTag("WallEffect");

    // Transform
    entity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto dekoMesh = twRenderer->CreateMeshDrawable();
    dekoMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    dekoMesh->m_pMesh = m_pObstacle30Dekos[height][deko];
	dekoMesh->m_Material.SetMaterial(m_pMaterialObstacle);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	dekoMesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceColor);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	dekoMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissive[0]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissive[1]);
	dekoMesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissive[2]);
    entity2->SetDrawable(dekoMesh);

    CreateShadow30(a_Rotated);

    twActiveWorld->AddEntity(entity2);
}

void CPatternTileCreator::CreateShadow05(const bool a_Rotated)
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.01f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow05;
	shadowMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	shadowMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow05);
    entity->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateShadow10(const bool a_Rotated)
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.01f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow10;
	shadowMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	shadowMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow10);
    entity->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateShadow20(const bool a_Rotated)
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.01f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow20;
	shadowMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	shadowMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow20);
    entity->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateShadow30(const bool a_Rotated)
{
    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.01f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow30;
	shadowMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	shadowMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow30);
    entity->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateMoving05x05()
{
    const size_t texture = twRandom::GetNumber(0, MaxObstacleTextures - 1);
    float textureValueFull = 1.0f, textureValueNone = 0.0f;

	float rand =GetRandomSign();;

	//Building effect 
	float distanceToPlayer = (m_PatternSpawnBegin + m_Tile.m_Y) - CGameInfo::Instance().m_PlayerPositionZ;
	float startDistanceBuildValue = 0.0f;

	if (distanceToPlayer < CPatternManager::StartBuildDistance)
		startDistanceBuildValue = distanceToPlayer;
	else if (distanceToPlayer >= CPatternManager::StartBuildDistance)
		startDistanceBuildValue = CPatternManager::StartBuildDistance;

	float startBuild = (startDistanceBuildValue - CPatternManager::EndBuildDistance) / CPatternManager::BuildStrength;

    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // ID
    entity->m_Tag.AddTag("Death");
    entity->m_Tag.AddTag("WallEffect");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, m_Tile.m_PosYStart, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;

    switch (m_Tile.m_Moving)
    {
    case SPatternTile::EMovingDirection::Up:
        mesh->m_pMesh = m_pMoving05Up;
        break;
    case SPatternTile::EMovingDirection::Down:
        mesh->m_pMesh = m_pMoving05Down;
        break;
    case SPatternTile::EMovingDirection::Left:
        mesh->m_pMesh = m_pMoving05Left;
        break;
    case SPatternTile::EMovingDirection::Right:
        mesh->m_pMesh = m_pMoving05Right;
        break;
    case SPatternTile::EMovingDirection::Air:
        mesh->m_pMesh = m_pMoving05None;
        break;
    case SPatternTile::EMovingDirection::To:
        mesh->m_pMesh = m_pMoving05To;
        break;
    case SPatternTile::EMovingDirection::Back:
        mesh->m_pMesh = m_pMoving05Back;
        break;
    }
	mesh->m_Material.SetMaterial(m_pMaterialObstacle);
	mesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	mesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceEmissiveColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	mesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	mesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	mesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissiveMoveable);
	mesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissiveMoveable);
	mesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissiveMoveable);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetMin(DirectX::XMVectorSet(-2.5f, 0.0f, -2.5f, 0.0f));
    collider->SetMax(DirectX::XMVectorSet(2.5f, 7.0f, 2.5f, 0.0f));
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    // Shadow
    CreateShadow05(false);

    // Behaviour
    DirectX::XMVECTOR start = DirectX::XMVectorSet(m_Tile.m_X, m_Tile.m_PosYStart, m_PatternSpawnBegin + m_Tile.m_Y, 0.0f);
    DirectX::XMVECTOR end = DirectX::XMVectorSet(m_Tile.m_PosXEnd, m_Tile.m_PosYEnd, m_PatternSpawnBegin + m_Tile.m_Y + m_Tile.m_PosZEnd, 0.0f);
    entity->SetBehaviour(new CMovingObstacle(start, end, m_Tile.m_Time, m_Tile.m_Distance, m_Entities[1]));

    twActiveWorld->AddEntity(entity);
}

void CPatternTileCreator::CreateMoving05x10(const bool a_Rotated)
{
    const size_t texture = twRandom::GetNumber(0, MaxObstacleTextures - 1);
    float textureValueFull = 1.0f, textureValueNone = 0.0f;


	//Building effect 
	float distanceToPlayer = (m_PatternSpawnBegin + m_Tile.m_Y) - CGameInfo::Instance().m_PlayerPositionZ;
	float startDistanceBuildValue = 0.0f;

	if (distanceToPlayer < CPatternManager::StartBuildDistance)
		startDistanceBuildValue = distanceToPlayer;
	else if (distanceToPlayer >= CPatternManager::StartBuildDistance)
		startDistanceBuildValue = CPatternManager::StartBuildDistance;

	float startBuild = (startDistanceBuildValue - CPatternManager::EndBuildDistance) / CPatternManager::BuildStrength;

	float rand =GetRandomSign();;

    auto entity = twActiveWorld->CreateEntity();
    m_Entities.push_back(entity);

    // ID
    entity->m_Tag.AddTag("Death");
    entity->m_Tag.AddTag("WallEffect");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, m_Tile.m_PosYStart, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
    switch (m_Tile.m_Moving)
    {
    case SPatternTile::EMovingDirection::Up:
        mesh->m_pMesh = m_pMoving10Up;
        break;
    case SPatternTile::EMovingDirection::Down:
        mesh->m_pMesh = m_pMoving10Down;
        break;
    case SPatternTile::EMovingDirection::Left:
        mesh->m_pMesh = m_pMoving10Left;
        break;
    case SPatternTile::EMovingDirection::Right:
        mesh->m_pMesh = m_pMoving10Right;
        break;
    case SPatternTile::EMovingDirection::Air:
        mesh->m_pMesh = m_pMoving10None;
        break;
    case SPatternTile::EMovingDirection::To:
        mesh->m_pMesh = m_pMoving10To;
        break;
    case SPatternTile::EMovingDirection::Back:
        mesh->m_pMesh = m_pMoving10Back;
        break;
    }
	mesh->m_Material.SetMaterial(m_pMaterialObstacle);
	mesh->m_Material.m_pGeometryShader.SetTexture(0, m_pTextureColorNoise);
	mesh->m_Material.m_pGeometryShader.SetTexture(1, m_pTextureNoise);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &textureValueFull);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &textureValueNone);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &LineColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &FaceEmissiveColor);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &startBuild);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &rand);
	mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle[texture][0]);
	mesh->m_Material.m_pPixelShader.SetTexture(1, m_pTextureObstacle[texture][1]);
	mesh->m_Material.m_pPixelShader.SetTexture(2, m_pTextureObstacle[texture][2]);
	mesh->m_Material.m_pPixelShader.SetTexture(3, m_pTextureEmissiveMoveable);
	mesh->m_Material.m_pPixelShader.SetTexture(4, m_pTextureEmissiveMoveable);
	mesh->m_Material.m_pPixelShader.SetTexture(5, m_pTextureEmissiveMoveable);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
    {
        collider->SetMin(DirectX::XMVectorSet(-5.0f, 0.0f, -2.5f, 0.0f));
        collider->SetMax(DirectX::XMVectorSet(5.0f, 7.0f, 2.5f, 0.0f));
    }
    else
    {
        collider->SetMin(DirectX::XMVectorSet(-2.5f, 0.0f, -5.0f, 0.0f));
        collider->SetMax(DirectX::XMVectorSet(2.5f, 7.0f, 5.0f, 0.0f));
    }

    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    // Shadow
    CreateShadow10(a_Rotated);

    // Behaviour
    DirectX::XMVECTOR start = DirectX::XMVectorSet(m_Tile.m_X, m_Tile.m_PosYStart, m_PatternSpawnBegin + m_Tile.m_Y, 0.0f);
    DirectX::XMVECTOR end = DirectX::XMVectorSet(m_Tile.m_PosXEnd, m_Tile.m_PosYEnd, m_PatternSpawnBegin + m_Tile.m_Y + m_Tile.m_PosZEnd, 0.0f);
    entity->SetBehaviour(new CMovingObstacle(start, end, m_Tile.m_Time, m_Tile.m_Distance, m_Entities[1]));

    twActiveWorld->AddEntity(entity);
}

float CPatternTileCreator::GetRandomSign()
{
	float t = twRandom::GetNumber(-1.0f, 1.0f);

	if (t >= 0)
		return 1.0f;
	else
	{
		return -1.0f;
	}
}
