#include <CManualMenu.h>

#include <CGameInfo.h>

CManualMenu::CManualMenu()
{
}

CManualMenu::~CManualMenu()
{
}

void CManualMenu::Start()
{
    // Background -------------------------------------------------

    m_pFieldBG = twActiveUIWorld->CreateUIEntity();
    m_pFieldBG->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pFieldBG->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.0f);

    auto fieldBGDrawable = twRenderer->CreateUIDrawable();
    fieldBGDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    fieldBGDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_bg"));

    m_pFieldBG->SetDrawable(fieldBGDrawable);

    twActiveUIWorld->AddUIEntity(m_pFieldBG);

    // Controls --------------------------------------------

    m_pControls = twActiveUIWorld->CreateUIEntity();
    m_pControls->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pControls->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto controlsDrawable = twRenderer->CreateUIDrawable();
    controlsDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    controlsDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_controller"));

    m_pControls->SetDrawable(controlsDrawable);

    twActiveUIWorld->AddUIEntity(m_pControls);
}

void CManualMenu::Update(const SUIInput& a_rInput)
{
    if (a_rInput.m_Back)
    {
        CGameInfo::Instance().m_ChangeMenu = true;
        CGameInfo::Instance().m_Menu = EMenus::Main;
        twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonBack"));
    }
}

void CManualMenu::End()
{
    twActiveUIWorld->RemoveUIEntity(m_pFieldBG);
    twActiveUIWorld->RemoveUIEntity(m_pControls);
}
