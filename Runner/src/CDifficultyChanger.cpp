#include <CDifficultyChanger.h>

#include <CGameInfo.h>
#include <CEngine.h>

CDifficultyChanger::CDifficultyChanger()
{
}

CDifficultyChanger::~CDifficultyChanger()
{
}

void CDifficultyChanger::Start()
{
    m_CurrentSpeedRaiseTime = SpeedRaiseTime;
}

void CDifficultyChanger::Update()
{
    CGameInfo& gameInfo = CGameInfo::Instance();
    
    float points = gameInfo.m_TotalPoints + (gameInfo.m_CurrentPoints * gameInfo.m_Multiplier);

    if (points < ScoreDifficulty2)
        gameInfo.m_Difficulty = 1;
    else if (points < ScoreDifficulty3)
        gameInfo.m_Difficulty = 2;
    else if (points < ScoreDifficulty4)
        gameInfo.m_Difficulty = 3;
    else if (points < ScoreDifficulty5)
        gameInfo.m_Difficulty = 4;
    else if (points < ScoreDifficulty6)
        gameInfo.m_Difficulty = 5;
    else
    {
        gameInfo.m_Difficulty = 6;
        m_CurrentSpeedRaiseTime -= twTime->GetDeltaTime();
        if (m_CurrentSpeedRaiseTime <= 0.0f)
        {
            m_CurrentSpeedRaiseTime = SpeedRaiseTime;
            AddSpeed();
        }
    }
}

void CDifficultyChanger::End()
{
}

void CDifficultyChanger::AddSpeed()
{
    CGameInfo& gameInfo = CGameInfo::Instance();

    gameInfo.m_FlyDifficultySpeed += AddedSpeed;
    if (gameInfo.m_FlyDifficultySpeed > MaxSpeed)
        gameInfo.m_FlyDifficultySpeed = MaxSpeed;
}
