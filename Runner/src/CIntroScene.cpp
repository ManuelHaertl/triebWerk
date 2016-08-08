#include <CIntroScene.h>

#include <CGameScene.h>
#include <CDebugScene.h>
#include <CMenuScene.h>

CIntroScene::CIntroScene()
    : m_pGALogo(nullptr)
    , m_pTWLogo(nullptr)
    , m_HasShown(false)
    , m_HasLoaded(false)
    , m_HasShownGALogo(false)
    , m_CurrentTime(0.0f)
{
}

CIntroScene::~CIntroScene()
{
}

void CIntroScene::Start()
{
    twResourceManager->LoadSpecificFile("data\\Assets\\ui\\T_ui_ga_logo.png", false);
    twResourceManager->LoadSpecificFile("data\\Assets\\ui\\T_ui_engine_logo.png", false);
    twResourceManager->LoadSpecificFile("data\\Assets\\ui\\T_ui_black.png", false);
    twResourceManager->LoadSpecificFile("data\\Shader\\StandardUI.hlsl", false);
    twResourceManager->LoadSpecificFile("data\\Settings\\values.twf", false);

    twActiveUIWorld->SetReferenceResolution(1920, 1080.0f, triebWerk::CUIWorld::EScreenMatchState::Height);

    // Background

    auto background = twActiveUIWorld->CreateUIEntity();
    background->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    background->m_Transform.SetPositionOffset(0.0f, 0.0f, 1.0f);
    background->m_Transform.SetScale(100.0, 100.0, 0.0f);

    auto backgroundDrawable = twRenderer->CreateUIDrawable();
    backgroundDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    backgroundDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_black"));

    background->SetDrawable(backgroundDrawable);

    twActiveUIWorld->AddUIEntity(background);

    // Logo Games Academy

    m_pGALogo = twActiveUIWorld->CreateUIEntity();
    m_pGALogo->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pGALogo->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.0f);

    auto logoGADrawable = twRenderer->CreateUIDrawable();
    logoGADrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    logoGADrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_ga_logo"));

    m_pGALogo->SetDrawable(logoGADrawable);

    twActiveUIWorld->AddUIEntity(m_pGALogo);

    // Logo triebWerk

    m_pTWLogo = twActiveUIWorld->CreateUIEntity();
    m_pTWLogo->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pTWLogo->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.0f);

    auto logoTWDrawable = twRenderer->CreateUIDrawable();
    logoTWDrawable->SetActive(false);
    logoTWDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    logoTWDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_engine_logo"));

    m_pTWLogo->SetDrawable(logoTWDrawable);

    twActiveUIWorld->AddUIEntity(m_pTWLogo);
}

void CIntroScene::Update()
{
#ifdef _DEBUG
    twResourceManager->LoadAllFilesInFolder("data");
    twSceneManager->AddScene(new CGameScene(), "Game");
    twSceneManager->AddScene(new CMenuScene(), "Menu");
    //twSceneManager->AddScene(new CDebugScene(), "Debug");

    twSceneManager->SetActiveScene("Game");
    twSceneManager->SetActiveScene("Menu");
    return;
#endif // DEBUG

    if (!m_HasShown)
    {
        m_HasShown = true;
    }
    else if (!m_HasLoaded)
    {
        m_HasLoaded = true;
        twResourceManager->LoadAllFilesInFolder("data");
    }
    else if (!m_HasShownGALogo)
    {
        m_CurrentTime += twTime->GetDeltaTime();

        if (m_CurrentTime >= GALogoTime)
        {
            m_HasShownGALogo = true;
            m_CurrentTime = 0.0f;
            
            m_pGALogo->GetDrawable()->SetActive(false);
            m_pTWLogo->GetDrawable()->SetActive(true);
        }
    }
    else
    {
        m_CurrentTime += twTime->GetDeltaTime();

        if (m_CurrentTime >= TWLogoTime)
        {
            twSceneManager->AddScene(new CGameScene(), "Game");
            twSceneManager->AddScene(new CMenuScene(), "Menu");
            //twSceneManager->AddScene(new CDebugScene(), "Debug");

            twSceneManager->SetActiveScene("Game");
            twSceneManager->SetActiveScene("Menu");
        }
    }
}

void CIntroScene::End()
{
}
