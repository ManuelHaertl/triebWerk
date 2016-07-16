#include <CUI.h>
#include <CGameInfo.h>
#include <iomanip>
#include <sstream>

CUI::CUI() :
	m_pCurrentPoints(nullptr)
	, m_pDifficulty(nullptr)
	, m_pMultiplier(nullptr)
	, m_pTotalPoints(nullptr)
{
}

CUI::~CUI()
{
}

void CUI::Start()
{
	m_pFont = twFontManager->LoadFont(twResourceManager->GetFontFace("Rubik-Regular"), 20);

	CreateTotalPoints();
	CreateCurrentPoints();
	CreateMultiplier();
	CreateDifficulty();
}

void CUI::Update()
{

	std::stringstream stream0;
	stream0  << std::fixed << std::setprecision(0) << CGameInfo::Instance().m_TotalPoints;
	std::string totalPoints = "Total Points: " + stream0.str();

	std::stringstream stream1;
	stream1 << std::fixed << std::setprecision(0) << CGameInfo::Instance().m_CurrentPoints;
	std::string currentPoints = "Current Points: " + stream1.str();

	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(1) << CGameInfo::Instance().m_Multiplier;
	std::string multiplier = "x" + stream2.str();

	std::stringstream stream3;
	stream3 << std::fixed << std::setprecision(1) << CGameInfo::Instance().m_Difficulty;
	std::string difficulty = "Difficulty: " + stream3.str();
 
	m_pTotalPoints->SetText(totalPoints);
	m_pCurrentPoints->SetText(currentPoints);
	m_pMultiplier->SetText(multiplier);
	m_pDifficulty->SetText(difficulty);
}

void CUI::End()
{
}

void CUI::CreateTotalPoints()
{
	m_pTotalPoints = twFontManager->CreateText();
	m_pTotalPoints->Set(m_pFont, "Total Points: 0", 1.0f);

	auto entity = twActiveWorld->CreateEntity();
	entity->m_Transform.SetPosition(-700.0f, 500.0f, 0.0f);

	auto fontDraw = twRenderer->CreateFontDrawable();
	fontDraw->m_pText = m_pTotalPoints;
	fontDraw->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
	fontDraw->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

	entity->SetDrawable(fontDraw);
	twActiveWorld->AddEntity(entity);
}

void CUI::CreateCurrentPoints()
{
	m_pCurrentPoints = twFontManager->CreateText();
	m_pCurrentPoints->Set(m_pFont, "Current Points: 0", 1.0f);

	auto entity = twActiveWorld->CreateEntity();
	entity->m_Transform.SetPosition(-700.0f, 470.0f, 0.0f);

	auto fontDraw = twRenderer->CreateFontDrawable();
	fontDraw->m_pText = m_pCurrentPoints;
	fontDraw->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
	fontDraw->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

	entity->SetDrawable(fontDraw);
	twActiveWorld->AddEntity(entity);
}

void CUI::CreateMultiplier()
{
	m_pMultiplier = twFontManager->CreateText();
	m_pMultiplier->Set(m_pFont, "x1.0", 1.0f);

	auto entity = twActiveWorld->CreateEntity();
	entity->m_Transform.SetPosition(-340.0f, 470.0f, 0.0f);

	auto fontDraw = twRenderer->CreateFontDrawable();
	fontDraw->m_pText = m_pMultiplier;
	fontDraw->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
	fontDraw->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

	entity->SetDrawable(fontDraw);
	twActiveWorld->AddEntity(entity);
}

void CUI::CreateDifficulty()
{
	m_pDifficulty = twFontManager->CreateText();
	m_pDifficulty->Set(m_pFont, "Difficulty: 0", 1.0f);

	auto entity = twActiveWorld->CreateEntity();
	entity->m_Transform.SetPosition(-700.0f, 440, 0.0f);

	auto fontDraw = twRenderer->CreateFontDrawable();
	fontDraw->m_pText = m_pDifficulty;
	fontDraw->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
	fontDraw->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(0.5f, 1.0f, 1.0f));

	entity->SetDrawable(fontDraw);
	twActiveWorld->AddEntity(entity);
}
