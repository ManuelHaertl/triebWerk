#pragma once
#include <IRenderCommand.h>
#include <CMesh.h>
#include <CMaterial.h>
#include <DirectXMath.h>

namespace triebWerk
{
	class CRenderCommandMesh : public IRenderCommand
	{
	public:
		CMesh* m_pMesh;
		CMaterial* m_pMaterial;
		DirectX::XMMATRIX m_Transformation;
	public:
		CRenderCommandMesh();
		~CRenderCommandMesh();

	public:
		ECommandType GetType() final;
		
	};
}
