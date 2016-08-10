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

    // Alex -------------------------------------------------

    m_pAlex = twActiveUIWorld->CreateUIEntity();
    m_pAlex->m_Transform.SetAnchorPoint(-0.05f, 0.15f);
    m_pAlex->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto alexText = twFontManager->CreateText();
    alexText->Set(font, "Alexander Klinger", 1.0f);
    alexText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto alexTextDrawable = twRenderer->CreateFontDrawable();
    alexTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    alexTextDrawable->m_pText = alexText;
    alexTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pAlex->SetDrawable(alexTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pAlex);

    // Alex Title -------------------------------------------------

    m_pAlexTitle = twActiveUIWorld->CreateUIEntity();
    m_pAlexTitle->m_Transform.SetAnchorPoint(0.05f, 0.15f);
    m_pAlexTitle->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto alexTitleText = twFontManager->CreateText();
    alexTitleText->Set(font, "Programming", 1.0f);
    alexTitleText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

    auto alexTitleTextDrawable = twRenderer->CreateFontDrawable();
    alexTitleTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    alexTitleTextDrawable->m_pText = alexTitleText;
    alexTitleTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pAlexTitle->SetDrawable(alexTitleTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pAlexTitle);

    // Manu -------------------------------------------------

    m_pManu = twActiveUIWorld->CreateUIEntity();
    m_pManu->m_Transform.SetAnchorPoint(-0.05f, 0.05f);
    m_pManu->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto manuText = twFontManager->CreateText();
    manuText->Set(font, "Manuel Haertl", 1.0f);
    manuText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto manuTextDrawable = twRenderer->CreateFontDrawable();
    manuTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    manuTextDrawable->m_pText = manuText;
    manuTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pManu->SetDrawable(manuTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pManu);

    // Manu Title -------------------------------------------------

    m_pManuTitle = twActiveUIWorld->CreateUIEntity();
    m_pManuTitle->m_Transform.SetAnchorPoint(0.05f, 0.05f);
    m_pManuTitle->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto manuTitleText = twFontManager->CreateText();
    manuTitleText->Set(font, "Programming", 1.0f);
    manuTitleText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

    auto manuTitleTextDrawable = twRenderer->CreateFontDrawable();
    manuTitleTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    manuTitleTextDrawable->m_pText = manuTitleText;
    manuTitleTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pManuTitle->SetDrawable(manuTitleTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pManuTitle);

    // Maren -------------------------------------------------

    m_pMaren = twActiveUIWorld->CreateUIEntity();
    m_pMaren->m_Transform.SetAnchorPoint(-0.05f, -0.05f);
    m_pMaren->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto marenText = twFontManager->CreateText();
    marenText->Set(font, "Maren Gerbach", 1.0f);
    marenText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

    auto marenTextDrawable = twRenderer->CreateFontDrawable();
    marenTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    marenTextDrawable->m_pText = marenText;
    marenTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pMaren->SetDrawable(marenTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pMaren);

    // Maren Title -------------------------------------------------

    m_pMarenTitle = twActiveUIWorld->CreateUIEntity();
    m_pMarenTitle->m_Transform.SetAnchorPoint(0.05f, -0.05f);
    m_pMarenTitle->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto marenTitleText = twFontManager->CreateText();
    marenTitleText->Set(font, "Art", 1.0f);
    marenTitleText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

    auto marenTitleTextDrawable = twRenderer->CreateFontDrawable();
    marenTitleTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    marenTitleTextDrawable->m_pText = marenTitleText;
    marenTitleTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pMarenTitle->SetDrawable(marenTitleTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pMarenTitle);

    // Pinar -------------------------------------------------

    m_pPinar = twActiveUIWorld->CreateUIEntity();
    m_pPinar->m_Transform.SetAnchorPoint(-0.05f, -0.15f);
    m_pPinar->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto pinarText = twFontManager->CreateText();
    pinarText->Set(font, "Pinar Dogru", 1.0f);
    pinarText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);


    auto pinarTextDrawable = twRenderer->CreateFontDrawable();
    pinarTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    pinarTextDrawable->m_pText = pinarText;
    pinarTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pPinar->SetDrawable(pinarTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pPinar);

    // Pinar Title -------------------------------------------------

    m_pPinarTitle = twActiveUIWorld->CreateUIEntity();
    m_pPinarTitle->m_Transform.SetAnchorPoint(0.05f, -0.15f);
    m_pPinarTitle->m_Transform.SetPositionOffset(0.0f, 0.0f, -0.1f);

    auto pinarTitleText = twFontManager->CreateText();
    pinarTitleText->Set(font, "Design", 1.0f);
    pinarTitleText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

    auto pinarTitleTextDrawable = twRenderer->CreateFontDrawable();
    pinarTitleTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
    pinarTitleTextDrawable->m_pText = pinarTitleText;
    pinarTitleTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    m_pPinarTitle->SetDrawable(pinarTitleTextDrawable);
    twActiveUIWorld->AddUIEntity(m_pPinarTitle);
}

void CCreditsMenu::Update(const SUIInput& a_rInput)
{
    if (a_rInput.m_Back)
    {
        CGameInfo::Instance().m_ChangeMenu = true;
        CGameInfo::Instance().m_Menu = EMenus::Main;
        twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonBack"));
    }
}

void CCreditsMenu::End()
{
    twActiveUIWorld->RemoveUIEntity(m_pFieldBG);
    twActiveUIWorld->RemoveUIEntity(m_pManu);
    twActiveUIWorld->RemoveUIEntity(m_pAlex);
    twActiveUIWorld->RemoveUIEntity(m_pMaren);
    twActiveUIWorld->RemoveUIEntity(m_pPinar);
    twActiveUIWorld->RemoveUIEntity(m_pManuTitle);
    twActiveUIWorld->RemoveUIEntity(m_pAlexTitle);
    twActiveUIWorld->RemoveUIEntity(m_pMarenTitle);
    twActiveUIWorld->RemoveUIEntity(m_pPinarTitle);
}
