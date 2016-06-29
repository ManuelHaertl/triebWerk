#include <CFontFace.h>

#include <CDebugLogfile.h>

triebWerk::CFontFace::CFontFace(FT_Library* a_pLibrary, const char* a_pFile, const char* a_pFileName)
{
    m_Name = a_pFileName;

    FT_Error error = FT_New_Face(*a_pLibrary, a_pFile, 0, &m_Face);

    if (error == FT_Err_Unknown_File_Format)
    {
        DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, a_pFile, " has an unsupported font format!");
    }
    else if (error != FT_Err_Ok)
    {
        DebugLogfile.LogfText(CDebugLogfile::ELogType::Error, false, a_pFile, " could not be opened, read or it's broken!");
    }
}

triebWerk::CFontFace::~CFontFace()
{
    FT_Done_Face(m_Face);
}

FT_Face& triebWerk::CFontFace::GetFace()
{
    return m_Face;
}

const std::string& triebWerk::CFontFace::GetName()
{
    return m_Name;
}
