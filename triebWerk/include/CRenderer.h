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

		ID3D11BlendState* m_pDefaultBlendState;
		ID3D11RasterizerState* m_pDefaultRasterizerState;
		
	public:
		CRenderer();
		~CRenderer();

	public:
		void Initialize(CGraphics* a_pGraphicsHandle, unsigned int a_ScreenWidth, unsigned int a_ScreenHeight);
		void Shutdown();

		//Camera Functions
		//--------------------------------------
		//Creates a camera which will be updated.
		//Renderer handles ownership
		CCamera* CreateCamera(const float a_Aspect, const float a_FOV, const float a_Near, const float a_Far);
		//Remove a camera from the list
		void RemoveCamera(CCamera* a_pCamera);
		//Set Camera to draw with
		void SetActiveCamera(CCamera* a_pCamera);
		//Get the camera which is the draw camera at the moment
		CCamera* GetCurrentActiveCamera();
		//--------------------------------------

		//Create Drawables
		//--------------------------------------
		//Creates a new font drawable.
		//Renderer handles ownership
		CFontDrawable* CreateFontDrawable();
		//Creates a new mesh drawable.
		//Renderer handles ownership
		CMeshDrawable* CreateMeshDrawable();
		//--------------------------------------

		//World Functions
		//Add a render command to the scene which will be drawn after calling draw scene
		void AddRenderCommand(IDrawable* a_pRenderCommand);
		//Draws all commands in buffer and resets the scene
		void DrawScene();


		//Render Targets does nothing at the moment
		CRenderTarget* AddRenderTarget(int a_Order);
	
		//Resize the Cameras and the viewports
		void ResizeRenderer(unsigned int a_ScreenWidth, unsigned int a_ScreenHeight);

	private:
		//Render the differnet drawable types
		void RenderMeshDrawables();
		void RenderFontDrawables();

		//Render pipeline functions
		void SetResources(const CMaterial* a_pMaterial);
		void SetShader(const CMaterial* a_pMaterial);
		void SetSpefificStates(const CMeshDrawable::SD3D11States* a_pMeshDrawable);

		void ResetRenderStates();

		//MeshDrawable
		//--------------------------------------
		void DrawMesh(const CMeshDrawable* a_pDrawable);
		void RenderMesh(CMeshDrawable* a_pDrawable);

		void InsertTransparent(CMeshDrawable* a_pDrawable);
		void SortTransparentObjects();

		void InstanceBatching(CMeshDrawable* a_pDrawable);
		void RenderInstancedMeshBatch(size_t a_Index);
		//--------------------------------------
		
		//MeshDrawable
		//--------------------------------------
		//Render the font buffer
		void RenderFont(CFontDrawable* a_pFont);
		//--------------------------------------
	};
}
