#pragma once
#include <string>
#include <DirectXMath.h>

class CHighscore
{
private:
    static const size_t MaxScores = 5;

public:
    size_t m_Scores[MaxScores];
    std::string m_Dates[MaxScores];
    DirectX::XMFLOAT3 m_Colors[MaxScores];

private:

    int m_CurrentRank;
    size_t m_CurrentScore;
    std::string m_CurrentDate;
    DirectX::XMFLOAT3 m_CurrentColor;

    bool m_IsHighscore;
    bool m_IsInRankList;

public:
    CHighscore();
    ~CHighscore();

    bool IsHighscore();
    bool IsInRankList();
    void AddScore(const size_t a_Score);
    void AddDate(const std::string a_Date);
    void AddColor(const DirectX::XMFLOAT3 a_Color);
    void Submit();
    void ResetScores();
};