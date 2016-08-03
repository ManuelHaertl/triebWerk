#include <CFontManager.h>

#include <CDebugLogfile.h>
#include <CFontFace.h>
#include <CFont.h>
#include <CGraphics.h>
#include <CResourceManager.h>
#include <CText.h>

triebWerk::CFontManager::CFontManager()
    : m_pGraphics(nullptr)
    , m_DPIX(92)
    , m_DPIY(92)
{
}

triebWerk::CFontManager::~CFontManager()
{
}

bool triebWerk::CFontManager::Initialize(CGraphics* a_pGraphics, const unsigned int a_DPIX, const unsigned int a_DPIY)
{
    m_pGraphics = a_pGraphics;
    
    if (a_DPIX != 0 && a_DPIY != 0)
    {
        m_DPIX = a_DPIX;
        m_DPIY = a_DPIY;
    }

    FT_Error error = FT_Init_FreeType(&m_Library);
    if (error != FT_Err_Ok)
    {
        DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Failed initializing FreeType!");
        return false;
    }
    
    return true;
}

void triebWerk::CFontManager::Shutdown()
{
    size_t size = m_Fonts.size();
    for (size_t i = 0; i < size; ++i)
    {
        delete m_Fonts[i];
    }
    m_Fonts.clear();

    FT_Error error = FT_Done_FreeType(m_Library);
    if (error != FT_Err_Ok)
    {
        DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, "Failed to shutdown FreeType!");
    }
}

FT_Library* triebWerk::CFontManager::GetLibrary()
{
    return &m_Library;
}

triebWerk::CFont* triebWerk::CFontManager::LoadFont(CFontFace* a_pFontFace, const unsigned int a_PointSize)
{
    size_t size = m_Fonts.size();
    for (size_t i = 0; i < size; ++i)
    {
        CFont* font = m_Fonts[i];
        if (font->GetFontFace() == a_pFontFace && font->GetPointSize() == a_PointSize)
        {
            return font;
        }
    }
    
    CFont* font = new CFont(m_pGraphics, m_DPIX, m_DPIY, a_pFontFace, a_PointSize);
    m_Fonts.push_back(font);
    return font;
}

void triebWerk::CFontManager::UnloadFont(const CFontFace* a_pFontFace, const unsigned int a_PointSize)
{
    size_t size = m_Fonts.size();
    for (size_t i = 0; i < size; ++i)
    {
        CFont* font = m_Fonts[i];
        if (font->GetFontFace() == a_pFontFace && font->GetPointSize() == a_PointSize)
        {
            delete font;
            m_Fonts.erase(m_Fonts.begin() + i);
            return;
        }
    }
}

triebWerk::CFont* triebWerk::CFontManager::GetFont(CFontFace* a_pFontFace, const unsigned int a_PointSize)
{
    size_t size = m_Fonts.size();
    for (size_t i = 0; i < size; ++i)
    {
        CFont* font = m_Fonts[i];
        if (font->GetFontFace() == a_pFontFace && font->GetPointSize() == a_PointSize)
        {
            return font;
        }
    }

    return nullptr;
}

triebWerk::CText* triebWerk::CFontManager::CreateText()
{
    CText* pText = new CText();
    return pText;
}
