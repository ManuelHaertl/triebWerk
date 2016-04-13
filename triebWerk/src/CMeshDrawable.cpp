#include <CMeshDrawable.h>

triebWerk::CMeshDrawable::CMeshDrawable():
	m_pMesh(nullptr)
{
	m_Type = IDrawable::EDrawableType::Mesh;
}

triebWerk::CMeshDrawable::~CMeshDrawable()
{
}

triebWerk::IRenderCommand* triebWerk::CMeshDrawable::GetRenderCommand()
{
	m_RenderCommand.m_pMaterial = &m_Material;
	m_RenderCommand.m_pMesh = m_pMesh;

	return &m_RenderCommand;
}

triebWerk::IDrawable::EDrawableType triebWerk::CMeshDrawable::GetType()
{
	return IDrawable::EDrawableType::Mesh;
}
