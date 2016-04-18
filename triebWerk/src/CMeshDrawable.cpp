#include <CMeshDrawable.h>
#include <CEntity.h>

triebWerk::CMeshDrawable::CMeshDrawable():
	m_pMesh(nullptr)
{
	m_Type = IDrawable::EDrawableType::Mesh;
}

triebWerk::CMeshDrawable::~CMeshDrawable()
{
}

triebWerk::IRenderCommand* triebWerk::CMeshDrawable::GetRenderCommand(CEntity* a_pEntity)
{
	m_RenderCommand.m_pMaterial = &m_Material;
	m_RenderCommand.m_pMesh = m_pMesh;
	m_RenderCommand.m_Transformation = a_pEntity->m_Transform.GetTransformation();

	return &m_RenderCommand;
}

triebWerk::IDrawable::EDrawableType triebWerk::CMeshDrawable::GetType()
{
	return IDrawable::EDrawableType::Mesh;
}
