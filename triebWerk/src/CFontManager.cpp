#include <CFontManager.h>

#include <CDebugLogfile.h>
#include <CGraphics.h>

triebWerk::CFontManager::CFontManager() :
    m_pGraphics(nullptr),
    m_DPIX(92),
    m_DPIY(92)
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

triebWerk::CText* triebWerk::CFontManager::CreateText(const char* a_pText, CFont* a_pFont, const unsigned int a_PointSize)
{
    CText* pText = new CText(m_pGraphics, m_DPIX, m_DPIY);
    pText->Update(a_pText, a_pFont, a_PointSize);
    return pText;
}

triebWerk::CText * triebWerk::CFontManager::CreateText(const std::string a_Text, CFont * a_pFont, const unsigned int a_PointSize)
{
    CText* pText = new CText(m_pGraphics, m_DPIX, m_DPIY);
    pText->Update(a_Text, a_pFont, a_PointSize);
    return pText;
}
