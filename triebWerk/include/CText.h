#pragma once
#include <string>
#include <ft2build.h>
#include <CTexture2D.h>
#include FT_FREETYPE_H

namespace triebWerk
{
    class CFont;
    class CGraphics;

    class CText
    {
    private:
        std::string m_Text;
        CFont* m_pFont;
        unsigned int m_PointSize;
        float m_LineSpacing;

        bool m_IsModified;
        unsigned int m_Width;
        unsigned int m_Height;
        unsigned int m_DPIX;
        unsigned int m_DPIY;

		CTexture2D m_Texture;
        CGraphics* m_pGraphics;
        unsigned char* m_pBuffer;

    public:
        CText(CGraphics* a_pGraphics, unsigned int a_DPIX, unsigned int a_DPIY, unsigned char* a_pBuffer);
        ~CText();

        void Update(const char* a_pText, CFont* a_pFont, const unsigned int a_PointSize);
        void Update(const std::string a_Text, CFont* a_pFont, const unsigned int a_PointSize);
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		CTexture2D* GetTexture();

    private:
        void CreateTexture();
        void DrawLetter(FT_Bitmap* a_pBitmap, FT_Int a_X, FT_Int a_Y);
    };
}