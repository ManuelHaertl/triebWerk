#pragma once
#include <CEngine.h>

class CCollectedPoint : public triebWerk::IBehaviour
{
private:
    const float Speed = 40.0f;
    const float ScaleValue = 1.0f;
    const float TimeAlive = 1.0f;

    float m_CurrentState;
    float m_CurrentScale;
    float m_AddedSpeed;
    float m_CurrentTime;

    triebWerk::CMeshDrawable* m_pMeshDrawable;

public:
    CCollectedPoint();
    ~CCollectedPoint();

    void Start();
    void Update();
    void End();
};