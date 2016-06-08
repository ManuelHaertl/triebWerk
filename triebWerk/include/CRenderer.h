#pragma once
#include <IDrawable.h>
#include <vector>
#include <CGraphics.h>
#include <CCamera.h>
#include <CMeshDrawable.h>
#include <CInstancedMeshBatch.h>
#include <unordered_map>
#include <CRenderTarget.h>
#include <CFontDrawable.h>

namespace triebWerk
{
	class CRenderer
	{
	private:

	private:
		const size_t m_MaxFonts = 1000;
		const size_t m_MaxDrawables = 10000;
		const size_t m_MaxInstancedMeshBatch = 100;

	private:
		//General
		CRenderTarget* m_pRenderTargetList;

		//UI
		CFontDrawable** m_pFontBuffer;
		size_t m_FontCommandCount;

		//Mesh Drawing
		IDrawable** m_pCommandBuffer;
		CMeshDrawable** m_pOpaqueMeshBuffer;
		CMeshDrawable** m_pTransparentMeshBuffer;
		CInstancedMeshBatch* m_pInstancedMeshBuffer;
		size_t m_RenderTargetCounter;
		size_t m_CommandCounter;
		size_t m_OpaqueMeshCounter;
		size_t m_TransparentMeshCounter;
		size_t m_InstancedMeshBatchCount;

		std::vector<CCamera*> m_CameraBuffer;
		CGraphics* m_pGraphicsHandle;
		CCamera* m_pCurrentCamera;

		unsigned int m_ScreenHeight;
		unsigned int m_ScreenWidth;
		
	public:
		CRenderer();
		~CRenderer();

	public:
		void Initialize(CGraphics* a_pGraphicsHandle, unsigned int a_ScreenWidth, unsigned int a_ScreenHeight);
		void Shutdown();

		//Camera Functions
		CCamera* CreateCamera(const float a_Aspect, const float a_FOV, const float a_Near, const float a_Far);
		void RemoveCamera(CCamera* a_pCamera);
		void SetActiveCamera(CCamera* a_pCamera);
		CCamera* GetCurrentActiveCamera();

		CMeshDrawable* CreateMeshDrawable();

		//Command Functions
		void AddRenderCommand(IDrawable* a_pRenderCommand);

		void RenderMeshDrawables();

		void RenderMesh(CMeshDrawable* a_pDrawable);
		void RenderInstancedMeshBatch(size_t a_Index);

		void InsertTransparent(CMeshDrawable* a_pDrawable);

		void SortTransparentObjects();

		CRenderTarget* AddRenderTarget(int a_Order);

		void InstanceBatching(CMeshDrawable* a_pDrawable);

		void DrawScene();
	};
}
