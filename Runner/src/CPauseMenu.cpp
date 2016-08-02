#include <CPauseMenu.h>

#include <CGameInfo.h>

CPauseMenu::CPauseMenu()
{
}

CPauseMenu::~CPauseMenu()
{
}

void CPauseMenu::Start()
{

}

void CPauseMenu::Update(const SUIInput& a_rInput)
{
    if (a_rInput.m_Pause)
        CGameInfo::Instance().m_IsGamePaused = !CGameInfo::Instance().m_IsGamePaused;

    if (CGameInfo::Instance().m_IsGamePaused)
    {

    }

    UpdateGraphics();
}

void CPauseMenu::End()
{
}

void CPauseMenu::Resume()
{
}

void CPauseMenu::UpdateGraphics()
{

}
