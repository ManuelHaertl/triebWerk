#pragma once
#include <CEngine.h>

class CUI
{
private:
	triebWerk::CFont* m_pFont;
	triebWerk::CText* m_pTotalPoints;
	triebWerk::CText* m_pCurrentPoints;
	triebWerk::CText* m_pMultiplier;
	triebWerk::CText* m_pDifficulty;

public:
	CUI();
	~CUI();

public:
	void Start();
	void Update();
	void End();

private:
    void CreateTextures();
	void CreateTotalPoints();
	void CreateCurrentPoints();
	void CreateMultiplier();
	void CreateDifficulty();

};