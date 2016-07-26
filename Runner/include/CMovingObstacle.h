#pragma once
#include <CEngine.h>

class CMovingObstacle : public triebWerk::IBehaviour
{
private:
    const DirectX::XMVECTOR PositionStart;
    const DirectX::XMVECTOR PositionEnd;
    const float Time;
    const float Distance;
    triebWerk::CEntity* m_pShadow;

    bool m_IsMoving;
    float m_CurrentTime;

public:
    CMovingObstacle(const DirectX::XMVECTOR a_PositionStart, const DirectX::XMVECTOR a_PositionEnd, const float a_Time, const float a_Distance, triebWerk::CEntity* a_pShadow);
    ~CMovingObstacle();

    void Start() final;
    void Update() final;
    void End() final;
};