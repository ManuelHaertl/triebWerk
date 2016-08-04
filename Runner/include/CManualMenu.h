#pragma once
#include <CEngine.h>
#include <IMenu.h>

class CManualMenu : public IMenu
{
private:
    triebWerk::CUIEntity* m_pFieldBG;
    triebWerk::CUIEntity* m_pControls;

public:
    CManualMenu();
    ~CManualMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
};