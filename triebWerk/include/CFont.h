#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

namespace triebWerk
{
    class CFont
    {
    private:
        FT_Library* m_pLibrary;

    public:
        CFont(FT_Library* a_pLibrary);
        ~CFont();
    };
}