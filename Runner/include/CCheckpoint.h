#pragma once
#include <CEngine.h>

class CCheckpoint : public triebWerk::IBehaviour
{
public:
    static float AddedMultiplier;
    static float HighestMultiplier;

    bool m_HasCollected;

public:
    CCheckpoint();
    ~CCheckpoint();

    void Start();
    void Update();
    void End();
};