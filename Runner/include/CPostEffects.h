#pragma once
#include <CEngine.h>

class CPostEffects : public triebWerk::IBehaviour
{
public:
    static float ChromaticAberrationStrength;

    static float CheckpointEffectLength;
    static float CheckpointEffectStrength;

    static float DodgeEffectStrength;
    static float DodgeEffectLength;

private:
    triebWerk::CPostEffectDrawable* m_pPostEffect;
    triebWerk::CMaterial* m_pChromaticAberration;
    triebWerk::CMaterial* m_pRipple;
    triebWerk::CMaterial* m_pScanLines;

    float m_CurrentChromaticAberrationStrength;
    float m_CurrentDodgeTime;

public:
    CPostEffects();
    ~CPostEffects();

    void Start() final;
    void Update() final;

private:
    void AddChromaticAberration();
    void AddRipple();
    void AddScanLines();
    void UpdateCheckpointEffect();
};