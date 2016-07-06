#include <CPatternTileCreator.h>

#include <CCheckpoint.h>
#include <CPoints.h>

CPatternTileCreator::CPatternTileCreator()
    : m_pFirstEntity(nullptr)
    , m_pSecondEntity(nullptr)
    , m_Tile()
    , m_PatternSpawnBegin(0.0f)
{
    m_pCheckPoint = twResourceManager->GetMesh("checkpoint");
    m_pPoints = twResourceManager->GetMesh("points");
    m_pBlock1x1 = twResourceManager->GetMesh("cube");
    m_pBlock2x2 = twResourceManager->GetMesh("cube");

    m_pObstacle05x05x08 = twResourceManager->GetMesh("ms_obs_05x05x08_base");
    m_pObstacle05x05x08Deko1 = twResourceManager->GetMesh("ms_obs_05x05x08_deko_01");
    m_pObstacle05x05x08Deko2 = twResourceManager->GetMesh("ms_obs_05x05x08_deko_02");
    m_pObstacle05x05x08Deko3 = twResourceManager->GetMesh("ms_obs_05x05x08_deko_03");
    m_pObstacle05x05x12 = twResourceManager->GetMesh("ms_obs_05x05x12_base");
    m_pObstacle05x05x12Deko1 = twResourceManager->GetMesh("ms_obs_05x05x12_deko_01");
    m_pObstacle05x05x12Deko2 = twResourceManager->GetMesh("ms_obs_05x05x12_deko_02");
    m_pObstacle05x05x12Deko3 = twResourceManager->GetMesh("ms_obs_05x05x12_deko_03");

    m_pObstacle05x10x08 = twResourceManager->GetMesh("ms_obs_05x10x08_base");
    m_pObstacle05x10x08Deko1 = twResourceManager->GetMesh("ms_obs_05x10x08_deko_01");
    m_pObstacle05x10x08Deko2 = twResourceManager->GetMesh("ms_obs_05x10x08_deko_02");
    m_pObstacle05x10x08Deko3 = twResourceManager->GetMesh("ms_obs_05x10x08_deko_03");
    m_pObstacle05x10x12 = twResourceManager->GetMesh("ms_obs_05x10x12_base");
    m_pObstacle05x10x12Deko1 = twResourceManager->GetMesh("ms_obs_05x10x12_deko_01");
    m_pObstacle05x10x12Deko2 = twResourceManager->GetMesh("ms_obs_05x10x12_deko_02");
    m_pObstacle05x10x12Deko3 = twResourceManager->GetMesh("ms_obs_05x10x12_deko_03");

    m_pObstacle05x20x08 = twResourceManager->GetMesh("ms_obs_05x20x08_base");
    m_pObstacle05x20x08Deko1 = twResourceManager->GetMesh("ms_obs_05x20x08_deko_01");
    m_pObstacle05x20x08Deko2 = twResourceManager->GetMesh("ms_obs_05x20x08_deko_02");
    m_pObstacle05x20x08Deko3 = twResourceManager->GetMesh("ms_obs_05x20x08_deko_03");
    m_pObstacle05x20x12 = twResourceManager->GetMesh("ms_obs_05x20x12_base");
    m_pObstacle05x20x12Deko1 = twResourceManager->GetMesh("ms_obs_05x20x12_deko_01");
    m_pObstacle05x20x12Deko2 = twResourceManager->GetMesh("ms_obs_05x20x12_deko_02");
    m_pObstacle05x20x12Deko3 = twResourceManager->GetMesh("ms_obs_05x20x12_deko_03");

    m_pObstacle05x30x08 = twResourceManager->GetMesh("ms_obs_05x30x08_base");
    m_pObstacle05x30x08Deko1 = twResourceManager->GetMesh("ms_obs_05x30x08_deko_01");
    m_pObstacle05x30x08Deko2 = twResourceManager->GetMesh("ms_obs_05x30x08_deko_02");
    m_pObstacle05x30x08Deko3 = twResourceManager->GetMesh("ms_obs_05x30x08_deko_03");
    m_pObstacle05x30x12 = twResourceManager->GetMesh("ms_obs_05x30x12_base");
    m_pObstacle05x30x12Deko1 = twResourceManager->GetMesh("ms_obs_05x30x12_deko_01");
    m_pObstacle05x30x12Deko2 = twResourceManager->GetMesh("ms_obs_05x30x12_deko_02");
    m_pObstacle05x30x12Deko3 = twResourceManager->GetMesh("ms_obs_05x30x12_deko_03");

    m_pTextureObstacle = twResourceManager->GetTexture2D("T_obs_01");

    m_pMaterialStandardColor = twResourceManager->GetMaterial("StandardColor");
    m_pMaterialStandardTexture = twResourceManager->GetMaterial("StandardTexture");
}

CPatternTileCreator::~CPatternTileCreator()
{
}

void CPatternTileCreator::CreateEntity(const SPatternTile& a_rTile, const float a_PatternSpawnBegin)
{
    m_Tile = a_rTile;
    m_PatternSpawnBegin = a_PatternSpawnBegin;

    m_pFirstEntity = nullptr;
    m_pSecondEntity = nullptr;

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
        CreateModel05x05();
        break;
    case ETileType::Model05x05Flipped:
        CreateModel05x05Flipped();
        break;
    case ETileType::Model05x10:
        CreateModel05x10();
        break;
    case ETileType::Model05x10Flipped:
        CreateModel05x10Flipped();
        break;
    case ETileType::Model05x20:
        CreateModel05x20();
        break;
    case ETileType::Model05x20Flipped:
        CreateModel05x20Flipped();
        break;
    case ETileType::Model05x30:
        CreateModel05x30();
        break;
    case ETileType::Model05x30Flipped:
        CreateModel05x30Flipped();
        break;
    }
}

void CPatternTileCreator::CreateCheckpoint()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Checkpoint");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.5f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetScale(1.3f, 1.3f, 1.3f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("checkpoint");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.2f, 1.0f, 0.2f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    // Behaviour
    entity->SetBehaviour(new CCheckpoint());

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreatePoints()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Points");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 1.5f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("points");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(0.8f, 0.8f, 0.8f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    // Behaviour
    entity->SetBehaviour(new CPoints());

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateShield()
{
    m_pFirstEntity = nullptr;
}

void CPatternTileCreator::CreateBlock1x1()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 5.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetScale(1.0f, 10.0f, 1.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
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
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateBlock2x2()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 5.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetScale(2.0f, 10.0f, 2.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
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
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x05()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();

    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x05x08 : mesh->m_pMesh = m_pObstacle05x05x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x05Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x05x08 : mesh->m_pMesh = m_pObstacle05x05x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x10()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x10x08 : mesh->m_pMesh = m_pObstacle05x10x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 10.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x10Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x10x08 : mesh->m_pMesh = m_pObstacle05x10x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(10.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x20()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x20x08 : mesh->m_pMesh = m_pObstacle05x20x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 20.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x20Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x20x08 : mesh->m_pMesh = m_pObstacle05x20x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(20.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x30()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x30x08 : mesh->m_pMesh = m_pObstacle05x30x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 30.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}

void CPatternTileCreator::CreateModel05x30Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    (twRandom::GetNumber(0, 1) == 0) ? mesh->m_pMesh = m_pObstacle05x30x08 : mesh->m_pMesh = m_pObstacle05x30x12;
    mesh->m_Material.SetMaterial(m_pMaterialStandardTexture);
    mesh->m_Material.m_pPixelShader.SetTexture(0, m_pTextureObstacle);
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(30.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    m_pFirstEntity = entity;
}
