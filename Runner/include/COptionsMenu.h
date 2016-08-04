#pragma once
#include <CEngine.h>
#include <IMenu.h>

class COptionsMenu : public IMenu
{
private:
    triebWerk::CUIEntity* m_pFieldBG;

public:
    COptionsMenu();
    ~COptionsMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
};