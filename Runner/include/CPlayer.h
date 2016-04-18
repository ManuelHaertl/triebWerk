#pragma once
#include <iostream>

#include <CEngine.h>

class CPlayer : public triebWerk::IBehaviour
{
private:
	triebWerk::CCamera* m_pCam;
	float Rotation;
	float RotationY;
	DirectX::XMINT2 pos;
public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;
    void End() final;
};