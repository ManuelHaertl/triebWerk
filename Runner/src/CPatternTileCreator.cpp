#include <CPatternTileCreator.h>

#include <CCheckpoint.h>
#include <CPoints.h>

CPatternTileCreator::CPatternTileCreator()
    : m_pEntity1(nullptr)
    , m_pEntity2(nullptr)
    , m_pEntity3(nullptr)
    , m_Tile()
    , m_PatternSpawnBegin(0.0f)
{
    m_pCheckPoint = twResourceManager->GetMesh("ms_checkpoint");
    m_pPoints = twResourceManager->GetMesh("ms_points");
    m_pBlock1x1 = twResourceManager->GetMesh("cube");
    m_pBlock2x2 = twResourceManager->GetMesh("cube");

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

    m_pTextureObstacle = twResourceManager->GetTexture2D("T_obs_01");
    m_pTexturePoints = twResourceManager->GetTexture2D("T_points_diff");
    m_pTextureCheckpoint = twResourceManager->GetTexture2D("T_checkpoint_diff");
    m_pTextureShadow05 = twResourceManager->GetTexture2D("t_shadow_05x05");
    m_pTextureShadow10 = twResourceManager->GetTexture2D("t_shadow_05x10");
    m_pTextureShadow20 = twResourceManager->GetTexture2D("t_shadow_05x20");
    m_pTextureShadow30 = twResourceManager->GetTexture2D("t_shadow_05x30");

    m_pMaterialStandardColor = twResourceManager->GetMaterial("StandardColor");
    m_pMaterialStandardTexture = twResourceManager->GetMaterial("StandardTexture");
    m_pMaterialStandardTransparentTexture = twResourceManager->GetMaterial("StandardTransparentTexture");
}

CPatternTileCreator::~CPatternTileCreator()
{
}

void CPatternTileCreator::CreateEntity(const SPatternTile& a_rTile, const float a_PatternSpawnBegin)
{
    m_Tile = a_rTile;
    m_PatternSpawnBegin = a_PatternSpawnBegin;

    m_pEntity1 = twActiveWorld->CreateEntity();
    m_pEntity2 = nullptr;
    m_pEntity3 = nullptr;

    switch (a_rTile.m_Type)
    {
    case ETileType::Checkpoint:
        CreateCheckpoint();
        break;
    case ETileType::Points:
        CreatePoints();
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
    }

    twActiveWorld->AddEntity(m_pEntity1);
}

void CPatternTileCreator::CreateCheckpoint()
{
    // ID
    m_pEntity1->m_ID.SetName("Checkpoint");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 0.5f, m_PatternSpawnBegin + m_Tile.m_Y);
    m_pEntity1->m_Transform.SetScale(1.3f, 1.3f, 1.3f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pCheckPoint;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureCheckpoint);
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);

    // Behaviour
    m_pEntity1->SetBehaviour(new CCheckpoint());
}

void CPatternTileCreator::CreatePoints()
{
    // ID
    m_pEntity1->m_ID.SetName("Points");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 1.5f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pPoints;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTexturePoints);
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(0.8f, 0.8f, 0.8f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);

    // Behaviour
    m_pEntity1->SetBehaviour(new CPoints());
}

void CPatternTileCreator::CreateShield()
{
    
}

void CPatternTileCreator::CreateBlock1x1()
{
    // ID
    m_pEntity1->m_ID.SetName("Wall");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 5.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    m_pEntity1->m_Transform.SetScale(1.0f, 10.0f, 1.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pBlock1x1;
    mesh->m_Material.SetMaterial(m_pMaterialStandardColor);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);
}

void CPatternTileCreator::CreateBlock2x2()
{
    // ID
    m_pEntity1->m_ID.SetName("Wall");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 5.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    m_pEntity1->m_Transform.SetScale(2.0f, 10.0f, 2.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pBlock2x2;
    mesh->m_Material.SetMaterial(m_pMaterialStandardColor);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);
}

