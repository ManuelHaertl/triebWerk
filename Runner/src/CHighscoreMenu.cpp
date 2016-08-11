#include <CHighscoreMenu.h>

#include <CGameInfo.h>

CHighscoreMenu::CHighscoreMenu()
{
}

CHighscoreMenu::~CHighscoreMenu()
{
}

void CHighscoreMenu::Start()
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

    // Scores ----------------------------------------------------------

    auto font = twFontManager->GetFont(twResourceManager->GetFontFace("AGENCYB"), 30);

	for (size_t i = 0; i < 5; i++)
	{
		std::string text = std::to_string((i + 1)) + ".";

		m_pNumbers[i] = twActiveUIWorld->CreateUIEntity();
		m_pNumbers[i]->m_Transform.SetAnchorPoint(-0.35f, (0.1f - ((float)i * 0.1f)));
		if (i == 0)
			m_pNumbers[i]->m_Transform.SetPositionOffset(3.0f, -11.0f, -0.1f);
		else
			m_pNumbers[i]->m_Transform.SetPositionOffset(10.0f, -11.0f, -0.1f);

		auto scoreText = twFontManager->CreateText();
		scoreText->Set(font, text, 1.2f);
		scoreText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

		auto scoreTextDrawable = twRenderer->CreateFontDrawable();
		scoreTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
		scoreTextDrawable->m_pText = scoreText;
		scoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1,1,1));

        m_pNumbers[i]->SetDrawable(scoreTextDrawable);
        twActiveUIWorld->AddUIEntity(m_pNumbers[i]);
    }

    for (size_t i = 0; i < 5; i++)
    {
        std::string text = std::to_string(CGameInfo::Instance().m_Highscore.m_Scores[i]);

        m_pScores[i] = twActiveUIWorld->CreateUIEntity();
        m_pScores[i]->m_Transform.SetAnchorPoint(-0.25f, (0.1f - ((float)i * 0.1f)));

        if (text[0] == '1')
            m_pScores[i]->m_Transform.SetPositionOffset(3.0f, -11.0f, -0.1f);
        else
            m_pScores[i]->m_Transform.SetPositionOffset(10.0f, -11.0f, -0.1f);

        auto scoreText = twFontManager->CreateText();
        scoreText->Set(font, text, 1.2f);
        scoreText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

        auto scoreTextDrawable = twRenderer->CreateFontDrawable();
        scoreTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
        scoreTextDrawable->m_pText = scoreText;
        scoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &CGameInfo::Instance().m_Highscore.m_Colors[i]);

        m_pScores[i]->SetDrawable(scoreTextDrawable);
        twActiveUIWorld->AddUIEntity(m_pScores[i]);
    }

	//Dates
	for (size_t i = 0; i < 5; i++)
	{
		std::string text = CGameInfo::Instance().m_Highscore.m_Dates[i];

		m_pDates[i] = twActiveUIWorld->CreateUIEntity();
		m_pDates[i]->m_Transform.SetAnchorPoint(0.10f, (0.1f - ((float)i * 0.1f)));

		if (text[0] == '1')
			m_pDates[i]->m_Transform.SetPositionOffset(3.0f, -11.0f, -0.1f);
		else
			m_pDates[i]->m_Transform.SetPositionOffset(10.0f, -11.0f, -0.1f);

		auto datesText = twFontManager->CreateText();
		datesText->Set(font, text, 1.2f);
		datesText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

		auto dateTextDrawable = twRenderer->CreateFontDrawable();
		dateTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
		dateTextDrawable->m_pText = datesText;
		dateTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &CGameInfo::Instance().m_Highscore.m_Colors[i]);

		m_pDates[i]->SetDrawable(dateTextDrawable);
		twActiveUIWorld->AddUIEntity(m_pDates[i]);
	}

	{
		std::string text = "#";

		m_pNumber = twActiveUIWorld->CreateUIEntity();
		m_pNumber->m_Transform.SetAnchorPoint(-0.35f, 0.25f);

		m_pNumber->m_Transform.SetPositionOffset(3.0f, -11.0f, -0.1f);

		auto scoreText = twFontManager->CreateText();
		scoreText->Set(font, text, 1.2f);
		scoreText->SetTextAlign(triebWerk::ETextAlign::MiddleRight);

		auto scoreTextDrawable = twRenderer->CreateFontDrawable();
		scoreTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
		scoreTextDrawable->m_pText = scoreText;
		scoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1, 1, 1));

		m_pNumber->SetDrawable(scoreTextDrawable);
		twActiveUIWorld->AddUIEntity(m_pNumber);
	}

	{
		std::string text = "Score";
		
		m_pScore = twActiveUIWorld->CreateUIEntity();
		m_pScore->m_Transform.SetAnchorPoint(-0.25f, 0.25f);
		m_pScore->m_Transform.SetPositionOffset(3.0f, -11.0f, -0.1f);
		
		auto scoreText = twFontManager->CreateText();
		scoreText->Set(font, text, 1.2f);
		scoreText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);
		
		auto scoreTextDrawable = twRenderer->CreateFontDrawable();
		scoreTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
		scoreTextDrawable->m_pText = scoreText;
		scoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1, 1, 1));
		
		m_pScore->SetDrawable(scoreTextDrawable);
		twActiveUIWorld->AddUIEntity(m_pScore);
	}

	{
		std::string text = "Date";

		m_pDate = twActiveUIWorld->CreateUIEntity();
		m_pDate->m_Transform.SetAnchorPoint(0.10f, 0.25f);
		m_pDate->m_Transform.SetPositionOffset(3.0f, -11.0f, -0.1f);

		auto scoreText = twFontManager->CreateText();
		scoreText->Set(font, text, 1.2f);
		scoreText->SetTextAlign(triebWerk::ETextAlign::MiddleLeft);

		auto scoreTextDrawable = twRenderer->CreateFontDrawable();
		scoreTextDrawable->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
		scoreTextDrawable->m_pText = scoreText;
		scoreTextDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1, 1, 1));

		m_pDate->SetDrawable(scoreTextDrawable);
		twActiveUIWorld->AddUIEntity(m_pDate);
	}
}

