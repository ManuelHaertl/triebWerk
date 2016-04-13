#pragma once
#include <IRenderCommand.h>
#include <CMesh.h>
#include <CMaterial.h>
namespace triebWerk
{
	class CRenderCommandMesh : public IRenderCommand
	{
	public:
		CMesh* m_pMesh;
		CMaterial* m_pMaterial;

	public:
		CRenderCommandMesh();
		~CRenderCommandMesh();

	public:
		ECommandType GetType() final;
		
	};
}
