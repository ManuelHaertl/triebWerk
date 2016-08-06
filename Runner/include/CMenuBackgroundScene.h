#pragma once
#include <CEngine.h>

class CMenuBackgroundScene
{
private:
    triebWerk::CCamera* m_pCamera;

    // Snakes
    const float SnakeRotateSpeed1 = -3.0f;
    const float SnakeRotateSpeed2 = -2.0f;
    const float SnakeRotateSpeed3 = -1.0f;
    DirectX::XMVECTOR m_SnakeRotation1;
    DirectX::XMVECTOR m_SnakeRotation2;
    DirectX::XMVECTOR m_SnakeRotation3;
    triebWerk::CEntity* m_pSnake1;
    triebWerk::CEntity* m_pSnake2;
    triebWerk::CEntity* m_pSnake3;

	std::list<triebWerk::CConstantBuffer*> m_FeathersBuffers;

public:
    CMenuBackgroundScene();
    ~CMenuBackgroundScene();

    void Start();
    void Update();
    void End();

private:
    void CreateRoad();
    void CreateGrid();
    void CreateBackground();
    void CreateSnakeLoops();
    void CreateFeathers();
};