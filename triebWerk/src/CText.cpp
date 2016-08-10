#include <CText.h>


triebWerk::CText::CText()
    : m_Text()
    , m_pFont(nullptr)
    , m_LineSpacing(1.0f)
    , m_pLetterInfo(nullptr)
    , m_LetterCount(0)
    , m_Width(0)
    , m_Height(0)
    , m_TextAlign(ETextAlign::MiddleCenter)
{

}

triebWerk::CText::~CText()
{
    if (m_pLetterInfo != nullptr)
        delete[] m_pLetterInfo;
}

void triebWerk::CText::Set(CFont* a_pFont, const char* a_pText, const float a_LineSpacing)
{
    m_Text = a_pText;
    m_pFont = a_pFont;
    m_LineSpacing = a_LineSpacing;
    MakeTextToValidIndices();
    CreateLetterInfo();
}

void triebWerk::CText::Set(CFont* a_pFont, std::string a_Text, const float a_LineSpacing)
{
    m_Text = a_Text;
    m_pFont = a_pFont;
    m_LineSpacing = a_LineSpacing;
    MakeTextToValidIndices();
    CreateLetterInfo();
}

void triebWerk::CText::SetFont(CFont* a_pFont)
{
    m_pFont = a_pFont;
    CreateLetterInfo();
}

void triebWerk::CText::SetText(const char* a_pText)
{
    m_Text = a_pText;
    MakeTextToValidIndices();
    CreateLetterInfo();
}

void triebWerk::CText::SetText(const std::string a_Text)
{
    m_Text = a_Text;
    MakeTextToValidIndices();
    CreateLetterInfo();
}

void triebWerk::CText::SetLineSpacing(const float a_LineSpacing)
{
    m_LineSpacing = a_LineSpacing;
    CreateLetterInfo();
}

void triebWerk::CText::SetTextAlign(const ETextAlign a_TextAlign)
{
    m_TextAlign = a_TextAlign;
    CreateLetterInfo();
}

void triebWerk::CText::CreateLetterInfo()
{
	m_LetterCount = m_Text.size();

	// delete the old letter buffer
	if (m_pLetterInfo != nullptr)
	{
		delete[] m_pLetterInfo;
		m_pLetterInfo = nullptr;
	}

	// check that there is at least 1 char
	if (m_LetterCount == 0)
		return;

	// create a new buffer
	m_pLetterInfo = new SLetterInfo[m_LetterCount];

	CalculateWidthAndHeight();

	float currentWidth = 0.0f;
	float currentHeight = 0.0f;

	switch (m_TextAlign)
	{
	case ETextAlign::TopCenter:
		currentWidth -= m_Width / 2.0f;
		break;
	case ETextAlign::TopRight:
		currentWidth -= m_Width;
		break;
	case ETextAlign::MiddleLeft:
		currentHeight += m_Height / 2.0f;
		break;
	case ETextAlign::MiddleCenter:
		currentWidth -= m_Width / 2.0f;
		currentHeight += m_Height / 2.0f;
		break;
	case ETextAlign::MiddleRight:
		currentWidth -= m_Width;
		currentHeight += m_Height / 2.0f;
		break;
	case ETextAlign::BottomLeft:
		currentHeight += m_Height;
		break;
	case ETextAlign::BottomCenter:
		currentWidth -= m_Width / 2.0f;
		currentHeight += m_Height;
		break;
	case ETextAlign::BottomRight:
		currentWidth -= m_Width;
		currentHeight += m_Height;
		break;
	}

	for (size_t i = 0; i < m_LetterCount; ++i)
	{
		SLetterCoordinate letter = m_pFont->m_LetterCoordinates[m_Text[i]];

		m_pLetterInfo[i].letterCoordinate = letter;
		m_pLetterInfo[i].offsetX = currentWidth;
		m_pLetterInfo[i].offsetY = currentHeight;

		currentWidth += (m_pFont->m_LetterCoordinates[m_Text[i]].width * m_LineSpacing) / 2;
		if (i + 1 < m_LetterCount)
			currentWidth += (m_pFont->m_LetterCoordinates[m_Text[i + 1]].width * m_LineSpacing) / 2;
	}
}

void triebWerk::CText::CalculateWidthAndHeight()
{
    m_Width = 0.0f;
    m_Height = 0.0f;

    for (size_t i = 0; i < m_LetterCount; ++i)
    {
        m_Width += m_pFont->m_LetterCoordinates[m_Text[i]].width * m_LineSpacing;
        if (m_pFont->m_LetterCoordinates[m_Text[i]].height > m_Height)
            m_Height = m_pFont->m_LetterCoordinates[m_Text[i]].height;
    }
}

void triebWerk::CText::MakeTextToValidIndices()
{
    size_t count = m_Text.size();
    for (size_t i = 0; i < count; ++i)
    {
        char& current = m_Text[i];
        current -= 32;

        if (current < 0 || current >= 94)
            current = 0;
    }
}
