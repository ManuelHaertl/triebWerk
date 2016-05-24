#include <CPatternManager.h>

CPatternManager::CPatternManager() :
    m_IsSpawned(0.0f),
    m_SpawnTo(SpawnDistance),
    m_PatternSpawnBegin(0.0f),
    m_pCurrentPattern(nullptr),
    m_CurrentTileIndex(0),
    m_DeleteZone(-DeleteDistance)
{

}

CPatternManager::~CPatternManager()
{
    
}

void CPatternManager::Start()
{
    End();

    CPatternLoader patternLoader;
    patternLoader.LoadPattern(m_Pattern);

    SetRandomPattern(0);
}

void CPatternManager::Update(const float a_MetersFlewn)
{
    m_SpawnTo += a_MetersFlewn;
    m_DeleteZone += a_MetersFlewn;

    while (m_IsSpawned < m_SpawnTo)
    {
        SpawnNextTile();
    }

    DeleteEntities();
}

void CPatternManager::End()
{
    // reset values
    m_IsSpawned = 0.0f;
    m_SpawnTo = SpawnDistance;
    m_PatternSpawnBegin = 0.0f;
    m_pCurrentPattern = nullptr;
    m_CurrentTileIndex = 0;
    m_DeleteZone = -DeleteDistance;

    m_Entities.clear();

    for (size_t i = 0; i < CPattern::MaxDifficulty; ++i)
    {
        for (size_t j = 0; j < m_Pattern[i].size(); ++j)
        {
            delete m_Pattern[i][j];
        }

        m_Pattern[i].clear();
    }
}

void CPatternManager::SpawnNextTile()
{
    CPattern& pattern = *m_pCurrentPattern;

    // set the next random pattern if all objects of the current one are spawned
    if (m_CurrentTileIndex >= pattern.m_Tiles.size())
    {
        m_PatternSpawnBegin += pattern.m_Height;

        SetNextPattern();
        m_CurrentTileIndex = 0;
        return;
    }

    // spawn the tile
    SPatternTile& patternTile = pattern.m_Tiles[m_CurrentTileIndex];
    SpawnPatternTile(patternTile);

    m_IsSpawned = m_PatternSpawnBegin + patternTile.m_Y;
    m_CurrentTileIndex++;
}

void CPatternManager::SetNextPattern()
{
    size_t difficulty = CGameInfo::Instance().m_Difficulty - 1;
    size_t priority = 0;

    size_t allPriorities = 0;

    // all this to get a random priority
    for (size_t i = 0; i < m_pCurrentPattern->m_Priorities[difficulty].size(); ++i)
    {
        allPriorities += m_pCurrentPattern->m_Priorities[difficulty][i];
    }

    size_t randomNumber = twRandom::GetNumber(0, allPriorities);

    for (size_t i = 0; i < m_pCurrentPattern->m_Priorities[difficulty].size(); ++i)
    {
        size_t curPrio = m_pCurrentPattern->m_Priorities[difficulty][i];
        if (randomNumber <= curPrio)
        {
            priority = curPrio;
            break;
        }
        else
        {
            randomNumber -= curPrio;
        }
    }


    // pick a random pattern based on the diffulty and priority
    size_t patternCount = m_pCurrentPattern->m_ConnectedPattern[difficulty][priority].size() - 1;
    int randomPatternNumber = twRandom::GetNumber(0, patternCount);

    m_pCurrentPattern = m_pCurrentPattern->m_ConnectedPattern[difficulty][priority][randomPatternNumber];

    auto color = triebWerk::CDebugLogfile::EColor::Black;
    int prio = CPattern::MaxPriorities + 1 - m_pCurrentPattern->m_Priority;
    std::string log =
        "Name: " + m_pCurrentPattern->m_Name +
        " Difficulty: " + std::to_string(m_pCurrentPattern->m_Difficulty) +
        " Priority: " + std::to_string(prio);


    triebWerk::CDebugLogfile::Instance().LogfText(color, false, log.c_str());
}

void CPatternManager::DeleteEntities()
{
    for (;;)
    {
        auto entity = m_Entities.front();
        if (entity->m_Transform.GetPosition().m128_f32[2] < m_DeleteZone)
        {
            twActiveWorld->RemoveEntity(entity);
            m_Entities.erase(m_Entities.begin());
        }
        else
        {
            break;
        }
    }
}

void CPatternManager::SpawnPatternTile(const SPatternTile& a_rPatternTile)
{
    DirectX::XMFLOAT3 colorBlock = { 0.9f, 0.9f, 0.9f };

    switch (a_rPatternTile.m_Type)
    {
    case ETileType::Block1x1:
    {
        auto entity = twActiveWorld->CreateEntity();
        entity->m_Transform.SetPosition(a_rPatternTile.m_X, 5.0f, m_PatternSpawnBegin + a_rPatternTile.m_Y);
        entity->m_Transform.SetScale(1.0f, 10.0f, 1.0f);

        triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
        mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
        mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
        entity->SetDrawable(mesh);

        auto physicEntity = twActivePhysic->CreatePhysicEntity();
        auto collider = twActivePhysic->CreateAABBCollider();
        collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
        collider->m_CheckCollision = false;
        physicEntity->AddCollider(collider);
        entity->SetPhysicEntity(physicEntity);

        twActiveWorld->AddEntity(entity);
        m_Entities.push_back(entity);
        break;
    }
    case ETileType::Block2x2:
    {
        auto entity = twActiveWorld->CreateEntity();
        entity->m_Transform.SetPosition(a_rPatternTile.m_X, 0.0f, m_PatternSpawnBegin + a_rPatternTile.m_Y);
        entity->m_Transform.SetScale(2.0f, 1.0f, 2.0f);

        triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
        mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
        mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
        entity->SetDrawable(mesh);
        twActiveWorld->AddEntity(entity);
        m_Entities.push_back(entity);
        break;
    }
    }
}

void CPatternManager::SetRandomPattern(size_t a_Difficulty)
{
    size_t max = m_Pattern[a_Difficulty].size();
    int random = twRandom::GetNumber(0, max - 1);

    m_pCurrentPattern = m_Pattern[a_Difficulty][random];
}
