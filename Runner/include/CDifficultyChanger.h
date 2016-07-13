#pragma once
class CDifficultyChanger
{
public:
    static float ScoreDifficulty2;
    static float ScoreDifficulty3;
    static float ScoreDifficulty4;
    static float ScoreDifficulty5;
    static float SpeedRaiseTime;
    static float AddedSpeed;
    static float MaxSpeed;

private:
    float m_CurrentSpeedRaiseTime;

public:
    CDifficultyChanger();
    ~CDifficultyChanger();

    void Start();
    void Update();
    void End();

private:
    void AddSpeed();
};