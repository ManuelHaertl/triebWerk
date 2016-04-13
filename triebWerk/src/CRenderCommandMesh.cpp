#include <CRenderCommandMesh.h>

triebWerk::CRenderCommandMesh::CRenderCommandMesh() :
	m_pMaterial(nullptr),
	m_pMesh(nullptr)
{
	m_CommandType = ECommandType::Mesh;
}

triebWerk::CRenderCommandMesh::~CRenderCommandMesh()
{
}

triebWerk::IRenderCommand::ECommandType triebWerk::CRenderCommandMesh::GetType()
{
	return ECommandType::Mesh;
}
