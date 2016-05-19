#include <CTMXParser.h>

triebWerk::CTMXParser::CTMXParser()
{
}

triebWerk::CTMXParser::~CTMXParser()
{
}

bool triebWerk::CTMXParser::ParseData(const char * a_pFilePath, CTilesetMap* a_pOutTilesetMap)
{
	m_TilesetMap = a_pOutTilesetMap;
	ReadData(a_pFilePath);
	std::string name(a_pFilePath);

	m_TilesetMap->m_Map.m_MapName = name.substr(name.rfind("\\")+1, name.size() - name.rfind("\\"));

	m_TilesetMap->m_Map.m_MapName = m_TilesetMap->m_Map.m_MapName.substr(0, m_TilesetMap->m_Map.m_MapName.find("."));


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

		if (BeginLineWith(line, "<objectgroup"))
		{
			this->ReadObject(line);
		}

		if (ReachedEndOfFile())
		{
			return false;
		}

	} while (!BeginLineWith(line, "</map>"));


	CloseFile();

	return m_TilesetMap;
}

std::string triebWerk::CTMXParser::GetProportie(std::string& a_Line, const char * a_pProportieName)
{
	std::string toSearch = a_pProportieName;
	toSearch += "=\"";
	size_t startPos = a_Line.find(toSearch) + toSearch.size();
	size_t endPos = a_Line.find("\"", startPos);
	return a_Line.substr(startPos, endPos - startPos);;
}

bool triebWerk::CTMXParser::BeginLineWith(std::string& a_Line, const char * a_pLineStart)
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

bool triebWerk::CTMXParser::ExistsProperty(std::string& a_Line, const char * a_pProportieName)
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

void triebWerk::CTMXParser::ReadLayer(std::string& a_Line)
{
	CMapLayer* layer = new CMapLayer();
	layer->m_LayerHeight = (short)stoi(GetProportie(a_Line, "height"));
	layer->m_LayerWidth = (short)stoi(GetProportie(a_Line, "width"));
	layer->m_LayerName = GetProportie(a_Line, "name");
	layer->m_Indices = new short[layer->m_LayerWidth * layer->m_LayerHeight];

	bool runState = true;
	std::string line;
	size_t begin = 0;

	std::string data = GetAllData();

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
						layer->m_Indices[layer->m_IndicesIterator] = static_cast<short>(stoi(line.substr(begin, startPos - begin)));
						layer->m_IndicesIterator++;
						break;
					}

					layer->m_Indices[layer->m_IndicesIterator] = static_cast<short>(stoi(line.substr(begin, startPos - begin)));
					begin = startPos + 1;

					layer->m_IndicesIterator++;

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

void triebWerk::CTMXParser::ReadImageLayer(std::string& a_Line)
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

void triebWerk::CTMXParser::ReadTileSet(std::string& a_Line)
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

void triebWerk::CTMXParser::ReadObject(std::string& a_Line)
{
	CObjectLayer* objectLayer = new CObjectLayer();

	objectLayer->m_Name = GetProportie(a_Line, "name");
	
	do
	{
		a_Line = GetLine();

		if (BeginLineWith(a_Line, "<properties>"))
		{
			ReadProperties(&objectLayer->Properties);

			a_Line = GetLine();
		}

		if (BeginLineWith(a_Line, "<object"))
		{
			CLayerObject object;

			object.m_ID = stoi(GetProportie(a_Line, "id"));
			object.m_GID = stoi(GetProportie(a_Line, "gid"));
			object.m_X = stoi(GetProportie(a_Line, "x"));
			object.m_Y = stoi(GetProportie(a_Line, "y"));
			object.m_Width = stoi(GetProportie(a_Line, "width"));
			object.m_Height = stoi(GetProportie(a_Line, "height"));

			if (a_Line.rfind("/>") != std::string::npos)
			{
				objectLayer->m_Objects.push_back(object);
				continue;
			}

			a_Line = GetLine();

			if (BeginLineWith(a_Line, "<properties>"))
			{
				ReadProperties(&object.m_Properties);
			}

			a_Line = GetLine();

			if (BeginLineWith(a_Line, "</object"))
			{
				objectLayer->m_Objects.push_back(object);
			}
		}


	} while (!BeginLineWith(a_Line, "</objectgroup>"));

	this->m_TilesetMap->m_Layers.push_back(objectLayer);

	//a_Line = GetLine();

	//if (BeginLineWith(a_Line, "<properties>"))
	//{
	//	ReadProperties(&objectLayer->m_Properties);
	//}
	//else if (BeginLineWith(a_Line, "</object"))
	//{
	//	this->m_TilesetMap->m_Layers.push_back(objectLayer);
	//}

	//a_Line = GetLine();
	//if (BeginLineWith(a_Line, "</object"))
	//{
	//	this->m_TilesetMap->m_Layers.push_back(objectLayer);
	//}

}

//void triebWerk::CTMXParser::RecalculateTilesetLayerIndices()
//{
//	short value = 0;
//	for (size_t i = 0; i < m_TilesetMap->m_Layers.size(); i++)
//	{
//
//
//		if (m_TilesetMap->m_Layers[i]->GetType() == IMapLayer::ETypes::MapLayer)
//		{
//			CMapLayer* maplayer = (CMapLayer*)m_TilesetMap->m_Layers[i];
//
//
//			for (size_t c = 0; c < maplayer->m_Indices.size(); c++)
//			{
//				if (maplayer->m_Indices[c] > 0)
//				{
//					value = maplayer->m_Indices[c];
//					break;
//				}
//			}
//
//			for (size_t x = 0; x < m_TilesetMap->m_Tilesets.size(); x++)
//			{
//				if (value >= m_TilesetMap->m_Tilesets[x]->m_FirstGid && value <= m_TilesetMap->m_Tilesets[x]->m_TileCount + m_TilesetMap->m_Tilesets[x]->m_FirstGid)
//				{
//					maplayer->m_TilesetName = m_TilesetMap->m_Tilesets[x]->m_ImageName.substr(m_TilesetMap->m_Tilesets[x]->m_ImageName.rfind("/") + 1, m_TilesetMap->m_Tilesets[x]->m_ImageName.size() - m_TilesetMap->m_Tilesets[x]->m_ImageName.rfind("/") + 1);
//
//					for (size_t y = 0; y < maplayer->m_Indices.size(); y++)
//					{
//						if (maplayer->m_Indices[y] > 0)
//						{
//							maplayer->m_Indices[y] = maplayer->m_Indices[y] - m_TilesetMap->m_Tilesets[x]->m_FirstGid;
//						}
//					}
//				}
//			}
//		}
//	}	
//}

void triebWerk::CTMXParser::ReadMap(std::string& a_Line)
{
	m_TilesetMap->m_Map.m_Orientation = GetProportie(a_Line, "orientation");
	m_TilesetMap->m_Map.m_RenderOrder = GetProportie(a_Line, "renderorder");
	m_TilesetMap->m_Map.m_NextObjectID = (short)stoi(GetProportie(a_Line, "nextobjectid"));
	m_TilesetMap->m_Map.m_Height = (short)stoi(GetProportie(a_Line, "height"));
	m_TilesetMap->m_Map.m_Width = (short)stoi(GetProportie(a_Line, "width"));
	m_TilesetMap->m_Map.m_TileHeight = (short)stoi(GetProportie(a_Line, "tileheight"));
	m_TilesetMap->m_Map.m_TileWidth = (short)stoi(GetProportie(a_Line, "tilewidth"));
}

