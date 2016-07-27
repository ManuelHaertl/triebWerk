#pragma once
#include <CEngine.h>

class CPoints : public triebWerk::IBehaviour
{
public:
    static int Points[3];

private:
    static DirectX::XMFLOAT3 Color[3];

    const float RotateSpeedZ = 130.0f;
    const float MinRotateSpeed = 15.0f;
    const float MaxRotateSpeed = 130.0f;
	const size_t PointCountWithGodray = 1;

    const size_t m_AmountID;

    float m_RotateSpeedX;
    float m_RotateSpeedY;
    float m_RotateSpeedZ;

    triebWerk::CEntity* m_pSphere;
	triebWerk::CEntity* m_pGodray;
	
	triebWerk::CConstantBuffer* m_pSphereBuffer;


public:
    CPoints(const size_t a_AmountID);
    ~CPoints();

    void Start();
    void Update();
    void End();

    void Collected();
    int GetPointAmount() const;

private:
    void CreateSphere();
	void CreateGodray();
};