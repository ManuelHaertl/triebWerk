#include <CTilesetMap.h>

triebWerk::CTilesetMap::CTilesetMap()
{
}

triebWerk::CTilesetMap::~CTilesetMap()
{
}

void triebWerk::CTilesetMap::ClearMap()
{
	for each (IMapLayer* layer in m_Layers)
	{
		delete layer;
	}

	for each (CTileset* tileset in m_Tilesets)
	{
		delete tileset;
	}

	m_Layers.clear();
	m_Tilesets.clear();
}
