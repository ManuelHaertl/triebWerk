#include <CPostEffects.h>

#include <CGameInfo.h>

float CPostEffects::m_CurrentGameStartTime = 0.0f;
float CPostEffects::m_CurrentGameStartEffectStrength = 0.0f;

CPostEffects::CPostEffects()
    : m_pPostEffect(nullptr)
    , m_pChromaticAberration(nullptr)
    , m_pRipple(nullptr)
    , m_pScanLines(nullptr)
	, m_pGrain(nullptr)
    , m_CurrentChromaticAberrationStrength(0.0f)
    , m_CurrentDodgeTime(0.0f)
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
	AddLensDistortion();
	AddGrain();
    
    m_pEntity->SetDrawable(m_pPostEffect);
}

void CPostEffects::Update()
{
    UpdateGoingIntoGameEffect();
    UpdateChromaticAberration();
	UpdateLensDistortion();
	UpdateGrainEffect();
    UpdateBlur();
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

void CPostEffects::AddLensDistortion()
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
    float strength = 0.0f;
    m_pBlur->m_ConstantBuffer.SetValueInBuffer(4, &strength);
}

void CPostEffects::UpdateGoingIntoGameEffect()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    if (gameInfo.m_EffectGoingIntoGame)
    {
        gameInfo.m_EffectGoingIntoGame = false;
        m_CurrentGameStartTime = GameStartTime;
    }

    if (m_CurrentGameStartTime > 0.0f)
    {
        m_CurrentGameStartTime -= twTime->GetDeltaTime();

        float half = GameStartTime / 2.0f;
        if (m_CurrentGameStartTime > half)
        {
            float currentHalf = m_CurrentGameStartTime - half;
            m_CurrentGameStartEffectStrength = (half - currentHalf) / half;
        }
        else
        {
            m_CurrentGameStartEffectStrength = ((m_CurrentGameStartTime * 2) / GameStartTime);
        }
    }
}

void CPostEffects::UpdateChromaticAberration()
{
    float value = 0.0f;
    CGameInfo& gameInfo = CGameInfo::Instance();

    if (m_CurrentGameStartTime > 0.0f)
        value = GameStartCAEffectStrength * m_CurrentGameStartEffectStrength;

    else if (gameInfo.m_EffectFullControl)
        value = (FullControlEffectStrengthMax - FullControlEffectStrengthMin) * gameInfo.m_EffectFullControlStrength + FullControlEffectStrengthMin;

    else
        value = ChromaticAberrationStrength;

    float time = twTime->GetTimeSinceStartup();

    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(4, &time);
    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(5, &value);
}

void CPostEffects::UpdateLensDistortion()
{
    float value = 0.0f;

    if (m_CurrentGameStartTime > 0.0f)
    {
        value = GameStartLDEffectStrength * m_CurrentGameStartEffectStrength;
    }
    else
    {
        if (CGameInfo::Instance().m_EffectShield)
            value = ShieldEffectStrength;
    }

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

void CPostEffects::UpdateGameStartEffect()
{
}
