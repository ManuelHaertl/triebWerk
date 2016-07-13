#pragma once
#include <CEngine.h>
#include <SPlayerInput.h>

class CPlayer : public triebWerk::IBehaviour
{
public:
    static float Acceleration;
    static float Drag;
    static float MaxSpeed;

    static float DodgeDistance;
    static float DodgeTime;
    static float DodgeCooldown;

    static float ShieldTime;
    static float ShieldCooldown;

    static float MaxRotation;
    static float RotationCameraFactor;

    static float RotationX;

    static float CameraRotationX;
    static float CameraPosY;
    static float CameraMinusPosZ;

    static int GodMode;

private:
    bool m_IsDodging;
    float m_DodgeSpeed;
    float m_CurrentDodgeTime;
    float m_CurrentDodgeCooldownTime;

    bool m_IsShieldActive;
    float m_CurrentShieldTime;
    float m_CurrentShieldCooldownTime;

    triebWerk::CEntity* m_pTrail;
    triebWerk::CMeshDrawable* m_pTrailMesh;
    triebWerk::CCamera* m_pMainCamera;
    SPlayerInput m_PlayerInput;

    bool m_IsDead;

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

    void Reset();

    float GetMetersFlewn() const;
    bool HasDied() const;

private:
    void CreateTrail();
    void CheckInput();
    void SetSpeed();
    void SetShield();
    void CalculateDistanceFlewn();
    void AddPointsForFlewnDistance();
    void UpdateTrail();
    void SetCamera();
    void SetRotation();
    void CheckSideWall(triebWerk::CCollisionEvent a_Collision);
};