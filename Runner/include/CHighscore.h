#pragma once
#include <string>
#include <DirectXMath.h>

class CHighscore
{
private:
    static const size_t MaxScores = 5;
    bool m_HasHighscore;

public:
    size_t m_Scores[MaxScores];
    std::string m_Dates[MaxScores];
    DirectX::XMFLOAT3 m_Colors[MaxScores];

public:
    CHighscore();
    ~CHighscore();

    bool IsHighscore();
    void AddScore(const size_t a_Score, const std::string a_Date, const DirectX::XMFLOAT3 a_Color);
    void ResetScores();

private:
    void Add(const size_t a_Rank, const size_t a_Score, const std::string a_Date, const DirectX::XMFLOAT3 a_Color);
};