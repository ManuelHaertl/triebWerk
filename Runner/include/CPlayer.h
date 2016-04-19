#pragma once
#include <iostream>

#include <CEngine.h>

class CPlayer : public triebWerk::IBehaviour
{
private:
public:
    CPlayer();
    ~CPlayer();

    void Start() final;
    void Update() final;
    void End() final;
};