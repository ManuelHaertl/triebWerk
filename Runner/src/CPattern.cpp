#include <CPattern.h>

CPattern::CPattern() :
    m_Priority(1),
    m_Difficulty(1),
    m_Width(0),
    m_Height(0),
    m_ConnectedPattern(),
    m_Tiles()
{
    for (size_t i = 0; i < MaxCategories; ++i)
    {
        m_ConnectedCategories[i] = false;
    }
}

CPattern::~CPattern()
{
}
