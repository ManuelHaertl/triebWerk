#include <CCreditsMenu.h>

#include <CGameInfo.h>

CCreditsMenu::CCreditsMenu()
{
}

CCreditsMenu::~CCreditsMenu()
{
}

void CCreditsMenu::Start()
{
    auto font = twFontManager->GetFont(twResourceManager->GetFontFace("AGENCYB"), 30);

    // Field BG -------------------------------------------------

    m_pFieldBG = twActiveUIWorld->CreateUIEntity();
    m_pFieldBG->m_Transform.SetAnchorPoint(0.0f, 0.0f);
    m_pFieldBG->m_Transform.SetPositionOffset(0.0f, 0.0f, 0.0f);

    auto fieldBGDrawable = twRenderer->CreateUIDrawable();
    fieldBGDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardUI"));
    fieldBGDrawable->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_ui_bg"));

    m_pFieldBG->SetDrawable(fieldBGDrawable);

    twActiveUIWorld->AddUIEntity(m_pFieldBG);

    // Manu -------------------------------------------------

    m_pManu = twActiveUIWorld->CreateUIEntity();
    m_pManu->m_Transform.SetAnchorPoint(-0.3f, 0.15f);
    m_pManu->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto manuText = twFontManager->CreateText();
    manuText->Set(font, "Manuel Haertl (Programmer)", 1.0f);
    manuText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

    auto manuTextDrawable = twRenderer->CreateFontDrawable();
    manuTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    manuTextDrawable->m_pText = manuText;
    manuTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pManu->SetDrawable(manuTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pManu);

    // Alex -------------------------------------------------

    m_pAlex = twActiveUIWorld->CreateUIEntity();
    m_pAlex->m_Transform.SetAnchorPoint(-0.3f, 0.05f);
    m_pAlex->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto alexText = twFontManager->CreateText();
    alexText->Set(font, "Alexander Klinger (Programmer)", 1.0f);
    alexText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

    auto alexTextDrawable = twRenderer->CreateFontDrawable();
    alexTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    alexTextDrawable->m_pText = alexText;
    alexTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pAlex->SetDrawable(alexTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pAlex);

    // Maren -------------------------------------------------

    m_pMaren = twActiveUIWorld->CreateUIEntity();
    m_pMaren->m_Transform.SetAnchorPoint(-0.3f, -0.05f);
    m_pMaren->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto marenText = twFontManager->CreateText();
    marenText->Set(font, "Maren Gerbach (Artist)", 1.0f);
    marenText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

    auto marenTextDrawable = twRenderer->CreateFontDrawable();
    marenTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    marenTextDrawable->m_pText = marenText;
    marenTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pMaren->SetDrawable(marenTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pMaren);

    // Pinar -------------------------------------------------

    m_pPinar = twActiveUIWorld->CreateUIEntity();
    m_pPinar->m_Transform.SetAnchorPoint(-0.3f, -0.15f);
    m_pPinar->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto pinarText = twFontManager->CreateText();
    pinarText->Set(font, "Pinar Dogru (Game Designer)", 1.0f);
    pinarText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);


    auto pinarTextDrawable = twRenderer->CreateFontDrawable();
    pinarTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    pinarTextDrawable->m_pText = pinarText;
    pinarTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

    m_pPinar->SetDrawable(pinarTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pPinar);
}

void CCreditsMenu::Update(const SUIInput& a_rInput)
{
    if (a_rInput.m_Back)
    {
        CGameInfo::Instance().m_ChangeMenu = true;
        CGameInfo::Instance().m_Menu = EMenus::Main;
    }
}

void CCreditsMenu::End()
{
    twActiveUIWorld->RemoveUIEntity(m_pFieldBG);
    twActiveUIWorld->RemoveUIEntity(m_pManu);
    twActiveUIWorld->RemoveUIEntity(m_pAlex);
    twActiveUIWorld->RemoveUIEntity(m_pMaren);
    twActiveUIWorld->RemoveUIEntity(m_pPinar);
}
