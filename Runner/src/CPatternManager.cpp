#include <CPatternManager.h>

#include <CCheckpoint.h>
#include <CGameInfo.h>
#include <CPoints.h>

CPatternManager::CPatternManager() :
    m_IsSpawned(0.0f),
    m_SpawnTo(SpawnDistance),
    m_PatternSpawnBegin(StartFreeDistance),
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

    twTime->ResetDeltaTime();
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
    UpdateTextureBlending();
}

void CPatternManager::End()
{
    // reset values
    m_IsSpawned = 0.0f;
    m_SpawnTo = SpawnDistance;
    m_PatternSpawnBegin = StartFreeDistance;
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

void CPatternManager::Reset()
{
    m_IsSpawned = 0.0f;
    m_SpawnTo = SpawnDistance;
    m_PatternSpawnBegin = StartFreeDistance;
    m_pCurrentPattern = nullptr;
    m_CurrentTileIndex = 0;
    m_DeleteZone = -DeleteDistance;

    size_t size = m_Entities.size();
    for (size_t i = 0; i < size; ++i)
    {
        auto entity = m_Entities.front();
        twActiveWorld->RemoveEntity(entity);
        m_Entities.erase(m_Entities.begin());
    }

    SetRandomPattern(0);
    twTime->ResetDeltaTime();
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
    m_PatternTileCreator.CreateEntity(patternTile, m_PatternSpawnBegin);

    size_t size = m_PatternTileCreator.m_Entities.size();
    for (size_t i = 0; i < size; ++i)
    {
        auto entity = m_PatternTileCreator.m_Entities[i];
        
        // For Debug purpose
        if (entity->m_Tag.HasTag("Death"))
            entity->m_ID.SetDescribtion("Died in Pattern: " + m_pCurrentPattern->m_Name + " Difficulty:  " + std::to_string(m_pCurrentPattern->m_Difficulty) + " Priority: " + std::to_string(m_pCurrentPattern->m_Priority));
    
        m_Entities.push_back(entity);
    }

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

    auto color = triebWerk::CDebugLogfile::ELogType::Text;
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
            m_Entities.remove(entity);
        }
        else
        {
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

void CPatternManager::UpdateTextureBlending()
{
    for (auto entity : m_Entities)
    {
        if (entity->m_Tag.HasTag("WallEffect"))
        {
            float blend1 = 1.0f, blend2 = 0.0f, blend3 = 0.0f;
            auto drawable = static_cast<triebWerk::CMeshDrawable*>(entity->GetDrawable());

            float distance = entity->m_Transform.GetPosition().m128_f32[2] - CGameInfo::Instance().m_PlayerPosition;

            if (distance < EndTextureBlendDistance)
            {
                blend1 = 0.0f;
                blend3 = 1.0f;
            }
            else if (distance < StartTextureBlendDistance)
            {
                float blendDistance = StartTextureBlendDistance - EndTextureBlendDistance;
                float blendDistanceHalf = blendDistance / 2.0f;
                float currentDistance = distance - EndTextureBlendDistance;

                if (currentDistance > blendDistanceHalf)
                {
                    blend1 = (distance - EndTextureBlendDistance - blendDistanceHalf) / blendDistanceHalf;
                    blend2 = 1.0f - blend1;
                    blend3 = 0.0f;
                }
                else
                {
                    blend1 = 0.0f;
                    blend2 = (distance - EndTextureBlendDistance) / blendDistanceHalf;
                    blend3 = 1.0f - blend2;
                }
            }

            drawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &blend1);
            drawable->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &blend2);
            drawable->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &blend3);

			if (distance < EndBuildDistance)
			{
				float buildDistance = 0.0f;
				drawable->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &buildDistance);
			}
			else if (distance <= StartBuildDistance)
			{
				float buildDistance = (distance - EndBuildDistance) / 10;
				drawable->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &buildDistance);

			}
        }
    }
}
