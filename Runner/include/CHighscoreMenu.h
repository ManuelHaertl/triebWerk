#pragma once
#include <CEngine.h>
#include <IMenu.h>

class CHighscoreMenu : public IMenu
{
private:
    triebWerk::CUIEntity* m_pFieldBG;
    triebWerk::CUIEntity* m_pNumbers[5];
    triebWerk::CUIEntity* m_pScores[5];
	triebWerk::CUIEntity* m_pDates[5];
	triebWerk::CUIEntity* m_pDate;
	triebWerk::CUIEntity* m_pScore;
	triebWerk::CUIEntity* m_pNumber;

public:
    CHighscoreMenu();
    ~CHighscoreMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
};