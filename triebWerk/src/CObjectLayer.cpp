#include <CObjectLayer.h>

triebWerk::CObjectLayer::CObjectLayer()
{
}

triebWerk::CObjectLayer::~CObjectLayer()
{
}

triebWerk::IMapLayer::ETypes::Type triebWerk::CObjectLayer::GetType()
{
	return ETypes::Type::ObjectLayer;
}
