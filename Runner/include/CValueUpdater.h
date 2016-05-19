#pragma once
#include <CEngine.h>

class CValueUpdater
{
private:
    triebWerk::CTWFData* m_pValues;
    triebWerk::CCamera* m_pMainCamera;

public:
    CValueUpdater();
    ~CValueUpdater();

    void Start();
    void Update();
    void End();

private:
    void UpdateValues();
};