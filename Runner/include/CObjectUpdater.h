#pragma once
#include <CEngine.h>
#define FogCount 40

class CObjectUpdater
{

public:
    triebWerk::CElementContainer<triebWerk::CEntity*> m_Fog;

private:
    triebWerk::CTWFData* m_pValues;

    triebWerk::CEntity* m_pSnake1;
    triebWerk::CEntity* m_pSnake2;
    triebWerk::CEntity* m_pSnake3;

    DirectX::XMVECTOR snake1Rotation = DirectX::XMVectorZero();
    DirectX::XMVECTOR snake2Rotation = DirectX::XMVectorZero();
    DirectX::XMVECTOR snake3Rotation = DirectX::XMVectorZero();
    size_t m_FogCount;

public:
    CObjectUpdater();
    ~CObjectUpdater();

    void Start(triebWerk::CEntity* a_pSnake1, triebWerk::CEntity* a_pSnake2, triebWerk::CEntity* a_pSnake3);
    void Update();

private:
    void UpdateValues();
    void RotateSnakes();
};