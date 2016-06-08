#include <CFontManager.h>

#include <CDebugLogfile.h>


triebWerk::CFontManager::CFontManager()
{
}

triebWerk::CFontManager::~CFontManager()
{
}

bool triebWerk::CFontManager::Initialize()
{
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

triebWerk::CFont* triebWerk::CFontManager::CreateEmptyFont()
{
    CFont* pFont = new CFont(&m_Library);
    return pFont;
}
