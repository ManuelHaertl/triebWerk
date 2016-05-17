#include <CMapLayer.h>

triebWerk::CMapLayer::CMapLayer() :
	m_Indices(nullptr),
	m_IndicesIterator(0)
{

}

triebWerk::CMapLayer::~CMapLayer()
{
	if(m_Indices != nullptr)
		delete m_Indices;
}

triebWerk::IMapLayer::ETypes::Type triebWerk::CMapLayer::GetType()
{
	return ETypes::Type::MapLayer;
}
