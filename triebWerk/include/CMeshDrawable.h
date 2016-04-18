#pragma once
#include <IDrawable.h>
#include <CMaterial.h>
#include <CMesh.h>
#include <CRenderCommandMesh.h>

namespace triebWerk
{
	class CMeshDrawable : public IDrawable
	{
	public:
		CMaterial m_Material;
		CMesh* m_pMesh;

	private:
		CRenderCommandMesh m_RenderCommand;

	public:
		CMeshDrawable();
		~CMeshDrawable();

	public:
		IRenderCommand* GetRenderCommand(CEntity* a_pThisEntity) final;
		EDrawableType GetType() final;
	};
}
