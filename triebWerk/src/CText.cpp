#include <CText.h>

#include <CFont.h>
#include <string.h>

#include <CEngine.h>

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

unsigned int triebWerk::CText::GetHeight() const
{
	return HEIGHT;
}

unsigned int triebWerk::CText::GetWidth() const
{
	return WIDTH;
}

triebWerk::CTexture2D * triebWerk::CText::GetTexture()
{
	return &m_Texture;
}

void triebWerk::CText::CreateTexture()
{
    FT_Error error;
	int penX = 0;
	int penY = 0;

    FT_Face face = m_pFont->GetFace();

    FT_Set_Char_Size(face, 16 * 64, 0, 300, 0);
    //FT_Set_Pixel_Sizes(face, 0, m_PixelSize);
    FT_Select_Charmap(face, FT_ENCODING_UNICODE);

    for (size_t i = 0; i < m_Text.size(); ++i)
    {
        error = FT_Load_Char(face, m_Text[i], FT_LOAD_RENDER);
        if (error)
            continue;

        DrawLetter(&face->glyph->bitmap, penX + face->glyph->bitmap_left, penY + face->glyph->bitmap_top);

		penX += face->glyph->advance.x >> 6;
		penY += face->glyph->advance.y >> 6;
    }
	
	//bool bla = true;
	//for (size_t i = 0; i < WIDTH; i++)
	//{
	//	for (size_t j = 0; j < HEIGHT; j++)
	//	{
	//		if (bla)
	//			m_Buffer[i][j] = 255;
	//		else
	//			m_Buffer[i][j] = 0;

	//		bla = !bla;
	//	}
	//}

	auto texture = CEngine::Instance().m_pGraphics->CreateD3D11FontTexture(&m_Buffer, WIDTH, HEIGHT);

	m_Texture.SetTexture(WIDTH, HEIGHT, texture, CEngine::Instance().m_pGraphics->CreateID3D11ShaderResourceViewFont(texture));
}

void triebWerk::CText::DrawLetter(FT_Bitmap* a_pBitmap, FT_Int a_X, FT_Int a_Y)
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
