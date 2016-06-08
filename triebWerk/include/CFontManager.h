#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <CFont.h>

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

        CFont* CreateEmptyFont();
    };
}