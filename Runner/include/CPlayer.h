#pragma once
#include <iostream>
#include <CMeshDrawable.h>
#include <CEngine.h>

class CPlayer : public triebWerk::IBehaviour
{
private:
    float m_Rotation;

public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;

    void CollisionEnter(triebWerk::CCollisionEvent a_Collision) final;
};