#pragma once
#include <CStringHasher.h>

namespace triebWerk
{
    class CID
    {
    private:
        std::string m_Name;
        std::string m_Describtion;
        size_t m_Hash;

    public:
        CID();
        ~CID();

        std::string GetName() const;
        std::string GetDescribtion() const;
        size_t GetHash() const;

        void SetName(const char* a_pName);
        void SetName(const std::string a_Name);
        void SetDescribtion(const char* a_pDescribtion);
        void SetDescribtion(const std::string a_Describtion);

    private:
        void HashName();
    };
}