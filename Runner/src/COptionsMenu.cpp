#include <COptionsMenu.h>

#include <CGameInfo.h>

COptionsMenu::COptionsMenu()
{
}

COptionsMenu::~COptionsMenu()
{
}

void COptionsMenu::Start()
{
    // Field BG -------------------------------------------------

    m_pFieldBG = twActiveUIWorld->CreateUIEntity();
    m_pFieldBG->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pFieldBG->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.0f);

    auto fieldBGDrawable = twRenderer->CreateUIDrawable();
    fieldBGDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    fieldBGDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_bg"));

    m_pFieldBG->SetDrawable(fieldBGDrawable);

    twActiveUIWorld->AddUIEntity(m_pFieldBG);
}

void COptionsMenu::Update(const SUIInput& a_rInput)
{
    if (a_rInput.m_Back)
    {
        CGameInfo::Instance().m_ChangeMenu = true;
        CGameInfo::Instance().m_Menu = EMenus::Main;
    }
}

void COptionsMenu::End()
{
    twActiveUIWorld->RemoveUIEntity(m_pFieldBG);
}
