#pragma once
#include <list>
#include <CGameInfo.h>
#include <CPatternLoader.h>

class CPatternManager
{
private:
    const float SpawnDistance = 300.0f;
    const float DeleteDistance = 10.0f;

    const int DifficultyMinRange = 1;
    const int DifficultyMaxRange = 1;

    std::list<triebWerk::CEntity*> m_Entities;

    // all information about all pattern that can be spawned
    CPattern* m_pPattern;
    size_t m_PatternCount;
    int m_MinDifficulty;
    int m_MaxDifficulty;
    int m_MinPriority;
    int m_MaxPriority;

    float m_IsSpawned;
    float m_SpawnTo;
    float m_PatternSpawnBegin;
    float m_DeleteZone;

    CPattern* m_pCurrentPattern;
    size_t m_CurrentTileIndex;

public:
    CPatternManager();
    ~CPatternManager();

    void LoadPattern();
    void Update(const float a_MetersFlewn);

private:
    void SpawnNextTile();
    void SetNextPattern();
    void DeleteEntities();
    void SpawnPatternTile(const SPatternTile& a_rPatternTile);
};