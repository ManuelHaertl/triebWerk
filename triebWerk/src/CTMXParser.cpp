#include <CTMXParser.h>

triebWerk::CTMXParser::CTMXParser()
{
}

triebWerk::CTMXParser::~CTMXParser()
{
}

triebWerk::CTilesetMap* triebWerk::CTMXParser::ParseData(const char * a_pFilePath)
{
	m_TilesetMap = new CTilesetMap();
	ReadData(a_pFilePath);
	std::string line;

	//Main Parse Loop whitch checks the different Layer Types
	do
	{
		line = GetLine();
		
		if (BeginLineWith(line, "<map"))
		{
			this->ReadMap(line);
		}

		if (BeginLineWith(line, "<tileset"))
		{
			this->ReadTileSet(line);
		}

		if (BeginLineWith(line, "<layer"))
		{
			this->ReadLayer(line);
		}

		if (BeginLineWith(line, "<imagelayer"))
		{
			this->ReadImageLayer(line);
		}

		if (ReachedEndOfFile())
		{
			return nullptr;
		}

	} while (!BeginLineWith(line, "</map>"));

	this->RecalculateTilesetLayerIndices();

	CloseFile();

	return m_TilesetMap;
}

std::string triebWerk::CTMXParser::GetProportie(std::string a_Line, const char * a_pProportieName)
{
	std::string toSearch = a_pProportieName;
	toSearch += "=\"";
	size_t startPos = a_Line.find(toSearch) + toSearch.size();
	size_t endPos = a_Line.find("\"", startPos);
	return a_Line.substr(startPos, endPos - startPos);;
}

