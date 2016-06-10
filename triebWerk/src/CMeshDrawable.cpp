#include <CMeshDrawable.h>
#include <CEntity.h>

triebWerk::CMeshDrawable::CMeshDrawable() :
	m_pMesh(nullptr),
	m_DrawType(CMeshDrawable::EDrawType::DrawIndexedInstanced),
	m_RenderMode(CMeshDrawable::ERenderMode::Opaque),
	m_Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
	m_Stride(sizeof(CMesh::SVertex))
{
	m_Type = IDrawable::EDrawableType::Mesh;

	m_D3DStates.m_pBlendState = nullptr;
	m_D3DStates.m_pRasterizerState = nullptr;
}

triebWerk::CMeshDrawable::~CMeshDrawable()
{
	if (m_D3DStates.m_pRasterizerState != nullptr)
		m_D3DStates.m_pRasterizerState->Release();
	if (m_D3DStates.m_pBlendState != nullptr)
		m_D3DStates.m_pBlendState->Release();
}

bool triebWerk::CMeshDrawable::IsValidDrawable(const CMeshDrawable * a_pDrawableToTest)
{
	if (a_pDrawableToTest->m_pMesh == nullptr || a_pDrawableToTest->m_Material.m_ID.GetHash() == 0 || a_pDrawableToTest->IsActive() == false )
	{
		return false;
	}
	else
	{
		return true;
	}
}

triebWerk::IDrawable::EDrawableType triebWerk::CMeshDrawable::GetType()
{
	return IDrawable::EDrawableType::Mesh;
}

void triebWerk::CMeshDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{
	m_Transformation = a_rTransform;
}
