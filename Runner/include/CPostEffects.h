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

	static float ShieldEffectLength;
	static float ShieldEffectStrength;

private:
    triebWerk::CPostEffectDrawable* m_pPostEffect;
    triebWerk::CMaterial* m_pChromaticAberration;
    triebWerk::CMaterial* m_pRipple;
    triebWerk::CMaterial* m_pScanLines;
	triebWerk::CMaterial* m_pGrain;
	triebWerk::CMaterial* m_pShield;

    float m_CurrentChromaticAberrationStrength;
    float m_CurrentDodgeTime;
	float m_CurrentShieldTime;

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

    void UpdateCheckpointEffect();
	void UpdateShieldEffect();
	void UpdateGrainEffect();
};