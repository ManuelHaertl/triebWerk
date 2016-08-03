#include <CFont.h>

#include <iostream>
#include <cmath>
#include <CFontFace.h>
#include <CGraphics.h>

triebWerk::CFont::CFont(CGraphics* a_pGraphics, const unsigned int a_DPIX, const unsigned int a_DPIY, CFontFace* a_pFontFace, const unsigned int a_PointSize)
    : m_pFontFace(a_pFontFace)
    , m_PointSize(a_PointSize)
    , m_DPIX(a_DPIX)
    , m_DPIY(a_DPIY)
    , m_LetterMap()
    , m_Width(0)
    , m_Height(0)
    , m_AllLetter(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")
    , m_pGraphics(a_pGraphics)
    , m_pBuffer(nullptr)
{
    CreateLetterMap();
}

triebWerk::CFont::~CFont()
{
    
}

const triebWerk::CFontFace* triebWerk::CFont::GetFontFace() const
{
    return m_pFontFace;
}

const unsigned int triebWerk::CFont::GetPointSize() const
{
    return m_PointSize;
}

void triebWerk::CFont::CreateLetterMap()
{
    // check that the texture can be created
    if (m_pFontFace == nullptr)
        return;

    // set the char size
    FT_Face face = m_pFontFace->GetFace();
    FT_Set_Char_Size(face, 0, m_PointSize * 64, m_DPIX, m_DPIY);

    // get the bounding box of all letter
    FT_BBox textureBBox = GetTextureBBox();
    m_Width = std::abs(textureBBox.xMin) + std::abs(textureBBox.xMax) + LETTER_COUNT * 2;
    m_Height = std::abs(textureBBox.yMin) + std::abs(textureBBox.yMax);

    // create a buffer (depending on the bounding box) to draw in all letter
    m_pBuffer = new char[m_Width * m_Height];
    memset(m_pBuffer, 0, m_Width * m_Height);

    DrawAllLetterInBuffer(textureBBox.xMin, textureBBox.yMax);

    // create the d3d11 texture with the letter
    CreateTexture();

    // delete the buffer
    delete[] m_pBuffer;
    m_pBuffer = nullptr;
}

FT_BBox triebWerk::CFont::GetTextureBBox()
{
    FT_Face face = m_pFontFace->GetFace();
    FT_GlyphSlot slot = face->glyph;
    FT_UInt       glyph_index;
    FT_Bool       use_kerning;
    FT_UInt       previous;
    int           pen_x, pen_y, n;
    FT_Error      error;

    FT_Glyph      glyphs[LETTER_COUNT];   /* glyph image    */
    FT_Vector     pos[LETTER_COUNT];   /* glyph position */
    FT_UInt       num_glyphs;

    pen_x = 0;   /* start at (0,0) */
    pen_y = 0;

    num_glyphs = 0;
    use_kerning = FT_HAS_KERNING(face);
    previous = 0;

    for (n = 0; n < LETTER_COUNT; n++)
    {
        /* convert character code to glyph index */
        glyph_index = FT_Get_Char_Index(face, m_AllLetter[n]);

        /* retrieve kerning distance and move pen position */
        if (use_kerning && previous && glyph_index)
        {
            FT_Vector  delta;

            FT_Get_Kerning(face, previous, glyph_index,
                FT_KERNING_DEFAULT, &delta);

            pen_x += delta.x >> 6;
        }

        /* store current pen position */
        pos[num_glyphs].x = pen_x;
        pos[num_glyphs].y = pen_y;

        /* load glyph image into the slot without rendering */
        error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
        if (error)
            continue;  /* ignore errors, jump to next glyph */

                       /* extract glyph image and store it in our table */
        error = FT_Get_Glyph(face->glyph, &glyphs[num_glyphs]);
        if (error)
            continue;  /* ignore errors, jump to next glyph */

                       /* increment pen position */
        pen_x += slot->advance.x >> 6;

        /* record current glyph index */
        previous = glyph_index;

        /* increment number of glyphs */
        num_glyphs++;
    }

    //////////////////////////////////////////////////////////////////////////////////////////

    FT_BBox textureBBox;
    FT_BBox glyph_bbox;

    /* initialize string bbox to "empty" values */
    textureBBox.xMin = textureBBox.yMin = 32000;
    textureBBox.xMax = textureBBox.yMax = -32000;

    /* for each glyph image, compute its bounding box, */
    /* translate it, and grow the string bbox          */
    int numGlyphs = static_cast<int>(num_glyphs);
    for (n = 0; n < numGlyphs; n++)
    {
        FT_Glyph_Get_CBox(glyphs[n], ft_glyph_bbox_pixels,
            &glyph_bbox);

        glyph_bbox.xMin += pos[n].x;
        glyph_bbox.xMax += pos[n].x;
        glyph_bbox.yMin += pos[n].y;
        glyph_bbox.yMax += pos[n].y;

        if (glyph_bbox.xMin < textureBBox.xMin)
            textureBBox.xMin = glyph_bbox.xMin;

        if (glyph_bbox.yMin < textureBBox.yMin)
            textureBBox.yMin = glyph_bbox.yMin;

        if (glyph_bbox.xMax > textureBBox.xMax)
            textureBBox.xMax = glyph_bbox.xMax;

        if (glyph_bbox.yMax > textureBBox.yMax)
            textureBBox.yMax = glyph_bbox.yMax;
    }

    /* check that we really grew the string bbox */
    if (textureBBox.xMin > textureBBox.xMax)
    {
        textureBBox.xMin = 0;
        textureBBox.yMin = 0;
        textureBBox.xMax = 0;
        textureBBox.yMax = 0;
    }

    for (size_t i = 0; i < LETTER_COUNT; ++i)
    {
        FT_Done_Glyph(glyphs[i]);
    }

    return textureBBox;
}

void triebWerk::CFont::DrawAllLetterInBuffer(int a_PenX, int a_PenY)
{
    FT_Error error;
    FT_Face face = m_pFontFace->GetFace();
    FT_GlyphSlot glyph = face->glyph;

    float fWidth = (float)m_Width;
    float fHeight = (float)m_Height;

    for (size_t i = 0; i < LETTER_COUNT; ++i)
    {
        error = FT_Load_Char(face, m_AllLetter[i], FT_LOAD_RENDER);
        if (error)
            continue;

        SLetterCoordinate& letterCoordinate = m_LetterCoordinates[i];
        letterCoordinate.uBegin = (float)(a_PenX + (glyph->metrics.horiBearingX >> 6)) / fWidth;
        letterCoordinate.uEnd = (float)(a_PenX + (glyph->metrics.horiBearingX >> 6) + (glyph->metrics.width >> 6)) / fWidth;
        letterCoordinate.vBegin = 1.0f / fHeight;
        letterCoordinate.vEnd = (fHeight - 1) / fHeight;

        DrawSingleLetter(
            &glyph->bitmap,
            a_PenX + glyph->bitmap_left,
            a_PenY - glyph->bitmap_top);

        int width = glyph->advance.x >> 6;
        a_PenX += width;

        if (m_AllLetter[i] == ' ')
            letterCoordinate.width = (float)width;
        else
            letterCoordinate.width = ((float)(a_PenX + (glyph->metrics.horiBearingX >> 6) + (glyph->metrics.width >> 6))) - ((float)(a_PenX + (glyph->metrics.horiBearingX >> 6)));
        letterCoordinate.width = (float)width;
        letterCoordinate.height = (float)m_Height;
        a_PenX += 2;
    }
}

void triebWerk::CFont::DrawSingleLetter(FT_Bitmap* a_pBitmap, FT_Int a_X, FT_Int a_Y)
{
    FT_Int  i, j, p, q;
    FT_Int  x_max = a_X + a_pBitmap->width;
    FT_Int  y_max = a_Y + a_pBitmap->rows;

    for (i = a_X, p = 0; i < x_max; i++, p++)
    {
        for (j = a_Y, q = 0; j < y_max; j++, q++)
        {
            if (i < 0 || j < 0 || i >= m_Width || j >= m_Height)
                continue;

            size_t cur = j * m_Width + i;
            m_pBuffer[cur] |= a_pBitmap->buffer[q * a_pBitmap->width + p];
        }
    }
}

void triebWerk::CFont::CreateTexture()
{
      if (m_LetterMap.GetD3D11Texture() == nullptr)
      {
          auto newTexture = m_pGraphics->CreateD3D11FontTexture(m_pBuffer, m_Width, m_Height);
          m_LetterMap.SetTexture(m_Width, m_Height, newTexture, m_pGraphics->CreateID3D11ShaderResourceViewFont(newTexture));
      }
      else
      {
          m_pGraphics->RemapTextureBuffer(m_pBuffer, m_Width, m_LetterMap.GetD3D11Texture());
      }
}
