#include <CPatternTileCreator.h>

#include <CCheckpoint.h>
#include <CPoints.h>

CPatternTileCreator::CPatternTileCreator()
{
}

CPatternTileCreator::~CPatternTileCreator()
{
}

triebWerk::CEntity* CPatternTileCreator::CreateEntity(const SPatternTile& a_rTile, const float a_PatternSpawnBegin)
{
    m_Tile = a_rTile;
    m_PatternSpawnBegin = a_PatternSpawnBegin;

    switch (a_rTile.m_Type)
    {
    case ETileType::Checkpoint:
        return CreateCheckpoint();
    case ETileType::Points:
        return CreatePoints();
    case ETileType::Shield:
        return CreateShield();
    case ETileType::Block1x1:
        return CreateBlock1x1();
    case ETileType::Block2x2:
        return CreateBlock2x2();
    case ETileType::Model05x05:
        return CreateModel05x05();
    case ETileType::Model05x05Flipped:
        return CreateModel05x05Flipped();
    case ETileType::Model05x10:
        return CreateModel05x10();
    case ETileType::Model05x10Flipped:
        return CreateModel05x10Flipped();
    case ETileType::Model05x20:
        return CreateModel05x20();
    case ETileType::Model05x20Flipped:
        return CreateModel05x20Flipped();
    case ETileType::Model05x30:
        return CreateModel05x30();
    case ETileType::Model05x30Flipped:
        return CreateModel05x30Flipped();
    }

    return nullptr;
}

triebWerk::CEntity* CPatternTileCreator::CreateCheckpoint()
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
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreatePoints()
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
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateShield()
{
    return nullptr;
}

triebWerk::CEntity* CPatternTileCreator::CreateBlock1x1()
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
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateBlock2x2()
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
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x05()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x05x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x05Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x05x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x10()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x10x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 10.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x10Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x10x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(10.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x20()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x20x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 20.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x20Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x20x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(20.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x30()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x30x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(5.0f, 8.0f, 30.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}

triebWerk::CEntity* CPatternTileCreator::CreateModel05x30Flipped()
{
    auto entity = twActiveWorld->CreateEntity();

    // ID
    entity->m_ID.SetName("Wall");

    // Transform
    entity->m_Transform.SetPosition(m_Tile.m_X, 0.0f, m_PatternSpawnBegin + m_Tile.m_Y);
    entity->m_Transform.SetRotationDegrees(0.0f, 90.0f, 0.0f);

    // Rendering
    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x30x08_base");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.9f, 0.9f, 0.9f));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = twActivePhysic->CreatePhysicEntity();
    auto collider = twActivePhysic->CreateAABBCollider();
    collider->SetSize(30.0f, 8.0f, 5.0f);
    collider->m_CheckCollision = false;
    physicEntity->AddCollider(collider);
    entity->SetPhysicEntity(physicEntity);

    twActiveWorld->AddEntity(entity);
    return entity;
}
