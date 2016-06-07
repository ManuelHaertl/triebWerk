#pragma once
#include <CEngine.h>
#include <SPlayerInput.h>

class CPlayer : public triebWerk::IBehaviour
{
public:
    static float FlySpeed;
    static float Acceleration;
    static float Drag;
    static float MaxSpeed;

    static float DodgeDistance;
    static float DodgeTime;
    static float DodgeCooldown;

    static float MaxRotation;
    static float RotationCameraFactor;

    static float RotationX;

    static float CameraRotationX;
    static float CameraPosY;
    static float CameraMinusPosZ;

private:
    bool m_IsDodging;
    float m_DodgeSpeed;
    float m_CurrentDodgeCooldownTime;
    float m_CurrentDodgeTime;

    triebWerk::CCamera* m_pMainCamera;
    SPlayerInput m_PlayerInput;

    bool m_IsDead;

    float m_MetersFlewn;
    float m_LastZ;

    // for testing (till we have an UI system)
    const float PointTellerTimer = 1.0f;
    float m_CurrentPointTellerTime = 0.0f;

public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;
    void LateUpdate() final;

    void CollisionEnter(triebWerk::CCollisionEvent a_Collision) final;
    void CollisionStay(triebWerk::CCollisionEvent a_Collision) final;

    void Reset();

    float GetMetersFlewn() const;
    bool HasDied() const;

private:
    void CheckInput();
    void SetSpeed();
    void CalculateDistanceFlewn();
    void AddPointsForFlewnDistance();
    void SetCamera();
    void SetRotation();
    void CheckSideWall(triebWerk::CCollisionEvent a_Collision);
};