#include <CEnvironmentCreator.h>

CEnvironmentCreator::CEnvironmentCreator() :
    m_RoadAllLength(0.0f),
    m_RoadMoveZone(-RoadMoveDistance),
    m_RoadCount(0),
    m_FeathersIsSpawnedTo(0.0f),
    m_FeathersSpawnTo(SpawnDistance),
    m_FeathersDeleteZone(-FeathersDeleteDistance),
    m_pEndWall(nullptr)
{
}

CEnvironmentCreator::~CEnvironmentCreator()
{
}

void CEnvironmentCreator::Start()
{
    m_RoadCount = static_cast<size_t>(SpawnDistance / RoadLength);
    m_RoadAllLength = m_RoadCount * RoadLength;

    CreateFloor();
    CreateCollisionSideWalls();
    CreateEndWall();
}

void CEnvironmentCreator::Update(const float a_MetersFlewn)
{
    m_FeathersSpawnTo += a_MetersFlewn;
    m_FeathersDeleteZone += a_MetersFlewn;

    while (m_FeathersIsSpawnedTo < m_FeathersSpawnTo)
    {
        SpawnFeathers();
    }

    DeleteFeathers();

    CheckFloorPosition(a_MetersFlewn);
    MoveEndWall(a_MetersFlewn);
}

void CEnvironmentCreator::End()
{

}

void CEnvironmentCreator::SpawnFeathers()
{
    int randomNumber = twRandom::GetNumber(0, 99);
    if (randomNumber < FeatherSpawnProbability)
    {
        auto entity = twWorld->CreateEntity();
        entity->m_Transform.SetPosition(0.0f, 0.0f, m_FeathersIsSpawnedTo);
        entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

        triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_feathers_01");
        mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
        mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("feather_diff_01"));
        entity->SetDrawable(mesh);

        twWorld->AddEntity(entity);
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
            twWorld->RemoveEntity(entity);
            m_FeathersEntities.erase(m_FeathersEntities.begin());
        }
        else
        {
            break;
        }
    }
}

void CEnvironmentCreator::CreateFloor()
{
    m_RoadEntities.clear();

    float position = 0.0f;
    for (size_t i = 0; i < m_RoadCount; ++i)
    {
        auto entity = twWorld->CreateEntity();
        entity->m_Transform.SetPosition(0.0f, 0.0f, position);
        entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

        triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_course_01");
        mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
        mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_course_diff"));
        entity->SetDrawable(mesh);

        twWorld->AddEntity(entity);
        m_RoadEntities.push_back(entity);

        position += RoadLength;
    }
}

void CEnvironmentCreator::CreateCollisionSideWalls()
{
    // left side wall
    auto wallLeft = twWorld->CreateEntity();
    wallLeft->m_Transform.SetPosition(-30.0f, 2.5f, 50.0f);
    wallLeft->m_Transform.SetScale(10.0f, 10.0f, 1000000.0f);
    wallLeft->m_ID.SetName("SideLeft");

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
    wallRight->m_Transform.SetScale(10.0f, 10.0f, 1000000.0f);
    wallRight->m_ID.SetName("SideRight");

    auto physicEntityRight = twPhysic->CreatePhysicEntity();
    auto collRight = twPhysic->CreateAABBCollider();
    collRight->SetSize(1.2f, 1.0f, 1.0f);
    collRight->m_CheckCollision = false;
    physicEntityRight->AddCollider(collRight);
    wallRight->SetPhysicEntity(physicEntityRight);

    twWorld->AddEntity(wallRight);
}

void CEnvironmentCreator::CreateEndWall()
{
    m_pEndWall = twWorld->CreateEntity();
    m_pEndWall->m_Transform.SetPosition(0.0f, -500.0f, 500.0f);
    m_pEndWall->m_Transform.SetScale(3000.0f, 2500.0f, 1.0f);

    triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
    mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_endwall"));
    m_pEndWall->SetDrawable(mesh);

    twWorld->AddEntity(m_pEndWall);
}

void CEnvironmentCreator::CheckFloorPosition(const float a_MetersFlewn)
{
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

void CEnvironmentCreator::MoveEndWall(const float a_MetersFlewn)
{
    DirectX::XMVECTOR position = m_pEndWall->m_Transform.GetPosition();
    position.m128_f32[2] += a_MetersFlewn;
    m_pEndWall->m_Transform.SetPosition(position);
}
