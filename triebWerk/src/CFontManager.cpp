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

FT_Library* triebWerk::CFontManager::GetLibrary()
{
    return &m_Library;
}

triebWerk::CText * triebWerk::CFontManager::CreateText()
{
    CText* pText = new CText();
    return pText;
}
