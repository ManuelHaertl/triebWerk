#include <CTag.h>

triebWerk::CTag::CTag()
{
}

triebWerk::CTag::~CTag()
{
}

void triebWerk::CTag::AddTag(const char* a_pTag)
{
    m_Tags.Add(StringHasher(a_pTag));
}

void triebWerk::CTag::AddTag(const std::string a_Tag)
{
    m_Tags.Add(StringHasher(a_Tag));
}

void triebWerk::CTag::RemoveTag(const char* a_pTag)
{
    m_Tags.Remove(StringHasher(a_pTag));
}

void triebWerk::CTag::RemoveTag(const std::string a_Tag)
{
    m_Tags.Remove(StringHasher(a_Tag));
}

bool triebWerk::CTag::HasTag(const char* a_pTag)
{
    return m_Tags.Contains(StringHasher(a_pTag));
}

bool triebWerk::CTag::HasTag(const std::string a_Tag)
{
    return m_Tags.Contains(StringHasher(a_Tag));
}