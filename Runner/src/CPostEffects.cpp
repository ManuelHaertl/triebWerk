#include <CPostEffects.h>

#include <CGameInfo.h>

CPostEffects::CPostEffects()
    : m_pPostEffect(nullptr)
    , m_pChromaticAberration(nullptr)
    , m_pRipple(nullptr)
    , m_pScanLines(nullptr)
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
    AddRipple();
    AddScanLines();

    m_pEntity->SetDrawable(m_pPostEffect);
}

void CPostEffects::Update()
{
    UpdateCheckpointEffect();

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

void CPostEffects::UpdateCheckpointEffect()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    if (gameInfo.m_EffectDodge)
    {
        gameInfo.m_EffectDodge = false;
        m_CurrentDodgeTime = DodgeEffectLength;
    }

    m_CurrentDodgeTime -= twTime->GetDeltaTime();

    if (m_CurrentDodgeTime > 0)
    {
        float lerpValue = m_CurrentDodgeTime;
        float half = DodgeEffectLength / 2.0f;

        if (lerpValue > half)
            lerpValue = DodgeEffectLength - m_CurrentDodgeTime;

        m_CurrentChromaticAberrationStrength = (lerpValue / half) * DodgeEffectStrength;

        std::cout << "Lerp " << m_CurrentChromaticAberrationStrength << std::endl;
    }
    else
    {
        m_CurrentChromaticAberrationStrength = ChromaticAberrationStrength;
    }
}
