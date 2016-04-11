#pragma once
#include <iostream>

#include <CEngine.h>

class CPlayer : public triebWerk::IBehaviour
{
public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;
    void End() final;
};