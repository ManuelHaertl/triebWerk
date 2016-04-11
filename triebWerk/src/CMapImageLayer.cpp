#include <CMapImageLayer.h>
triebWerk::CMapImageLayer::CMapImageLayer()
{
}

triebWerk::CMapImageLayer::~CMapImageLayer()
{
	
}

triebWerk::IMapLayer::ETypes::Type triebWerk::CMapImageLayer::GetType()
{
	return ETypes::Type::MapImageLayer;
}