bool triebWerk::CTMXParser::BeginLineWith(std::string a_Line, const char * a_pLineStart)
{
	size_t startPos = a_Line.find(a_pLineStart);

	if (startPos != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool triebWerk::CTMXParser::ExistsProperty(std::string a_Line, const char * a_pProportieName)
{
	std::string toSearch = a_pProportieName;
	toSearch += "=\"";
	size_t startPos = a_Line.find(toSearch);
	if (startPos == std::string::npos)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void triebWerk::CTMXParser::ReadLayer(std::string a_Line)
{
	CMapLayer* layer = new CMapLayer();
	layer->m_LayerHeight = (short)stoi(GetProportie(a_Line, "height"));
	layer->m_LayerWidth = (short)stoi(GetProportie(a_Line, "width"));
	layer->m_LayerName = GetProportie(a_Line, "name");

	bool runState = true;
	std::string line;
	size_t begin = 0;

	do
	{
		line = GetLine();

		if (BeginLineWith(line, "<data"))
		{
			do
			{
				line = GetLine();
				if (BeginLineWith(line, "</data>"))
				{
					break;
				}
				do
				{
					size_t startPos = line.find(",", begin);

					if (startPos == std::string::npos)
					{
						startPos = line.size();
						layer->m_Indices.push_back(static_cast<short>(stoi(line.substr(begin, startPos - begin))));
						break;
					}

					layer->m_Indices.push_back(static_cast<short>(stoi(line.substr(begin, startPos - begin))));
					begin = startPos + 1;
					if (line.size() == begin)
					{
						begin = 0;
						break;
					}
				} while (runState);
            } while (!BeginLineWith(line, "</data>"));
		}

		if (BeginLineWith(line, "<properties>"))
		{
			this->ReadProperties(&layer->m_Properties);
		}

	} while (!BeginLineWith(line, "</layer>"));

	this->m_TilesetMap->m_Layers.push_back(layer);
}

void triebWerk::CTMXParser::ReadImageLayer(std::string a_Line)
{
	CMapImageLayer* tileset = new CMapImageLayer();

	tileset->m_Name = GetProportie(a_Line, "name");

	if (ExistsProperty(a_Line, "x"))
	{
		tileset->m_PositionX = (short)stoi(GetProportie(a_Line, "x"));
	}
	else
	{
		tileset->m_PositionX = 0;
	}

	if (ExistsProperty(a_Line, "y"))
	{
		tileset->m_PositionY = (short)stoi(GetProportie(a_Line, "y"));
	}
	else
	{
		tileset->m_PositionY = 0;
	}

	std::string line;

	do
	{
		line = GetLine();
		if (BeginLineWith(line, "<image"))
		{
			tileset->m_ImageName = GetProportie(line, "source");
		}

		if (BeginLineWith(line, "<properties>"))
		{
			ReadProperties(&tileset->Properties);
		}
	} while (!BeginLineWith(line, "</imagelayer>"));


	this->m_TilesetMap->m_Layers.push_back(tileset);
}

void triebWerk::CTMXParser::ReadTileSet(std::string a_Line)
{
	CTileset* tileset = new CTileset();

	tileset->m_FirstGid = (short)stoi(GetProportie(a_Line, "firstgid"));
	tileset->m_TileWidth = (short)stoi(GetProportie(a_Line, "tilewidth"));
	tileset->m_TileHeight = (short)stoi(GetProportie(a_Line, "tileheight"));
	tileset->m_TileCount = (short)stoi(GetProportie(a_Line, "tilecount"));
 	tileset->m_TilesetName = GetProportie(a_Line, "name");
	std::string line;
	
	do
	{
		 line = GetLine();
		if (BeginLineWith(line, "<image"))
		{
			tileset->m_ImageName = GetProportie(line, "source");
			tileset->m_ImageHeight = (short)stoi(GetProportie(line, "height"));
			tileset->m_ImageWidth = (short)stoi(GetProportie(line, "width"));
		}

		if (BeginLineWith(line, "<properties>"))
		{
			ReadProperties(&tileset->m_Properties);
		}
	} while (!BeginLineWith(line, "</tileset>"));

	this->m_TilesetMap->m_Tilesets.push_back(tileset);
}

void triebWerk::CTMXParser::ReadProperties(std::unordered_map<std::string, std::string>* a_pProp)
{
	bool runState = true;

	std::string line;

	do
	{
		line = GetLine();
		if (BeginLineWith(line, "</properties>"))
		{
			break;
		}
		CTilesetMap::PropertyPair temp = CTilesetMap::PropertyPair(GetProportie(line, "name"), GetProportie(line, "value"));
		a_pProp->insert(temp);
	} while (runState);
}

void triebWerk::CTMXParser::RecalculateTilesetLayerIndices()
{
	short value = 0;
	for (size_t i = 0; i < m_TilesetMap->m_Layers.size(); i++)
	{


		if (m_TilesetMap->m_Layers[i]->GetType() == IMapLayer::ETypes::MapLayer)
		{
			CMapLayer* maplayer = (CMapLayer*)m_TilesetMap->m_Layers[i];


			for (size_t c = 0; c < maplayer->m_Indices.size(); c++)
			{
				if (maplayer->m_Indices[c] > 0)
				{
					value = maplayer->m_Indices[c];
					break;
				}
			}

			for (size_t x = 0; x < m_TilesetMap->m_Tilesets.size(); x++)
			{
				if (value >= m_TilesetMap->m_Tilesets[x]->m_FirstGid && value <= m_TilesetMap->m_Tilesets[x]->m_TileCount + m_TilesetMap->m_Tilesets[x]->m_FirstGid)
				{
					maplayer->m_TilesetName = m_TilesetMap->m_Tilesets[x]->m_ImageName.substr(m_TilesetMap->m_Tilesets[x]->m_ImageName.rfind("/") + 1, m_TilesetMap->m_Tilesets[x]->m_ImageName.size() - m_TilesetMap->m_Tilesets[x]->m_ImageName.rfind("/") + 1);

					for (size_t y = 0; y < maplayer->m_Indices.size(); y++)
					{
						if (maplayer->m_Indices[y] > 0)
						{
							maplayer->m_Indices[y] = maplayer->m_Indices[y] - m_TilesetMap->m_Tilesets[x]->m_FirstGid;
						}
					}
				}
			}
		}
	}	
}

void triebWerk::CTMXParser::ReadMap(std::string a_Line)
{
	m_TilesetMap->m_Map.m_Orientation = GetProportie(a_Line, "orientation");
	m_TilesetMap->m_Map.m_RenderOrder = GetProportie(a_Line, "renderorder");
	m_TilesetMap->m_Map.m_NextObjectID = (short)stoi(GetProportie(a_Line, "nextobjectid"));
	m_TilesetMap->m_Map.m_Height = (short)stoi(GetProportie(a_Line, "height"));
	m_TilesetMap->m_Map.m_Width = (short)stoi(GetProportie(a_Line, "width"));
	m_TilesetMap->m_Map.m_TileHeight = (short)stoi(GetProportie(a_Line, "tileheight"));
	m_TilesetMap->m_Map.m_TileWidth = (short)stoi(GetProportie(a_Line, "tilewidth"));
}
