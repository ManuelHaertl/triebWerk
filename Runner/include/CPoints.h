#pragma once
#include <CEngine.h>

class CPoints : public triebWerk::IBehaviour
{
public:
    int m_Points = 10;

private:
    const float RotateSpeedZ = 130.0f;
    const float MinRotateSpeed = 15.0f;
    const float MaxRotateSpeed = 130.0f;

    float m_RotateSpeedX;
    float m_RotateSpeedY;
    float m_RotateSpeedZ;

    triebWerk::CEntity* m_pSphere;
    triebWerk::CConstantBuffer* m_pSphereBuffer;

public:
    CPoints();
    ~CPoints();

    void Start();
    void Update();
    void End();

    void Collected();

private:
    void CreateSphere();
};