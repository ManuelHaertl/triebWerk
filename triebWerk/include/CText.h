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
        float offsetX, offsetY;

        SLetterInfo()
            : letterCoordinate()
            , offsetX(0)
            , offsetY(0)
        { }
    };

    enum class ETextAlign
    {
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

    class CText
    {
	public:
		CFont* m_pFont;
		SLetterInfo* m_pLetterInfo;
		size_t m_LetterCount;

    private:
        std::string m_Text;
        float m_LineSpacing;
        float m_Width, m_Height;
        ETextAlign m_TextAlign;

    public:
        CText();
        ~CText();

        void Set(CFont* a_pFont, const char* a_pText, const float a_LineSpacing);
        void Set(CFont* a_pFont, std::string a_Text, const float a_LineSpacing);
        void SetFont(CFont* a_pFont);
        void SetText(const char* a_pText);
        void SetText(const std::string a_Text);
        void SetLineSpacing(const float a_LineSpacing);
        void SetTextAlign(const ETextAlign a_TextAlign);

    private:
        void CreateLetterInfo();
        void CalculateWidthAndHeight();
        void MakeTextToValidIndices();
    };
}