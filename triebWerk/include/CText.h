#pragma once
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace triebWerk
{
    class CFont;

    class CText
    {
    private:
        std::string m_Text;
        CFont* m_pFont;
        unsigned int m_PixelSize;

        bool m_IsModified;
        static const unsigned int WIDTH = 800;
        static const unsigned int HEIGHT = 600;
        unsigned char m_Buffer[WIDTH][HEIGHT];

    public:
        CText();
        ~CText();

        void SetText(const std::string a_Text);
        void SetText(const char* const a_Text);
        void SetFont(CFont* const a_pFont);
        void SetPixelSize(const unsigned int a_PixelSize);

    public:
        void CreateTexture();

    private:
        void DrawLetter(FT_Bitmap* a_pBitmap, FT_Int a_X, FT_Int a_Y);
    };
}