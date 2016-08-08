#pragma once
#include <CEngine.h>
#include <IMenu.h>

class CHighscoreMenu : public IMenu
{
private:
    triebWerk::CUIEntity* m_pFieldBG;
    triebWerk::CUIEntity* m_pScores[5];

public:
    CHighscoreMenu();
    ~CHighscoreMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
};