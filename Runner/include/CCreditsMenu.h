#pragma once
#include <CEngine.h>
#include <IMenu.h>

class CCreditsMenu : public IMenu
{
private:
    triebWerk::CUIEntity* m_pFieldBG;
    triebWerk::CUIEntity* m_pManu;
    triebWerk::CUIEntity* m_pAlex;
    triebWerk::CUIEntity* m_pMaren;
    triebWerk::CUIEntity* m_pPinar;
    triebWerk::CUIEntity* m_pManuTitle;
    triebWerk::CUIEntity* m_pAlexTitle;
    triebWerk::CUIEntity* m_pMarenTitle;
    triebWerk::CUIEntity* m_pPinarTitle;

public:
    CCreditsMenu();
    ~CCreditsMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
};