#include <CFileWriter.h>
#include <Windows.h>

triebWerk::CFileWriter::CFileWriter()
	: m_pFile(nullptr)
{
}

triebWerk::CFileWriter::~CFileWriter()
{
}

bool triebWerk::CFileWriter::CreateSaveFile(const char * a_pPath)
{
	std::string t = a_pPath;
	auto e = t.find_last_of("\\");
	t.resize(e+1);

	CreateDirectory(t.c_str(), NULL);

	fopen_s(&m_pFile, a_pPath, "w");
	if (m_pFile == nullptr)
		return false;
	else
		return true;
}

void triebWerk::CFileWriter::SetParams(const std::string & a_rKey, const std::string & a_rValue)
{
	//pl_Acceleration = 250.0
	std::string line = a_rKey;
	line += " = ";
	line += a_rValue;
    line += "\n";

	fwrite(line.c_str(), line.size(), 1, m_pFile);
}

void triebWerk::CFileWriter::SaveFile()
{
	fclose(m_pFile);
}
