#pragma once
#include <IMenu.h>
#include <CEngine.h>

class CInGameUI
{
private:
    SUIInput m_UIInput;
    IMenu* m_pPauseMenu;

    triebWerk::CText* m_pCurrentPoints;
    triebWerk::CText* m_pTotalPoints;
    triebWerk::CUIDrawable* m_pBarLeft;
    triebWerk::CUIDrawable* m_pBarRight;

public:
    CInGameUI();
    ~CInGameUI();

    void Start();
    void Update();
    void End();

private:
    void CreateIngameUI();
    void UpdateIngameUI();
    void CheckInput();
};