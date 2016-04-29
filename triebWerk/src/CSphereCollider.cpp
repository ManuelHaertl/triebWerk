#include <CSphereCollider.h>

triebWerk::CSphereCollider::CSphereCollider()
{
}

triebWerk::CSphereCollider::~CSphereCollider()
{
}

triebWerk::ECollider::Type triebWerk::CSphereCollider::GetColliderType()
{
	return ECollider::Type();
}

void triebWerk::CSphereCollider::CreateFromVertices(const CMesh::SVertex * const a_pVertices, const size_t a_Count)
{
}
