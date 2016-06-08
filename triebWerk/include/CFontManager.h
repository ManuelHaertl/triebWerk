#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <CFont.h>
#include <CText.h>

namespace triebWerk
{
    class CFontManager
    {
    private:
        FT_Library m_Library;

    public:
        CFontManager();
        ~CFontManager();

        bool Initialize();
        void Shutdown();

        FT_Library* GetLibrary();
        CText* CreateText();
    };
}