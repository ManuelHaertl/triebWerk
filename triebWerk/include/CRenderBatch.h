#pragma once
#include <CMeshDrawable.h>
#include <CInstancedMeshBatch.h>
#include <CFontDrawable.h>
#include <CUIDrawable.h>

namespace triebWerk
{
	class CRenderBatch
	{

	public:
		const static size_t m_MaxFonts = 1000;
		const static size_t m_MaxDrawables = 10000;
		const static size_t m_MaxInstancedMeshBatch = 100;
		const static size_t m_MaxUIElements = 200;

	public:
		//UI
		CFontDrawable** m_pFontBuffer;
		size_t m_FontCommandCount;

		//Mesh Drawing
		CMeshDrawable** m_pOpaqueMeshBuffer;
		CMeshDrawable** m_pTransparentMeshBuffer;
		CInstancedMeshBatch* m_pInstancedMeshBuffer;
		CUIDrawable** m_pUIBuffer;
		size_t m_OpaqueMeshCounter;
		size_t m_TransparentMeshCounter;
		size_t m_InstancedMeshBatchCount;
		size_t m_UIElementCount;

	public:
		CRenderBatch();
		~CRenderBatch();

	public:
		void Create(CGraphics* a_pGraphics);
		void Free();
		void Reset();
	};
}