#pragma once
#include <iostream>
#include <CMeshDrawable.h>
#include <CEngine.h>

class CPlayer : public triebWerk::IBehaviour
{
private:
    const float FlySpeed = 75.0f;

    const float Acceleration = 250.0f;
    const float Drag = 150.0f;
    const float MaxSpeed = 30.0f;

    const float MaxRotation = 25.0f;
    const float RotationCameraFactor = 0.03f;

    triebWerk::CCamera* m_pMainCamera;
    float m_CurrentMaxSpeedValue;

    float m_MetersFlewn;
    float m_LastZ;

public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;
    void LateUpdate() final;

    void CollisionEnter(triebWerk::CCollisionEvent a_Collision) final;
    void CollisionStay(triebWerk::CCollisionEvent a_Collision) final;

    float GetMetersFlewn() const;

private:
    void SetSpeed();
    void SetCamera();
    void SetRotation();
    void CheckSideWall(triebWerk::CCollisionEvent a_Collision);
};