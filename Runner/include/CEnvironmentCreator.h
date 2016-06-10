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

    // Ground Plane
    triebWerk::CEntity* m_pGround;

    // End Wall
    triebWerk::CEntity* m_pEndWall;

    // Snake Loop
    const float SnakeRotateSpeed1 = -3.0f;
    const float SnakeRotateSpeed2 = -2.0f;
    const float SnakeRotateSpeed3 = -1.0f;
    DirectX::XMVECTOR m_SnakeRotation1;
    DirectX::XMVECTOR m_SnakeRotation2;
    DirectX::XMVECTOR m_SnakeRotation3;
    triebWerk::CEntity* m_pSnake1;
    triebWerk::CEntity* m_pSnake2;
    triebWerk::CEntity* m_pSnake3;

public:
    CEnvironmentCreator();
    ~CEnvironmentCreator();

public:
    void Start();
    void Update(const float a_MetersFlewn);
    void End();

    void Reset();

private:
    void SpawnFeathers();
    void DeleteFeathers();
    void CreateFloor();
    void CreateCollisionSideWalls();
    void CreateGround();
    void CreateEndWall();
    void CreateSnakeLoops();
    void CheckFloorPosition(const float a_MetersFlewn);
    void RotateSnakes();
};