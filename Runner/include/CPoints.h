#pragma once
#include <CEngine.h>

class CPoints : public triebWerk::IBehaviour
{
public:
    int m_Points = 10;

private:
    const float RotateSpeed = 130.0f;

public:
    CPoints();
    ~CPoints();

    void Start();
    void Update();
    void End();
};