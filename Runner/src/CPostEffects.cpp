#include <CPostEffects.h>

#include <CGameInfo.h>

CPostEffects::CPostEffects()
    : m_pPostEffect(nullptr)
    , m_pChromaticAberration(nullptr)
    , m_pRipple(nullptr)
    , m_pScanLines(nullptr)
	, m_pGrain(nullptr)
    , m_CurrentChromaticAberrationStrength(0.0f)
    , m_CurrentDodgeTime(0.0f)
	, m_ProcessCheckpointEffectCollected(false)
	, m_ProcessCheckpointEffectPassedCoolDown(false)
{
}

CPostEffects::~CPostEffects()
{
}

void CPostEffects::Start()
{
    m_pPostEffect = twRenderer->CreatePostEffecthDrawable();
	
	AddShockwave();
    AddChromaticAberration();
	AddBlur();
    AddRipple();
    AddScanLines();
	AddShieldEffect();
	AddGrain();

    m_pEntity->SetDrawable(m_pPostEffect);
}

void CPostEffects::Update()
{
    UpdateFullControlEffect();
	UpdateShieldEffect();
	UpdateGrainEffect();
    UpdateBlur();
	UpdateShockwave();
	UpdateChromaticAberration();
}

void CPostEffects::AddChromaticAberration()
{
    m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ChromaticAberration"));

    m_pChromaticAberration = m_pPostEffect->m_Materials[1];
    m_pChromaticAberration->m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(5, &m_CurrentChromaticAberrationStrength);
}

void CPostEffects::AddRipple()
{
	m_pRipple = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Ripple"));

}

void CPostEffects::AddScanLines()
{
    m_pScanLines = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));
}

void CPostEffects::AddShieldEffect()
{
	m_pShield = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("LensDistortion"));
	float lensStrenght = 0.0f;
	m_pShield->m_ConstantBuffer.SetValueInBuffer(4, &lensStrenght);
}

void CPostEffects::AddGrain()
{
	m_pGrain = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Grain"));
	float strength = 10.0f;
	m_pGrain->m_ConstantBuffer.SetValueInBuffer(5, &strength);
}

void CPostEffects::AddShockwave()
{
	m_pShockwave = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("CheckpointEffect"));
	float is = 1.0f;
	m_pShockwave->m_ConstantBuffer.SetValueInBuffer(5, &is);
}

void CPostEffects::AddBlur()
{
    m_pBlur = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("RadialBlur"));
    float strength = 00.0f;
    m_pBlur->m_ConstantBuffer.SetValueInBuffer(4, &strength);
}

void CPostEffects::UpdateFullControlEffect()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    if (gameInfo.m_EffectFullControl)
    {
        m_CurrentChromaticAberrationStrength = (FullControlEffectStrengthMax - FullControlEffectStrengthMin) * gameInfo.m_EffectFullControlStrength + FullControlEffectStrengthMin;
    }
    else
    {
        m_CurrentChromaticAberrationStrength = ChromaticAberrationStrength;
    }
}

void CPostEffects::UpdateShieldEffect()
{
    float value = 0.0f;

    if (CGameInfo::Instance().m_EffectShield)
        value = ShieldEffectStrength;

    m_pShield->m_ConstantBuffer.SetValueInBuffer(4, &value);
}

void CPostEffects::UpdateGrainEffect()
{
	float time = twTime->GetTimeSinceStartup();
	m_pGrain->m_ConstantBuffer.SetValueInBuffer(4, &time);
}

void CPostEffects::UpdateBlur()
{
    float strength = 0.0f;

    if (CGameInfo::Instance().m_EffectBoost)
        strength = BoostEffectStrength;

    m_pBlur->m_ConstantBuffer.SetValueInBuffer(4, &strength);
}

void CPostEffects::UpdateShockwave()
{
	//Collected ----
	if (CGameInfo::Instance().m_EffectCheckpointCollected)
	{
		m_ProcessCheckpointEffectCollected = true;
		CGameInfo::Instance().m_EffectCheckpointCollected = false;
		m_CurrentEffectCheckpointTime = 0.0f;

		float collected = 1.0f;
		m_pShockwave->m_ConstantBuffer.SetValueInBuffer(5, &collected);
	}

	if (m_ProcessCheckpointEffectCollected)
	{
		m_CurrentEffectCheckpointTime += twTime->GetDeltaTime() / 2;
		m_pShockwave->m_ConstantBuffer.SetValueInBuffer(4, &m_CurrentEffectCheckpointTime);

		if (m_CurrentEffectCheckpointTime > CheckpointEffectLength)
		{
			m_ProcessCheckpointEffectCollected = false;

			float restValue = 100.0f; //some high value so the scene has no distortion
			m_pShockwave->m_ConstantBuffer.SetValueInBuffer(4, &restValue);
			m_CurrentEffectCheckpointTime = 0.0f;
		}
	}

	//Passed ----
	if (CGameInfo::Instance().m_EffectCheckpointPassed)
	{
		m_ProcessCheckpointEffectPassed = true;
		CGameInfo::Instance().m_EffectCheckpointPassed = false;
		m_CurrentEffectCheckpointTime = 0.0f;

		float collected = 0.0f;
		m_pShockwave->m_ConstantBuffer.SetValueInBuffer(5, &collected);
	}

	if (m_ProcessCheckpointEffectPassed)
	{
		if(!m_ProcessCheckpointEffectPassedCoolDown)
			m_CurrentEffectCheckpointTime += twTime->GetDeltaTime();
		else
			m_CurrentEffectCheckpointTime -= twTime->GetDeltaTime();

		//float t = m_CurrentEffectCheckpointTime * pow(2, m_CurrentEffectCheckpointTime);
		m_pShockwave->m_ConstantBuffer.SetValueInBuffer(4, &m_CurrentEffectCheckpointTime);

		if (m_CurrentEffectCheckpointTime > CheckpointEffectLength / 1.2f)
			m_ProcessCheckpointEffectPassedCoolDown = true;

		if (m_CurrentEffectCheckpointTime < 0.0f)
		{
			m_ProcessCheckpointEffectPassed = false;

			float restValue = 0.0f;
			m_pShockwave->m_ConstantBuffer.SetValueInBuffer(4, &restValue);
			m_CurrentEffectCheckpointTime = 0.0f;
			m_ProcessCheckpointEffectPassedCoolDown = false;
		}

	}

}

void CPostEffects::UpdateChromaticAberration()
{
	float time = twTime->GetTimeSinceStartup();

	m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(4, &time);
	m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(5, &m_CurrentChromaticAberrationStrength);
}
