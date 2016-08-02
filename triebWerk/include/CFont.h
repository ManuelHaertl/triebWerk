#pragma once
#include <CTexture2D.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace triebWerk
{
    class CFontFace;
    class CGraphics;

    struct SLetterCoordinate
    {
        float uBegin, uEnd, vBegin, vEnd;
        float width, height;

        SLetterCoordinate()
            : uBegin(0.0f)
            , uEnd(1.0f)
            , vBegin(0.0f)
            , vEnd(1.0f)
            , width(0)
            , height(0)
        { }
    };

    class CFont
    {
    private:
        static const size_t LETTER_COUNT = 94;

    public:
        CTexture2D m_LetterMap;
        int m_Width, m_Height;
        SLetterCoordinate m_LetterCoordinates[LETTER_COUNT];

    private:
        // user specific
        CFontFace* m_pFontFace;
        unsigned int m_PointSize;

        // engine specific
        unsigned int m_DPIX;
        unsigned int m_DPIY;
        const char* m_AllLetter;

        // Font properties
        CGraphics* m_pGraphics;
        char* m_pBuffer;

    public:
        CFont(CGraphics* a_pGraphics, const unsigned int a_DPIX, const unsigned int a_DPIY, CFontFace* a_pFontFace, const unsigned int a_PointSize);
        ~CFont();

        const CFontFace* GetFontFace() const;
        const unsigned int GetPointSize() const;

    private:
        void CreateLetterMap();
        FT_BBox GetTextureBBox();
        void DrawAllLetterInBuffer(int a_PenX, int a_PenY);
        void DrawSingleLetter(FT_Bitmap* a_pBitmap, FT_Int a_X, FT_Int a_Y);
        void CreateTexture();
    };
}