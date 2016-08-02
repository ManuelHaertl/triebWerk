#pragma once
#include <CEngine.h>

class CPostEffects : public triebWerk::IBehaviour
{
public:
    static float ChromaticAberrationStrength;

    static float CheckpointEffectCollectedLength;
    static float CheckpointEffectPassedLength;

    static float FullControlEffectStrengthMin;
    static float FullControlEffectStrengthMax;
    static float BoostEffectStrength;
	static float ShieldEffectStrength;

    static float GameStartTime;
    static float GameStartLDEffectStrength;
    static float GameStartCAEffectStrength;
    static float GameStartRIBeginEffectStrength;
    static float GameStartRIEndEffectStrength;

private:
    triebWerk::CPostEffectDrawable* m_pPostEffect;
    triebWerk::CMaterial* m_pChromaticAberration;
    triebWerk::CMaterial* m_pRipple;
    triebWerk::CMaterial* m_pScanLines;
	triebWerk::CMaterial* m_pGrain;
    triebWerk::CMaterial* m_pShield;
    triebWerk::CMaterial* m_pBlur;
	triebWerk::CMaterial* m_pShockwave;

    static float m_CurrentGameStartTime;
    static float m_CurrentGameStartEffectStrength;
    float m_CurrentChromaticAberrationStrength;
    float m_CurrentDodgeTime;

	float m_CurrentEffectCheckpointValueCollected;
	float m_CurrentEffectCheckpointValuePassed;
	bool m_ProcessCheckpointEffectCollected;
	bool m_ProcessCheckpointEffectPassed;
	bool m_ProcessCheckpointEffectPassedCoolDown;

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
	void AddLensDistortion();
	void AddGrain();
	void AddShockwave();

    void UpdateGoingIntoGameEffect();
    void UpdateChromaticAberration();
	void UpdateLensDistortion();
	void UpdateGrainEffect();
    void UpdateBlur();
    void UpdateRipple();
	void UpdateShockwave();
};