void CPatternTileCreator::CreateModel05x05(const bool a_Rotated)
{
    size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);

    // ID
    m_pEntity1->m_ID.SetName("Wall");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pObstacle05[height];
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(5.0f, 8.0f, 5.0f);
    else
        collider->SetSize(5.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);

    // --------- Deko ---------

    m_pEntity2 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto dekoMesh = twRenderer->CreateMeshDrawable();
    dekoMesh->m_pMesh = m_pObstacle05Dekos[height][deko];
    dekoMesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    dekoMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity2->SetDrawable(dekoMesh);

    twActiveWorld->AddEntity(m_pEntity2);

    CreateShadow05(a_Rotated);
}

void CPatternTileCreator::CreateModel05x10(const bool a_Rotated)
{
    size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);

    // ID
    m_pEntity1->m_ID.SetName("Wall");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pObstacle10[height];
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(10.0f, 8.0f, 5.0f);
    else 
        collider->SetSize(5.0f, 8.0f, 10.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);

    // --------- Deko ---------

    m_pEntity2 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto dekoMesh = twRenderer->CreateMeshDrawable();
    dekoMesh->m_pMesh = m_pObstacle10Dekos[height][deko];
    dekoMesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    dekoMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity2->SetDrawable(dekoMesh);

    twActiveWorld->AddEntity(m_pEntity2);

    CreateShadow10(a_Rotated);
}

void CPatternTileCreator::CreateModel05x20(const bool a_Rotated)
{
    size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);

    // ID
    m_pEntity1->m_ID.SetName("Wall");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pObstacle20[height];
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(20.0f, 8.0f, 5.0f);
    else
        collider->SetSize(5.0f, 8.0f, 20.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);

    // --------- Deko ---------

    m_pEntity2 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pObstacle20Dekos[height][deko];
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity2->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(m_pEntity2);

    CreateShadow20(a_Rotated);
}

void CPatternTileCreator::CreateModel05x30(const bool a_Rotated)
{
    size_t height = twRandom::GetNumber(0, MaxObstacleHeights - 1);
    size_t deko = twRandom::GetNumber(0, MaxObstacleDekos - 1);

    // ID
    m_pEntity1->m_ID.SetName("Wall");

    // Transform
    m_pEntity1->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity1->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = m_pObstacle30[height];
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity1->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    if (a_Rotated)
        collider->SetSize(30.0f, 8.0f, 5.0f);
    else
        collider->SetSize(5.0f, 8.0f, 30.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    m_pEntity1->SetPhysicEntity(physicEntity);

    // --------- Deko ---------

    m_pEntity2 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity2->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity2->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pObstacle30Dekos[height][deko];
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    m_pEntity2->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(m_pEntity2);

    CreateShadow30(a_Rotated);
}

void CPatternTileCreator::CreateShadow05(const bool a_Rotated)
{
    m_pEntity3 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity3->m_Transform.SetPosition(m_Tile.m_X, 0.001f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity3->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow05;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow05);
    m_pEntity3->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(m_pEntity3);
}

void CPatternTileCreator::CreateShadow10(const bool a_Rotated)
{
    m_pEntity3 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity3->m_Transform.SetPosition(m_Tile.m_X, 0.001f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity3->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow10;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow10);
    m_pEntity3->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(m_pEntity3);
}

void CPatternTileCreator::CreateShadow20(const bool a_Rotated)
{
    m_pEntity3 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity3->m_Transform.SetPosition(m_Tile.m_X, 0.001f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity3->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow20;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow20);
    m_pEntity3->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(m_pEntity3);
}

void CPatternTileCreator::CreateShadow30(const bool a_Rotated)
{
    m_pEntity3 = twActiveWorld->CreateEntity();

    // Transform
    m_pEntity3->m_Transform.SetPosition(m_Tile.m_X, 0.001f, m_PatternSpawnBegin + m_Tile.m_Y);
    if (a_Rotated) m_pEntity3->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto shadowMesh = twRenderer->CreateMeshDrawable();
    shadowMesh->m_pMesh = m_pShadow30;
    shadowMesh->m_Material.SetMaterial(m_pMaterialStandardTransparentTexture);
    shadowMesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureShadow30);
    m_pEntity3->SetDrawable(shadowMesh);

    twActiveWorld->AddEntity(m_pEntity3);
}
