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

    // Grid Plane
    const float GridMoveDistance = 650.0f;
    const float GridLength = 1000.0f;

    float m_GridAllLength;
    float m_GridMoveZone;

    size_t m_GridCount;
    std::list<triebWerk::CEntity*> m_GridEntities;

    // Background
    triebWerk::CEntity* m_pBGPlane;
    triebWerk::CEntity* m_pBGSnake;
    triebWerk::CEntity* m_pBGBassLeft;
    triebWerk::CEntity* m_pBGBassRight;

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

    // Fog
    triebWerk::CElementContainer<triebWerk::CMeshDrawable*> m_Fogs;

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
    void CreateRoad();
    void CreateCollisionSideWalls();
    void CreateGrid();
    void CreateBackground();
    void CreateSnakeLoops();
    void CreateFog();
    void MoveRoad(const float a_MetersFlewn);
    void MoveGrid(const float a_MetersFlewn);
    void UpdateFog();
    void RotateSnakes();
};