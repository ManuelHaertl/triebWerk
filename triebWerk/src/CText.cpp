#include <CText.h>

#include <CFont.h>
#include <string.h>

triebWerk::CText::CText() :
    m_Text(),
    m_pFont(nullptr),
    m_PixelSize(12),
    m_IsModified(false)
{
    memset(&m_Buffer, 0, WIDTH * HEIGHT);
}

triebWerk::CText::~CText()
{
    
}

void triebWerk::CText::SetText(const std::string a_Text)
{
    m_Text = a_Text;
    m_IsModified = true;
}

void triebWerk::CText::SetText(const char* const a_Text)
{
    m_Text = a_Text;
    m_IsModified = true;
}

void triebWerk::CText::SetFont(CFont* const a_pFont)
{
    m_pFont = a_pFont;
    m_IsModified = true;
}

void triebWerk::CText::SetPixelSize(const unsigned int a_PixelSize)
{
    m_PixelSize = a_PixelSize;
    m_IsModified = true;
}

void triebWerk::CText::CreateTexture()
{
    FT_Error error;

    FT_Face face = m_pFont->GetFace();

    FT_Set_Char_Size(face, 50 * 64, 0, 100, 0);
    //FT_Set_Pixel_Sizes(face, 0, m_PixelSize);
    //FT_Select_Charmap(face, FT_ENCODING_BIG5);

    for (size_t i = 0; i < m_Text.size(); ++i)
    {
        error = FT_Load_Char(face, m_Text[i], FT_LOAD_RENDER);
        if (error)
            continue;

        DrawLetter(&face->glyph->bitmap, face->glyph->bitmap_left, face->glyph->bitmap_top);
    }
}

void triebWerk::CText::DrawLetter(FT_Bitmap * a_pBitmap, FT_Int a_X, FT_Int a_Y)
{
    FT_Int  i, j, p, q;
    FT_Int  x_max = a_X + a_pBitmap->width;
    FT_Int  y_max = a_Y + a_pBitmap->rows;

    for (i = a_X, p = 0; i < x_max; i++, p++)
    {
        for (j = a_Y, q = 0; j < y_max; j++, q++)
        {
            if (i < 0 || j < 0 ||
                i >= WIDTH || j >= HEIGHT)
                continue;

            m_Buffer[j][i] |= a_pBitmap->buffer[q * a_pBitmap->width + p];
        }
    }
}
