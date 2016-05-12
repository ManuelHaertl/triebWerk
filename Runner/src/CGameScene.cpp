#include <CGameScene.h>

CGameScene::CGameScene() :
    m_pPattern(nullptr),
    m_PatternCount(0),
    m_MinDifficulty(0),
    m_MaxDifficulty(0),
    m_MinPriority(0),
    m_MaxPriority(0)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Start()
{
    LoadAllPattern();
    CreateFloorAndSidewalls();
    CreatePattern();
    //CreateTestCubes();

    CreatePlayer();

    // camera settings
    auto camera = twEngine.m_pRenderer->GetCurrentActiveCamera();
    camera->m_Transform.SetPosition(0.0f, 4.32f, -9.23f);
    camera->m_Transform.SetRotationDegrees(5.7f, 0.0f, 0.0f);
    camera->SetNear(0.1f);
    camera->SetFar(1000.0f);
    camera->SetFOV(DirectX::XMConvertToRadians(44.0f));
}

void CGameScene::Update()
{
    if (twKeyboard.IsState(triebWerk::EKey::F3, triebWerk::EButtonState::Down))
    {
        if (!twDebug->IsInDebug())
            twDebug->Enable();
        else
            twDebug->Disable();
    }
}

void CGameScene::End()
{
    if (m_pPattern != nullptr)
    {
        delete[] m_pPattern;
    }
}

void CGameScene::LoadAllPattern()
{
    CPatternLoader patternLoader;
    patternLoader.LoadPattern();

    m_pPattern = patternLoader.GetPattern();
    m_PatternCount = patternLoader.GetPatternCount();
    m_MinDifficulty = patternLoader.GetMinDifficulty();
    m_MaxDifficulty = patternLoader.GetMaxDifficulty();
    m_MinPriority = patternLoader.GetMinPriority();
    m_MaxPriority = patternLoader.GetMaxPriority();
}

void CGameScene::CreateFloorAndSidewalls()
{
    DirectX::XMFLOAT3 colorSideWalls = { 1.0f, 0.5f, 0.5f };
    DirectX::XMFLOAT3 colorFloor = { 0.1f, 0.1f, 0.1f };

    // left side wall
    auto wallLeft = twWorld->CreateEntity();
    wallLeft->m_Transform.SetPosition(-30.0f, 2.5f, 50.0f);
    wallLeft->m_Transform.SetScale(10.0f, 5.0f, 1000.0f);
    wallLeft->m_ID.SetName("SideLeft");

    triebWerk::CMeshDrawable* meshLeft = twRenderer->CreateMeshDrawable();
    meshLeft->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    meshLeft->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    meshLeft->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorSideWalls);
    wallLeft->SetDrawable(meshLeft);

    auto physicEntityLeft = twPhysic->CreatePhysicEntity();
    auto collLeft = twPhysic->CreateAABBCollider();
    collLeft->SetSize(1.2f, 1.0f, 1.0f);
    collLeft->m_CheckCollision = false;
    physicEntityLeft->AddCollider(collLeft);
    wallLeft->SetPhysicEntity(physicEntityLeft);

    twWorld->AddEntity(wallLeft);

    // right side wall
    auto wallRight = twWorld->CreateEntity();
    wallRight->m_Transform.SetPosition(30.0f, 2.5f, 50.0f);
    wallRight->m_Transform.SetScale(10.0f, 5.0f, 1000.0f);
    wallRight->m_ID.SetName("SideRight");

    triebWerk::CMeshDrawable* meshRight = twRenderer->CreateMeshDrawable();
    meshRight->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    meshRight->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    meshRight->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorSideWalls);
    wallRight->SetDrawable(meshRight);

    auto physicEntityRight = twPhysic->CreatePhysicEntity();
    auto collRight = twPhysic->CreateAABBCollider();
    collRight->SetSize(1.2f, 1.0f, 1.0f);
    collRight->m_CheckCollision = false;
    physicEntityRight->AddCollider(collRight);
    wallRight->SetPhysicEntity(physicEntityRight);

    twWorld->AddEntity(wallRight);

    // ground
    auto floor = twWorld->CreateEntity();
    floor->m_Transform.SetPosition(0.0f, -0.5f, 0.0f);
    floor->m_Transform.SetScale(1000.0f, 1.0f, 1000.0f);

    triebWerk::CMeshDrawable* meshBottom = twRenderer->CreateMeshDrawable();
    meshBottom->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    meshBottom->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    meshBottom->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorFloor);
    floor->SetDrawable(meshBottom);
    twWorld->AddEntity(floor);
}

