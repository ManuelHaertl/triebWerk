#pragma once
#include <list>
#include <CEngine.h>
#include <CObjectUpdater.h>

class CEnvironmentCreator
{
public:
    static int FeatherSpawnProbability;
    static float SnakeRotateSpeed1;
    static float SnakeRotateSpeed2;
    static float SnakeRotateSpeed3;

private:
    CObjectUpdater m_ObjectUpdater;

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
    const float BGPlaneDistanceZ = 500.0f;
    triebWerk::CEntity* m_pBGPlane;

    // Snake Loop
    DirectX::XMVECTOR m_SnakeRotation1;
    DirectX::XMVECTOR m_SnakeRotation2;
    DirectX::XMVECTOR m_SnakeRotation3;
    triebWerk::CEntity* m_pSnake1;
    triebWerk::CEntity* m_pSnake2;
    triebWerk::CEntity* m_pSnake3;
	triebWerk::CEntity* m_pRoadBorder;
	triebWerk::CEntity* m_pParticleSpawner;
	triebWerk::CEntity* m_pBlackGround;

    // Fog
    triebWerk::CElementContainer<triebWerk::CEntity*> m_Fogs;

public:
    CEnvironmentCreator();
    ~CEnvironmentCreator();

public:
    void Start();
    void Update(const float a_MetersFlewn);
    void End();

    void Reset();
    triebWerk::CTransform* GetBackground();

private:
    void SpawnFeathers();
    void DeleteFeathers();
    void CreateRoad();
    void CreateCollisionSideWalls();
    void CreateGrid();
	void CreateBlackGround();
    void CreateBackground();
    void CreateSnakeLoops();
    void CreateFog();
	void CreateRoadBorder();
	void CreateParticleSpawner();
    void MoveBackground();
    void MoveRoad(const float a_MetersFlewn);
    void MoveGrid(const float a_MetersFlewn);
    void UpdateFog();
	void UpdateFeathers();
    void RotateSnakes();
};