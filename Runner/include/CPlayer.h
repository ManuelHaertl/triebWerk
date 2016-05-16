#pragma once
#include <iostream>
#include <CMeshDrawable.h>
#include <CEngine.h>

class CPlayer : public triebWerk::IBehaviour
{
public:
    static float FlySpeed;
    static float Acceleration;
    static float Drag;
    static float MaxSpeed;

    static float MaxRotation;
    static float RotationCameraFactor;

private:

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