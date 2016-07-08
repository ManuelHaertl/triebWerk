#include <CPostEffects.h>

CPostEffects::CPostEffects()
    : m_ChromaticAberrationStrength(0.6f)
    , m_pPostEffect(nullptr)
    , m_pChromaticAberration(nullptr)
    , m_pRipple(nullptr)
    , m_pScanLines(nullptr)
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
    float time = twTime->GetTimeSinceStartup();

    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(4, &time);
    //m_pRipple->m_ConstantBuffer.SetValueInBuffer(4, &time);
}

void CPostEffects::AddChromaticAberration()
{
    m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ChromaticAberration"));

    m_pChromaticAberration = &m_pPostEffect->m_Materials[0];
    m_pChromaticAberration->m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
    m_pChromaticAberration->m_ConstantBuffer.SetValueInBuffer(5, &m_ChromaticAberrationStrength);
}

void CPostEffects::AddRipple()
{
    m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("Ripple"));

    m_pRipple = &m_pPostEffect->m_Materials[1];
}

void CPostEffects::AddScanLines()
{
    m_pPostEffect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));

    m_pRipple = &m_pPostEffect->m_Materials[2];
}
