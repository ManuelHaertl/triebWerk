#pragma once
#include <iostream>
#include <CMeshDrawable.h>
#include <CEngine.h>

class CPlayer : public triebWerk::IBehaviour
{
private:
    const float Acceleration = 800.0f;
    const float Drag = 250.0f;
    const float MaxSpeed = 30.0f;

    const float MaxRotation = 25.0f;
    const float RotationCameraFactor = 0.03f;

    const float DodgeSpeed = 50.0f;
    const float DodgeTime = 0.2f;
    const float DodgeCDTime = 0.5f;

    triebWerk::CCamera* m_pMainCamera;
    float m_CurrentMaxSpeedValue;

public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;
    void LateUpdate() final;

    void CollisionEnter(triebWerk::CCollisionEvent a_Collision) final;

private:
    void SetSpeed();
    void SetCamera();
    void SetRotation();
};