void CHighscoreMenu::Update(const SUIInput& a_rInput)
{
    if (a_rInput.m_Back)
    {
        CGameInfo::Instance().m_ChangeMenu = true;
        CGameInfo::Instance().m_Menu = EMenus::Main;
        twAudio->PlaySFX(twResourceManager->GetSound("SFX_ButtonBack"));
    }
}

void CHighscoreMenu::End()
{
    twActiveUIWorld->RemoveUIEntity(m_pFieldBG);
    twActiveUIWorld->RemoveUIEntity(m_pNumbers[0]);
    twActiveUIWorld->RemoveUIEntity(m_pNumbers[1]);
    twActiveUIWorld->RemoveUIEntity(m_pNumbers[2]);
    twActiveUIWorld->RemoveUIEntity(m_pNumbers[3]);
    twActiveUIWorld->RemoveUIEntity(m_pNumbers[4]);

    twActiveUIWorld->RemoveUIEntity(m_pScores[0]);
    twActiveUIWorld->RemoveUIEntity(m_pScores[1]);
    twActiveUIWorld->RemoveUIEntity(m_pScores[2]);
    twActiveUIWorld->RemoveUIEntity(m_pScores[3]);
    twActiveUIWorld->RemoveUIEntity(m_pScores[4]);

	twActiveUIWorld->RemoveUIEntity(m_pDates[0]);
	twActiveUIWorld->RemoveUIEntity(m_pDates[1]);
	twActiveUIWorld->RemoveUIEntity(m_pDates[2]);
	twActiveUIWorld->RemoveUIEntity(m_pDates[3]);
	twActiveUIWorld->RemoveUIEntity(m_pDates[4]);

	twActiveUIWorld->RemoveUIEntity(m_pDate);
	twActiveUIWorld->RemoveUIEntity(m_pNumber);
	twActiveUIWorld->RemoveUIEntity(m_pScore);
}
