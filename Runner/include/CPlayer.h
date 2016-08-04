#pragma once
#include <CEngine.h>
#include <SPlayerInput.h>

class CPlayer : public triebWerk::IBehaviour
{
public:
    static float Acceleration;
    static float Drag;
    static float MaxSpeed;

    static float MaxResource;
    static float ResourcePerSecond;

    static float FullControlSpeed;
    static float FullControlCost;

    static float BoostSpeed;
    static float BoostCost;

    static float MaxRotation;
    static float RotationCameraFactor;

    static float RotationX;

    static float CameraRotationX;
    static float CameraPosY;
    static float CameraMinusPosZ;

    static int GodMode;

private:
    float m_CurrentResource;

    bool m_InFullControlMode;
    bool m_InBoostMode;

    triebWerk::CEntity* m_pTrail;
	triebWerk::CEntity* m_pDangerHitbox;
    triebWerk::CMeshDrawable* m_pTrailMesh;
    triebWerk::CCamera* m_pMainCamera;
    triebWerk::CTransform* m_pBackground;
	triebWerk::CMaterial* m_pFloorEffectMaterial;
    SPlayerInput m_PlayerInput;

    bool m_IsDead;

    float m_MetersFlewn;
    float m_LastZ;
	float m_LastX;

	DirectX::XMVECTOR m_FloorEffectLastPosition;
	float m_FloorEffectCounterRight;
	float m_FloorEffectCounterLeft;

public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;
    void LateUpdate() final;

    void CollisionEnter(triebWerk::CCollisionEvent a_Collision) final;
    void CollisionStay(triebWerk::CCollisionEvent a_Collision) final;

    void Reset();
    void SetBackground(triebWerk::CTransform* a_pBackground);

    float GetMetersFlewn() const;
    bool HasDied() const;

private:
    void CreateTrail();
	void CreateFloorEffect();
	void CreatePlayerDangerHitbox();
    void CheckInput();
    void CheckResource();
    void SetSpeed();
    void CalculateDistanceFlewn();
    void UpdateTrail();
	void UpdateFloorEffect();
    void SetCamera();
    void SetRotation();
    void CheckSideWall(triebWerk::CCollisionEvent a_Collision);
};