#pragma once
#include <list>
#include <CGameInfo.h>
#include <CPatternLoader.h>

class CPatternManager
{
private:
    const float SpawnDistance = 300.0f;
    const float DeleteDistance = 10.0f;

    std::list<triebWerk::CEntity*> m_Entities;

    std::vector<CPattern*> m_Pattern[CPattern::MaxDifficulty];

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
    void SetRandomPattern(size_t a_Difficulty);
};