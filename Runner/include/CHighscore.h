#pragma once
class CHighscore
{
private:
    static const size_t MaxScores = 5;
    bool m_HasHighscore;

public:
    size_t m_Scores[MaxScores];

public:
    CHighscore();
    ~CHighscore();

    bool IsHighscore();
    void AddScore(const size_t a_Score);
    void ResetScores();
};