void CGameScene::CreatePattern()
{
    CPattern& pattern = m_pPattern[0];
    DirectX::XMFLOAT3 colorBlock = { 0.9f, 0.9f, 0.9f };

    for (size_t i = 0; i < pattern.m_Tiles.size(); ++i)
    {
        SPatternTile& tile = pattern.m_Tiles[i];

        switch (tile.m_Type)
        {
        case ETileType::Block1x1:
        {
            auto entity = twWorld->CreateEntity();
            entity->m_Transform.SetPosition(tile.m_X, 1.5f, tile.m_Y);
            entity->m_Transform.SetScale(1.0f, 3.0f, 1.0f);

            triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
            mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
            mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
            mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
            entity->SetDrawable(mesh);

            auto physicEntity = twPhysic->CreatePhysicEntity();
            auto collider = twPhysic->CreateAABBCollider();
            collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
            collider->m_CheckCollision = false;
            physicEntity->AddCollider(collider);
            entity->SetPhysicEntity(physicEntity);

            twWorld->AddEntity(entity);
            break;
        }
        case ETileType::Block2x2:
        {
            auto entity = twWorld->CreateEntity();
            entity->m_Transform.SetPosition(tile.m_X, 0.0f, tile.m_Y);
            entity->m_Transform.SetScale(2.0f, 1.0f, 2.0f);

            triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
            mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
            mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
            mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
            entity->SetDrawable(mesh);
            twWorld->AddEntity(entity);
            break;
        }
        }
    }
}

void CGameScene::CreateTestCubes()
{
    const int range = 30;
    const int incrementer = 5;
    const int freeArea = 1;
    DirectX::XMFLOAT3 colorBlock = { 0.5f, 0.5f, 0.5f };

    for (int x = -range; x < range; x += incrementer)
    {
        for (int y = -range; y < range; y += incrementer)
        {
            for (int z = -range; z < range; z += incrementer)
            {
                auto entity = twWorld->CreateEntity();
                entity->m_Transform.SetPosition(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

                triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
                mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
                mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
                mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
                entity->SetDrawable(mesh);
                twWorld->AddEntity(entity);
            }
        }
    }
}

void CGameScene::CreatePlayer()
{
    DirectX::XMFLOAT3 colorPlayer = { 0.0f, 0.0f, 1.0f };

    auto player = twWorld->CreateEntity();

    // Transform
    player->m_Transform.SetPosition(0.0f, 1.0f, 0.0f);
    player->m_Transform.SetRotationDegrees(0.0f, 0.0f, 0.0f);
    player->m_Transform.SetScale(1.5f, 0.7f, 2.0f);

    // Behaviour
    player->SetBehaviour(new CPlayer());

    // Drawable
    triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorPlayer);
    player->SetDrawable(mesh);

    // Physic
    auto physicEntity = twPhysic->CreatePhysicEntity();

    auto collbox = twPhysic->CreateAABBCollider();
    collbox->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collbox->m_CheckCollision = true;
    physicEntity->AddCollider(collbox);

    auto body = twPhysic->CreateBody();
    body->m_GravityFactor = 0.0f;
    physicEntity->SetBody(body);

    player->SetPhysicEntity(physicEntity);

    twWorld->AddEntity(player);
}
