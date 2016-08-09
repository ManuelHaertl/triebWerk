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
    static float FullControlExtraTime;

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
    float m_CurrentFullControlExtraTime;

    bool m_InFullControlMode;
    bool m_InBoostMode;

	//Sound bools
	bool m_FullControlActivated;
	bool m_BoostActivated;
	bool m_FullResourcePlayed;
	bool m_NoResourcePlayed;

    triebWerk::CEntity* m_pTrail;
	float m_TrailBlend;

	triebWerk::CEntity* m_pDangerHitbox;
	triebWerk::CEntity* m_pFloorEffect;
    triebWerk::CMeshDrawable* m_pTrailMesh;
    triebWerk::CCamera* m_pMainCamera;
    triebWerk::CTransform* m_pBackground;
	triebWerk::CMaterial* m_pFloorEffectMaterial;
    SPlayerInput m_PlayerInput;

    float m_MetersFlewn;
    float m_LastZ;
	float m_LastX;

	DirectX::XMVECTOR m_FloorEffectLastPosition;
	float m_FloorEffectCounterRight;
	float m_FloorEffectCounterLeft;
	float m_DyingSpeed;
	float m_DyingCameraZ;

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

private:
    void CreateTrail();
	void CreateFloorEffect();
	void CreatePlayerDangerHitbox();
    void CheckInput();
    void CheckResource();
    void SetSpeed();
    void CalculateDistanceFlewn();
    void UpdateTrail();
	void UpdateDying();
	void UpdateFloorEffect();
    void SetCamera();
    void SetRotation();
    void CheckSideWall(triebWerk::CCollisionEvent a_Collision);
};