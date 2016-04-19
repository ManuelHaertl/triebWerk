#include <CRenderCommandMesh.h>

triebWerk::CRenderCommandMesh::CRenderCommandMesh() :
	m_pMaterial(nullptr),
	m_pMesh(nullptr),
	m_DrawType(triebWerk::IRenderCommand::EDrawType::Draw),
	m_Topology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
	m_Stride(sizeof(CMesh::SVertex))
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
