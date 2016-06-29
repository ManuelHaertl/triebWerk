#pragma once
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <CFont.h>

namespace triebWerk
{
    struct SLetterInfo
    {
        SLetterCoordinate letterCoordinate;
        int offsetX, offsetY;

        SLetterInfo()
            : letterCoordinate()
            , offsetX(0)
            , offsetY(0)
        { }
    };

    class CText
    {
    private:
        std::string m_Text;
        CFont* m_pFont;
        float m_LineSpacing;

        SLetterInfo* m_pLetterInfo;
        size_t m_LetterCount;
        int m_Width, m_Height;

    public:
        CText();
        ~CText();

        void Set(CFont* a_pFont, const char* a_pText, const float a_LineSpacing);
        void Set(CFont* a_pFont, std::string a_Text, const float a_LineSpacing);
        void SetFont(CFont* a_pFont);
        void SetText(const char* a_pText);
        void SetText(const std::string a_Text);
        void SetLineSpacing(const float a_LineSpacing);

    private:
        void CreateLetterInfo();
        void CalculateWidthAndHeight();
        void MakeTextToValidIndices();
    };
}