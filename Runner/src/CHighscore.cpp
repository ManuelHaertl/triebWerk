#include <CHighscore.h>

CHighscore::CHighscore()
    : m_Scores{ 0,0,0,0,0 }
    , m_Dates{"-", "-", "-", "-", "-"}
    , m_Colors{DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) , DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) , DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) , DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f) }
    , m_CurrentRank(-1)
    , m_CurrentScore(0)
    , m_CurrentDate("-")
    , m_CurrentColor{1.0f, 1.0f, 1.0f}
    , m_IsHighscore(false)
    , m_IsInRankList(false)
{
}

CHighscore::~CHighscore()
{
}

bool CHighscore::IsHighscore()
{
    return m_IsHighscore;
}

bool CHighscore::IsInRankList()
{
    return m_IsInRankList;
}

void CHighscore::AddScore(const size_t a_Score)
{
    m_CurrentScore = a_Score;

    m_CurrentRank = -1;
    for (size_t i = 0; i < MaxScores; ++i)
    {
        if (a_Score > m_Scores[i])
        {
            m_CurrentRank = i;
            break;
        }
    }

    // if you aren't in the rank list
    if (m_CurrentRank == -1)
    {
        m_IsHighscore = false;
        m_IsInRankList = false;
    }
    // if you are rank 1
    else if (m_CurrentRank == 0)
    {
        m_IsHighscore = true;
        m_IsInRankList = true;
    }
    // if you are elsewhere in the rank list
    else
    {
        m_IsHighscore = false;
        m_IsInRankList = true;
    }
}

void CHighscore::AddDate(const std::string a_Date)
{
    m_CurrentDate = a_Date;
}

void CHighscore::AddColor(const DirectX::XMFLOAT3 a_Color)
{
    m_CurrentColor = a_Color;
}

void CHighscore::Submit()
{
    if (m_CurrentRank == -1)
        return;

    else if (m_CurrentRank != MaxScores - 1)
    {
        // move all scores (behind the rank) 1 back
        for (size_t i = MaxScores - 1; i > m_CurrentRank; --i)
        {
            m_Scores[i] = m_Scores[i - 1];
            m_Dates[i] = m_Dates[i - 1];
            m_Colors[i] = m_Colors[i - 1];
        }
    }

    m_Scores[m_CurrentRank] = m_CurrentScore;
    m_Dates[m_CurrentRank] = m_CurrentDate;
    m_Colors[m_CurrentRank] = m_CurrentColor;
}

void CHighscore::ResetScores()
{
    for (size_t i = 0; i < MaxScores - 1; ++i)
    {
        m_Scores[i] = 0;
        m_Dates[i] = "-";
        m_Colors[i].x = 1.0f;
        m_Colors[i].y = 1.0f;
        m_Colors[i].z = 1.0f;
    }
}