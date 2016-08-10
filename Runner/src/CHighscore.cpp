#include <CHighscore.h>

CHighscore::CHighscore()
    : m_Scores{ 0,0,0,0,0 }
    , m_HasHighscore(false)
{
}

CHighscore::~CHighscore()
{
}

bool CHighscore::IsHighscore()
{
    return m_HasHighscore;
}

void CHighscore::AddScore(const size_t a_Score)
{
    // get the rank
    size_t rank = 100;
    for (size_t i = 0; i < MaxScores; ++i)
    {
        if (a_Score > m_Scores[i])
        {
            rank = i;
            break;
        }
    }

    m_HasHighscore = (rank == 0);

    // early out if the score won't make it into the highscore list
    if (rank >= MaxScores)
        return;

    // if it is the last rank
    if (rank == MaxScores - 1)
    {
        m_Scores[MaxScores - 1] = a_Score;
        return;
    }

    // move all scores (behind the rank) 1 back
    for (size_t i = MaxScores - 1; i > rank; --i)
        m_Scores[i] = m_Scores[i - 1];

    // set score
    m_Scores[rank] = a_Score;
}

void CHighscore::ResetScores()
{
    for (size_t i = 0; i < MaxScores - 1; ++i)
        m_Scores[i] = 0;
}
