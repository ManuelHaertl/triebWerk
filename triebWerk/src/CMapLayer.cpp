#include <CMapLayer.h>

triebWerk::CMapLayer::CMapLayer()
{
}

triebWerk::CMapLayer::~CMapLayer()
{
}

triebWerk::IMapLayer::ETypes::Type triebWerk::CMapLayer::GetType()
{
	return ETypes::Type::MapLayer;
}
