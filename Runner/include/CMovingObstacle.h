#pragma once
#include <CEngine.h>

class CMovingObstacle : public triebWerk::IBehaviour
{
private:
    const float PositionStart;
    const float PositionEnd;
    const float Time;
    const float Distance;

    bool m_Up;

    bool m_IsMoving;
    float m_UpDownValue;
    float m_Speed;
    float m_CurrentTime;

public:
    CMovingObstacle(const float a_PositionStart, const float a_PositionEnd, const float a_Time, const float a_Distance);
    ~CMovingObstacle();

    void Start() final;
    void Update() final;
    void End() final;
};