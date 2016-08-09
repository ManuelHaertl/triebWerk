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
    , m_CurrentTryAgainTime(0.0f)
    , m_CurrentTryAgainEffectStrength(0.0f)
    , m_CurrentChromaticAberrationStrength(0.0f)
    , m_CurrentDodgeTime(0.0f)
	, m_ProcessCheckpointEffectCollected(false)
	, m_ProcessCheckpointEffectPassedCoolDown(false)
	, m_ProcessCheckpointEffectPassed(false)
	, m_CurrentEffectCheckpointValueCollected(0.0f)
	, m_CurrentEffectCheckpointValuePassed(0.0f)
{
    
}

CPostEffects::~CPostEffects()
{
}

void CPostEffects::Start()
{
    m_pPostEffect = twRenderer->CreatePostEffecthDrawable();
	
	AddBloom();
	AddShockwave();
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
    UpdateTryAgainEffect();
    UpdateChromaticAberration();
	UpdateLensDistortion();
	UpdateGrainEffect();
    UpdateBlur();
    UpdateRipple();
	UpdateShockwave();
}

void CPostEffects::AddChromaticAberration()
{
	m_pChromaticAberration = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ChromaticAberration"));

    m_pChromaticAberration->m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(5, &m_CurrentChromaticAberrationStrength);
}

void CPostEffects::AddRipple()
{
    float value = 3.0f;
	m_pRipple = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Ripple"));
    m_pRipple->m_ConstantBuffer.SetValueInBuffer(5, &value);
}

void CPostEffects::AddScanLines()
{
    m_pScanLines = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));
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

void CPostEffects::AddShockwave()
{
	m_pShockwave = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("CheckpointEffect"));
	float temp = 100.0f;
	m_pShockwave->m_ConstantBuffer.SetValueInBuffer(4, &temp);
	temp = 0.0f;
	m_pShockwave->m_ConstantBuffer.SetValueInBuffer(5, &temp);
}

void CPostEffects::AddBloom()
{
	auto extract = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Extract"));
	

	auto blur = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Blur"));
		
	auto bloom = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Bloom"));
	bloom->m_pPixelShader.SetTexture(1, twRenderer->GetRenderTarget(0)->GetSceneTexture());
}

void CPostEffects::AddBlur()
{
    m_pBlur = m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("RadialBlur"));
    float strength = 0.0f;
    m_pBlur->m_ConstantBuffer.SetValueInBuffer(4, &strength);
	
	auto t = twResourceManager->GetTexture2D("t_blur_lookup");

	m_pBlur->m_pPixelShader.SetTexture(1, t);
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

void CPostEffects::UpdateTryAgainEffect()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    if (gameInfo.m_EffectTryAgain)
    {
        gameInfo.m_EffectTryAgain = false;
        m_CurrentTryAgainTime = TryAgainTime;
    }

    if (m_CurrentTryAgainTime > 0.0f)
    {
        m_CurrentTryAgainTime -= twTime->GetDeltaTime();

        float half = TryAgainTime / 2.0f;
        if (m_CurrentTryAgainTime > half)
        {
            float currentHalf = m_CurrentTryAgainTime - half;
            m_CurrentTryAgainEffectStrength = (half - currentHalf) / half;
        }
        else
        {
            m_CurrentTryAgainEffectStrength = ((m_CurrentTryAgainTime * 2) / TryAgainTime);
        }
    }
}

void CPostEffects::UpdateChromaticAberration()
{
    float value = 0.0f;
    CGameInfo& gameInfo = CGameInfo::Instance();

    if (m_CurrentGameStartTime > 0.0f)
        value = GameStartCAEffectStrength * m_CurrentGameStartEffectStrength;

    else if (gameInfo.m_EffectFullControl && !CGameInfo::Instance().m_IsGamePaused && !CGameInfo::Instance().m_IsPlayerDead)
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

    if (CGameInfo::Instance().m_EffectBoost && !CGameInfo::Instance().m_IsGamePaused && !CGameInfo::Instance().m_IsPlayerDead)
        strength = BoostEffectStrength;

    m_pBlur->m_ConstantBuffer.SetValueInBuffer(4, &strength);
}

void CPostEffects::UpdateRipple()
{
    float time = twTime->GetTimeSinceStartup();
    float strength = 5000.0f;

    if (m_CurrentGameStartTime > 0.0f)
    {
        float value = 1.0f - m_CurrentGameStartEffectStrength;
        strength = (GameStartRIBeginEffectStrength - GameStartRIEndEffectStrength) * value + GameStartRIEndEffectStrength;
    }
    else if (m_CurrentTryAgainTime > 0.0f)
    {
        float value = 1.0f - m_CurrentTryAgainEffectStrength;
        strength = (TryAgainRIBeginEffectStrength - TryAgainRIEndEffectStrength) * value + TryAgainRIEndEffectStrength;
    }

    m_pRipple->m_ConstantBuffer.SetValueInBuffer(4, &time);
    m_pRipple->m_ConstantBuffer.SetValueInBuffer(5, &strength);
}

void CPostEffects::UpdateShockwave()
{
	//Collected ----
	if (CGameInfo::Instance().m_EffectCheckpointCollected)
	{
		m_ProcessCheckpointEffectCollected = true;
		CGameInfo::Instance().m_EffectCheckpointCollected = false;
		m_CurrentEffectCheckpointValueCollected = 0.0f;
	}

	if (m_ProcessCheckpointEffectCollected)
	{
		m_CurrentEffectCheckpointValueCollected += twTime->GetDeltaTime() / 2;
		m_pShockwave->m_ConstantBuffer.SetValueInBuffer(4, &m_CurrentEffectCheckpointValueCollected);

		if (m_CurrentEffectCheckpointValueCollected > CheckpointEffectCollectedLength)
		{
			m_ProcessCheckpointEffectCollected = false;

			float restValue = 100.0f; //some high value so the scene has no distortion
			m_pShockwave->m_ConstantBuffer.SetValueInBuffer(4, &restValue);
			m_CurrentEffectCheckpointValueCollected = 0.0f;
		}
	}

	//Passed ----
	if (CGameInfo::Instance().m_EffectCheckpointPassed)
	{
		m_ProcessCheckpointEffectPassed = true;
		CGameInfo::Instance().m_EffectCheckpointPassed = false;
		m_CurrentEffectCheckpointValuePassed = 0.0f;
	}

	if (m_ProcessCheckpointEffectPassed)
	{
		if(!m_ProcessCheckpointEffectPassedCoolDown)
			m_CurrentEffectCheckpointValuePassed += twTime->GetDeltaTime();
		else
			m_CurrentEffectCheckpointValuePassed -= twTime->GetDeltaTime();

		//float t = m_CurrentEffectCheckpointTime * pow(2, m_CurrentEffectCheckpointTime);
		m_pShockwave->m_ConstantBuffer.SetValueInBuffer(5, &m_CurrentEffectCheckpointValuePassed);

		if (m_CurrentEffectCheckpointValuePassed > CheckpointEffectPassedLength / 1.2f)
			m_ProcessCheckpointEffectPassedCoolDown = true;

		if (m_CurrentEffectCheckpointValuePassed < 0.0f)
		{
			m_ProcessCheckpointEffectPassed = false;

			float restValue = 0.0f;
			m_pShockwave->m_ConstantBuffer.SetValueInBuffer(5, &restValue);
			m_CurrentEffectCheckpointValuePassed = 0.0f;
			m_ProcessCheckpointEffectPassedCoolDown = false;
		}

	}

}
