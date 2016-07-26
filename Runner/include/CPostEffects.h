#pragma once
#include <CEngine.h>

class CPostEffects : public triebWerk::IBehaviour
{
public:
    static float ChromaticAberrationStrength;

    static float CheckpointEffectLength;
    static float CheckpointEffectStrength;

    static float FullControlEffectStrengthMin;
    static float FullControlEffectStrengthMax;
    static float BoostEffectStrength;
	static float ShieldEffectStrength;

private:
    triebWerk::CPostEffectDrawable* m_pPostEffect;
    triebWerk::CMaterial* m_pChromaticAberration;
    triebWerk::CMaterial* m_pRipple;
    triebWerk::CMaterial* m_pScanLines;
	triebWerk::CMaterial* m_pGrain;
    triebWerk::CMaterial* m_pShield;
    triebWerk::CMaterial* m_pBlur;

    float m_CurrentChromaticAberrationStrength;
    float m_CurrentDodgeTime;

public:
    CPostEffects();
    ~CPostEffects();

    void Start() final;
    void Update() final;

private:
    void AddChromaticAberration();
	void AddBlur();
    void AddRipple();
    void AddScanLines();
	void AddShieldEffect();
	void AddGrain();

    void UpdateFullControlEffect();
	void UpdateShieldEffect();
	void UpdateGrainEffect();
    void UpdateBlur();
};