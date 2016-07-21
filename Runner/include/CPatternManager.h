#pragma once
#include <list>
#include <CPatternLoader.h>
#include <CPatternTileCreator.h>

class CPatternManager
{
public:
    static float SpawnDistance;
    static float DeleteDistance;
    static float StartFreeDistance;
    static float StartTextureBlendDistance;
    static float EndTextureBlendDistance;

private:
    std::list<triebWerk::CEntity*> m_Entities;
    std::vector<CPattern*> m_Pattern[CPattern::MaxDifficulty];
    CPatternTileCreator m_PatternTileCreator;

    float m_IsSpawned;
    float m_SpawnTo;
    float m_PatternSpawnBegin;
    float m_DeleteZone;
    float m_PlayerPosition;

    CPattern* m_pCurrentPattern;
    size_t m_CurrentTileIndex;


public:
    CPatternManager();
    ~CPatternManager();

    void Start();
    void Update(const float a_MetersFlewn);
    void End();

    void Reset();

private:
    void SpawnNextTile();
    void SetNextPattern();
    void DeleteEntities();
    //void SpawnPatternTile(const SPatternTile& a_rPatternTile);
    void SetRandomPattern(size_t a_Difficulty);
    void UpdateTextureBlending();
};