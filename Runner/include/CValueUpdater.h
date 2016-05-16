#pragma once
#include <CEngine.h>

class CValueUpdater
{
private:
    triebWerk::CTWFData* m_pValues;

public:
    CValueUpdater();
    ~CValueUpdater();

    void Start();
    void Update();
    void End();
};