#include <CPatternManager.h>

CPatternManager::CPatternManager() :
    m_pPattern(nullptr),
    m_PatternCount(0),
    m_MinDifficulty(0),
    m_MaxDifficulty(0),
    m_MinPriority(0),
    m_MaxPriority(0),
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
    if (m_pPattern != nullptr)
    {
        delete[] m_pPattern;
    }
}

void CPatternManager::LoadPattern()
{
    CPatternLoader patternLoader;
    patternLoader.LoadPattern();

    m_pPattern = patternLoader.GetPattern();
    m_PatternCount = patternLoader.GetPatternCount();
    m_MinDifficulty = patternLoader.GetMinDifficulty();
    m_MaxDifficulty = patternLoader.GetMaxDifficulty();
    m_MinPriority = patternLoader.GetMinPriority();
    m_MaxPriority = patternLoader.GetMaxPriority();

    CGameInfo::Instance().m_Difficulty = m_MinDifficulty;

    m_pCurrentPattern = &m_pPattern[0];
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
    //CPattern& pattern = *m_pCurrentPattern;
    //size_t size = pattern.m_ConnectedPattern.size();

    //// pick any random pattern if the current one has no connected pattern
    //if (size == 0)
    //{
    //    m_pCurrentPattern = &m_pPattern[twRandom::GetNumber(0, m_PatternCount - 1)];
    //    return;
    //}

    //// get the range of difficulty pattern that can spawn
    //int minDifficulty = CGameInfo::Instance().m_Difficulty - DifficultyMinRange;
    //int maxDifficulty = CGameInfo::Instance().m_Difficulty + DifficultyMaxRange;

    //// clamp the difficulty to those that really exist
    //if (minDifficulty < m_MinDifficulty)
    //    minDifficulty = m_MinDifficulty;

    //if (maxDifficulty > m_MaxDifficulty)
    //    maxDifficulty = m_MaxDifficulty;

    //std::vector<CPattern*> possiblePattern;
    //int maxPriority = 0;

    //// add all pattern that are in the difficulty range 
    //for (size_t i = 0; i < size; ++i)
    //{
    //    CPattern* curPattern = pattern.m_ConnectedPattern[i];

    //    int difficulty = curPattern->m_Difficulty;
    //    if (difficulty >= minDifficulty &&
    //        difficulty <= maxDifficulty)
    //    {
    //        possiblePattern.push_back(curPattern);

    //        // add the priority
    //        maxPriority += curPattern->m_Priority;
    //    }
    //}

    //// pick a random pattern depending on the priority
    //int randomNumber = twRandom::GetNumber(0, maxPriority);
    //int possiblePatternSize = possiblePattern.size();

    //for (size_t i = 0; i < possiblePatternSize; ++i)
    //{
    //    if (randomNumber <= maxPriority)
    //    {
    //        m_pCurrentPattern = possiblePattern[i];
    //        break;
    //    }

    //    randomNumber += possiblePattern[i]->m_Priority;
    //}
}

void CPatternManager::DeleteEntities()
{
    for (;;)
    {
        auto entity = m_Entities.front();
        if (entity->m_Transform.GetPosition().m128_f32[2] < m_DeleteZone)
        {
            twWorld->RemoveEntity(entity);
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
        auto entity = twWorld->CreateEntity();
        entity->m_Transform.SetPosition(a_rPatternTile.m_X, 1.5f, m_PatternSpawnBegin + a_rPatternTile.m_Y);
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
        m_Entities.push_back(entity);
        break;
    }
    case ETileType::Block2x2:
    {
        auto entity = twWorld->CreateEntity();
        entity->m_Transform.SetPosition(a_rPatternTile.m_X, 0.0f, m_PatternSpawnBegin + a_rPatternTile.m_Y);
        entity->m_Transform.SetScale(2.0f, 1.0f, 2.0f);

        triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
        mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
        mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
        entity->SetDrawable(mesh);
        twWorld->AddEntity(entity);
        m_Entities.push_back(entity);
        break;
    }
    }
}
