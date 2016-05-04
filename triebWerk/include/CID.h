#pragma once
#include <CStringHasher.h>

namespace triebWerk
{
    class CID
    {
    private:
        std::string m_Name;
        size_t m_Hash;

    public:
        CID();
        ~CID();

        std::string GetName() const;
        size_t GetHash() const;

        void SetName(const char* a_pName);
        void Setname(const std::string a_Name);

    private:
        void HashName();
    };
}