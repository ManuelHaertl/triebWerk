#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

namespace triebWerk
{
    class CFont
    {
    private:
        FT_Face m_Face;

    public:
        CFont(FT_Library* a_pLibrary, const char* a_pFile);
        ~CFont();

        FT_Face& GetFace();
    };
}