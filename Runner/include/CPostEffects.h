#pragma once
#include <CEngine.h>

class CPostEffects : public triebWerk::IBehaviour
{
public:
    float m_ChromaticAberrationStrength;

private:
    triebWerk::CPostEffectDrawable* m_pPostEffect;
    triebWerk::CMaterial* m_pChromaticAberration;
    triebWerk::CMaterial* m_pRipple;
    triebWerk::CMaterial* m_pScanLines;

public:
    CPostEffects();
    ~CPostEffects();

    void Start() final;
    void Update() final;

private:
    void AddChromaticAberration();
    void AddRipple();
    void AddScanLines();
};