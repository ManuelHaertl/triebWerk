#pragma once
#include <vector>
#include <CFileReader.h>
#include <CTilesetMap.h>

namespace triebWerk
{
class CTMXParser : public CFileReader
{
private:
	CTilesetMap* m_TilesetMap;

public:
	CTMXParser();
	~CTMXParser();

public:
	CTilesetMap* ParseData(const char* a_pFilePath);

private:
        std::string GetProportie(std::string& a_Line, const char* a_pProportieName);
	bool BeginLineWith(std::string& a_Line, const char* a_pLineStart);
	bool ExistsProperty(std::string& a_Line, const char* a_pProportieName);

	void ReadLayer(std::string& a_Line);
	void ReadImageLayer(std::string& a_Line);
	void ReadTileSet(std::string& a_Line);      
	void ReadMap(std::string& a_Line);
	void ReadProperties(std::unordered_map<std::string, std::string>* a_pProp);
	void ReadObject(std::string& a_Line);

	//TODO: Fix Index count
	void RecalculateTilesetLayerIndices();
};
}
