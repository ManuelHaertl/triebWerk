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
	, m_CurrentShieldTime(0.0f)
{
}

CPostEffects::~CPostEffects()
{
}

void CPostEffects::Start()
{
    m_pPostEffect = twRenderer->CreatePostEffecthDrawable();

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
    UpdateCheckpointEffect();
	UpdateShieldEffect();
	UpdateGrainEffect();
    UpdateBlur();

    float time = twTime->GetTimeSinceStartup();

    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(4, &time);
    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(5, &m_CurrentChromaticAberrationStrength);
}

void CPostEffects::AddChromaticAberration()
{
    m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ChromaticAberration"));

    m_pChromaticAberration = m_pPostEffect->m_Materials[0];
    m_pChromaticAberration->m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(5, &m_CurrentChromaticAberrationStrength);
}

void CPostEffects::AddRipple()
{
    m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Ripple"));

    m_pRipple = m_pPostEffect->m_Materials[1];
}

void CPostEffects::AddScanLines()
{
    m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));

    m_pRipple = m_pPostEffect->m_Materials[2];
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

void CPostEffects::AddBlur()
{
    m_pBlur = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("RadialBlur"));
    float strength = 00.0f;
    m_pBlur->m_ConstantBuffer.SetValueInBuffer(4, &strength);
}

void CPostEffects::UpdateCheckpointEffect()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    if (gameInfo.m_EffectDodge)
    {

        m_CurrentChromaticAberrationStrength = (DodgeEffectStrengthMax - DodgeEffectStrengthMin) * gameInfo.m_EffectDodgeStrength + DodgeEffectStrengthMin;
    }
    else
    {
        m_CurrentChromaticAberrationStrength = ChromaticAberrationStrength;
    }

    //m_CurrentDodgeTime -= twTime->GetDeltaTime();

    //if (m_CurrentDodgeTime > 0)
    //{
    //    float lerpValue = m_CurrentDodgeTime;
    //    float half = DodgeEffectLength / 2.0f;

    //    if (lerpValue > half)
    //        lerpValue = DodgeEffectLength - m_CurrentDodgeTime;

    //    m_CurrentChromaticAberrationStrength = (lerpValue / half) * DodgeEffectStrength;

    //    std::cout << "Lerp " << m_CurrentChromaticAberrationStrength << std::endl;
    //}
    //else
    //{
    //    m_CurrentChromaticAberrationStrength = ChromaticAberrationStrength;
    //}
}

void CPostEffects::UpdateShieldEffect()
{
	CGameInfo& gameInfo = CGameInfo::Instance();
	if (gameInfo.m_EffectShield)
	{
		gameInfo.m_EffectShield = false;
		m_CurrentShieldTime = ShieldEffectLength;
	}
	float lensStrenght = 0.0f;

	m_CurrentShieldTime -= twTime->GetDeltaTime();

	if (m_CurrentShieldTime > 0)
	{
		float lerpValue = m_CurrentShieldTime;
		float half = ShieldEffectLength / 2.0f;

		if (lerpValue > half)
			lerpValue = ShieldEffectLength - m_CurrentShieldTime;

		lensStrenght = (lerpValue / half) * ShieldEffectStrength;

		std::cout << "Lerp " << m_CurrentChromaticAberrationStrength << std::endl;
	}
	else
	{
		lensStrenght = 0.0f;
	}

	m_pShield->m_ConstantBuffer.SetValueInBuffer(4, &lensStrenght);
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
