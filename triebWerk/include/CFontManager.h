#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <CFont.h>
#include <CText.h>

namespace triebWerk
{
    class CGraphics;

    class CFontManager
    {
    private:
        FT_Library m_Library;
            
        CGraphics* m_pGraphics;
        unsigned int m_DPIX;
        unsigned int m_DPIY;

    public:
        CFontManager();
        ~CFontManager();

        bool Initialize(CGraphics* a_pGraphics, const unsigned int a_DPIX, const unsigned int a_DPIY);
        void Shutdown();

        FT_Library* GetLibrary();
        CText* CreateText(const char* a_pText, CFont* a_pFont, const unsigned int a_PointSize);
        CText* CreateText(const std::string a_Text, CFont* a_pFont, const unsigned int a_PointSize);
    };
}