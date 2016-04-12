#include <CAABB.h>

triebWerk::CAABB::CAABB()
{
}

triebWerk::CAABB::~CAABB()
{
}

ECollider::Type triebWerk::CAABB::GetColliderType()
{
    return ECollider::Type::AABB;
}
