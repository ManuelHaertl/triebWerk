#pragma once
#include <string>

namespace triebWerk
{
    class CFont;

    class CText
    {
    public:
        std::string m_Text;
        CFont* m_pFont;

    public:
        CText();
        ~CText();
    };
}