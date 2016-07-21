#pragma once
#include <CElementContainer.h>
#include <CStringHasher.h>

namespace triebWerk
{
    class CTag
    {
    private:
        CElementContainer<size_t> m_Tags;

    public:
        CTag();
        ~CTag();

        void AddTag(const char* a_pTag);
        void AddTag(const std::string a_Tag);
        void RemoveTag(const char* a_pTag);
        void RemoveTag(const std::string a_Tag);
        bool HasTag(const char* a_pTag);
        bool HasTag(const std::string a_Tag);
    };
}