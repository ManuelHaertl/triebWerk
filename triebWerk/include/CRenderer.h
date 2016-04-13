#pragma once
#include <IDrawable.h>
#include <vector>
#include <CRenderCommandMesh.h>
#include <CGraphics.h>

namespace triebWerk
{
	class CRenderer
	{
	private:
		std::vector<IRenderCommand*> m_CommandList;
		CGraphics* m_pGraphicsHandle;

	public:
		CRenderer();
		~CRenderer();

	public:
		void Initialize(CGraphics* a_pGraphicsHandle);
		
		void AddRenderCommand(IRenderCommand* a_pRenderCommand);

		void DrawScene();
	};
}
