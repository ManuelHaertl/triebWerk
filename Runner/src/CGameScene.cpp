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
    auto wallLeft = twWorld->CreateEntity();
    wallLeft->m_Transform.SetPosition(-24.5f, 2.5f, 50.0f);
    wallLeft->m_Transform.SetScale(1.0f, 5.0f, 1000.0f);

    triebWerk::CMeshDrawable* meshLeft = twRenderer->CreateMeshDrawable();
    meshLeft->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    meshLeft->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardRed"));
    wallLeft->SetDrawable(meshLeft);
    twWorld->AddEntity(wallLeft);

    auto wallRight = twWorld->CreateEntity();
    wallRight->m_Transform.SetPosition(25.5f, 2.5f, 50.0f);
    wallRight->m_Transform.SetScale(1.0f, 5.0f, 1000.0f);

    triebWerk::CMeshDrawable* meshRight = twRenderer->CreateMeshDrawable();
    meshRight->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    meshRight->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardRed"));
    wallRight->SetDrawable(meshRight);
    twWorld->AddEntity(wallRight);

    auto floor = twWorld->CreateEntity();
    floor->m_Transform.SetPosition(0.0f, -0.5f, 0.0f);
    floor->m_Transform.SetScale(1000.0f, 1.0f, 1000.0f);

    triebWerk::CMeshDrawable* meshBottom = twRenderer->CreateMeshDrawable();
    meshBottom->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    meshBottom->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardGray"));
    floor->SetDrawable(meshBottom);
    twWorld->AddEntity(floor);
}

void CGameScene::CreatePattern()
{
    CPattern& pattern = m_pPattern[0];

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
            mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardDarkGray"));
            entity->SetDrawable(mesh);
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
            mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardGray"));
            entity->SetDrawable(mesh);
            twWorld->AddEntity(entity);
            break;
        }
        }
    }
}

void CGameScene::CreateTestCubes()
{
    const int range = 40;
    const int incrementer = 5;
    const int freeArea = 1;

    for (int x = -range; x < range; x += incrementer)
    {
        for (int y = -range; y < range; y += incrementer)
        {
            for (int z = -range; z < range; z += incrementer)
            {
                auto entity = twWorld->CreateEntity();
                entity->m_Transform.SetPosition(x, y, z);

                triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
                mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
                mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardGray"));
                entity->SetDrawable(mesh);
                twWorld->AddEntity(entity);
            }
        }
    }
}

void CGameScene::CreatePlayer()
{
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
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Standard"));
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
