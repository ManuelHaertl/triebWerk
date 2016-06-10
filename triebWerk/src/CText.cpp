#include <CText.h>

#include <CFont.h>
#include <CGraphics.h>
#include <string.h>


triebWerk::CText::CText(CGraphics* a_pGraphics, unsigned int a_DPIX, unsigned int a_DPIY, unsigned char* a_pBuffer) :
    m_Text(),
    m_pFont(nullptr),
    m_PointSize(12),
    m_LineSpacing(1.0f),
    m_IsModified(false),
    m_Width(800),
    m_Height(600),
    m_DPIX(a_DPIX),
    m_DPIY(a_DPIY),
    m_pBuffer(a_pBuffer),
    m_Texture(),
    m_pGraphics(a_pGraphics)
{
    
}

triebWerk::CText::~CText()
{
    
}

void triebWerk::CText::Update(const char* a_pText, CFont* a_pFont, const unsigned int a_PointSize)
{
    m_Text = a_pText;

    if (a_pFont != nullptr)
        m_pFont = a_pFont;

    if (a_PointSize != 0)
        m_PointSize = a_PointSize;

    CreateTexture();
}

void triebWerk::CText::Update(const std::string a_Text, CFont* a_pFont, const unsigned int a_PointSize)
{
    m_Text = a_Text.c_str();

    if (a_pFont != nullptr)
        m_pFont = a_pFont;

    if (a_PointSize != 0)
        m_PointSize = a_PointSize;

    CreateTexture();
}

unsigned int triebWerk::CText::GetWidth() const
{
    return m_Width;
}

unsigned int triebWerk::CText::GetHeight() const
{
	return m_Height;
}

triebWerk::CTexture2D * triebWerk::CText::GetTexture()
{
	return &m_Texture;
}

void triebWerk::CText::CreateTexture()
{
    FT_Error error;
	int penX = 0;
	int penY = 100;

    FT_Face face = m_pFont->GetFace();
    FT_GlyphSlot glyph = face->glyph;

    FT_Set_Char_Size(face, 0, m_PointSize * 64, m_DPIX, m_DPIY);

    memset(m_pBuffer, 0, m_Height * m_Width);

    for (size_t i = 0; i < m_Text.size(); ++i)
    {
        if (m_Text[i] == '\n')
        {
            penX = 0;
            penY += (unsigned int)(face->max_advance_height * m_LineSpacing) >> 6;
            continue;
        }

        error = FT_Load_Char(face, m_Text[i], FT_LOAD_RENDER);
        if (error)
            continue;

        DrawLetter(
            &glyph->bitmap,
            penX + glyph->bitmap_left,
            penY - glyph->bitmap_top);

		penX += glyph->advance.x >> 6;
    }

    // check if there is a an old texture to release
    auto texture = m_Texture.GetD3D11Texture();
    if (texture != nullptr)
        texture->Release();
    auto shaderResource = m_Texture.GetShaderResourceView();
    if (shaderResource != nullptr)
        shaderResource->Release();

    // create the new texture
    auto newTexture = m_pGraphics->CreateD3D11FontTexture(m_pBuffer, m_Width, m_Height);
	m_Texture.SetTexture(m_Width, m_Height, newTexture, m_pGraphics->CreateID3D11ShaderResourceViewFont(newTexture));
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
            if (i < 0 || j < 0 || i >= m_Width || j >= m_Height)
                continue;

            size_t cur = j * m_Width + i;
            m_pBuffer[cur] |= a_pBitmap->buffer[q * a_pBitmap->width + p];
        }
    }
}
