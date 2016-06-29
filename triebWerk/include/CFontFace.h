#pragma once
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace triebWerk
{
    class CFontFace
    {
    private:
        FT_Face m_Face;
        std::string m_Name;

    public:
        CFontFace(FT_Library* a_pLibrary, const char* a_pFile, const char* a_pFileName);
        ~CFontFace();

        FT_Face& GetFace();
        const std::string& GetName();
    };
}