#pragma once
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace triebWerk
{
    class CGraphics;
    class CFont;
    class CFontFace;
    class CText;

    class CFontManager
    {
    private:
        FT_Library m_Library;
        std::vector<CFont*> m_Fonts;

        CGraphics* m_pGraphics;
        unsigned int m_DPIX;
        unsigned int m_DPIY;

    public:
        CFontManager();
        ~CFontManager();

        bool Initialize(CGraphics* a_pGraphics, const unsigned int a_DPIX, const unsigned int a_DPIY);
        void Shutdown();

        FT_Library* GetLibrary();
        CFont* LoadFont(CFontFace* a_pFontFace, const unsigned int a_PointSize);
        void UnloadFont(const CFontFace* a_pFontFace, const unsigned int a_PointSize);
        CFont* GetFont(CFontFace* a_pFontFace, const unsigned int a_PointSize);
        CText* CreateText();
    };
}