#pragma once
#include <list>
#include <CEngine.h>

class CEnvironmentCreator
{
public:
    static int FeatherSpawnProbability;

private:
    const float SpawnDistance = 300.0f;

    // Road
    const float RoadMoveDistance = 30.0f;
    const float RoadLength = 50.0f;

    float m_RoadAllLength;
    float m_RoadMoveZone;
    
    size_t m_RoadCount;
    std::list<triebWerk::CEntity*> m_RoadEntities;

    // Feathers
    const float FeathersDeleteDistance = 30.0f;
    const float FeathersLength = 50.0f;

    float m_FeathersIsSpawnedTo;
    float m_FeathersSpawnTo;
    float m_FeathersDeleteZone;
    std::list<triebWerk::CEntity*> m_FeathersEntities;

    // End Wall
    triebWerk::CEntity* m_pEndWall;

public:
    CEnvironmentCreator();
    ~CEnvironmentCreator();

public:
    void Start();
    void Update(const float a_MetersFlewn);
    void End();

private:
    void SpawnFeathers();
    void DeleteFeathers();
    void CreateFloor();
    void CreateCollisionSideWalls();
    void CreateEndWall();
    void CheckFloorPosition(const float a_MetersFlewn);
    void MoveEndWall(const float a_MetersFlewn);
};