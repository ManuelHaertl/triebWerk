#pragma once
#include <IMenu.h>

class CInGameUI
{
private:
    SUIInput m_UIInput;
    IMenu* m_pPauseMenu;

public:
    CInGameUI();
    ~CInGameUI();

    void Start();
    void Update();
    void End();

private:
    void CheckInput();
};