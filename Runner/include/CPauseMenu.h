#pragma once
#include <CEngine.h>
#include <IMenu.h>
class CPauseMenu : public IMenu
{
public:
    CPauseMenu();
    ~CPauseMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;
    void Resume() final;

private:
    void UpdateGraphics();
};