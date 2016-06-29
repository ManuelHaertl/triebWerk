#include <CID.h>

triebWerk::CID::CID() :
    m_Name(""),
    m_Hash(0)
{
}

triebWerk::CID::~CID()
{
}

std::string triebWerk::CID::GetName() const
{
    return m_Name;
}

std::string triebWerk::CID::GetDescribtion() const
{
    return m_Describtion;
}

size_t triebWerk::CID::GetHash() const
{
    return m_Hash;
}

void triebWerk::CID::SetName(const char* a_pName)
{
    m_Name = a_pName;
    HashName();
}

void triebWerk::CID::SetName(const std::string a_Name)
{
    m_Name = a_Name;
    HashName();
}

void triebWerk::CID::SetDescribtion(const char* a_pDescribtion)
{
    m_Describtion = a_pDescribtion;
}

void triebWerk::CID::SetDescribtion(const std::string a_Describtion)
{
    m_Describtion = a_Describtion;
}

void triebWerk::CID::HashName()
{
    m_Hash = StringHasher(m_Name);
}
