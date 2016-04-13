#include <CAABBCollider.h>

triebWerk::CAABBCollider::CAABBCollider()
{
}

triebWerk::CAABBCollider::~CAABBCollider()
{
}

triebWerk::ECollider::Type triebWerk::CAABBCollider::GetColliderType()
{
    return ECollider::Type::AABB;
}
