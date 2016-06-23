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
#include <CRenderBatch.h>
#include <CPostEffectDrawable.h>

namespace triebWerk
{
	class CRenderer
	{
	private:
		const size_t m_MaxRenderTargetCount = 4;
		const size_t m_MaxPostEffects = 30;

	private:
		//General
		CRenderTarget* m_pRenderTargetList;
		size_t m_RenderTargetCounter;
		size_t m_CommandCounter;

		//PostEffects
		CPostEffectDrawable** m_pPostEffectBuffer;
		CPostEffectDrawable* m_pDefaultPostEffect;
		size_t m_PostEffectCounter;

		//Render Target to draw with
		int m_ActiveRenderTargetSlot;

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
		//Creates a new mesh drawable.
		//Renderer handles ownership
		CPostEffectDrawable* CreatePostEffecthDrawable();
		//--------------------------------------

		//World Functions
		//Add a render command to the scene which will be drawn after calling draw scene
		void AddRenderCommand(IDrawable* a_pRenderCommand);
		//Draws all commands in buffer and resets the scene
		void DrawScene();


		//Render Target
		CRenderTarget* GetRenderTarget(unsigned int a_Slot);
	
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

		//RenderTarget
		//--------------------------------------
		void DrawRenderTarget(CRenderTarget* a_pRenderTarget);
		//--------------------------------------
		//MeshDrawable
		//--------------------------------------
		void DrawMesh(const CMeshDrawable* a_pDrawable);
		void RenderMesh(CMeshDrawable* a_pDrawable);

		void InsertTransparent(CMeshDrawable* a_pDrawable);
		void SortTransparentObjects();

		void InstanceBatching(CMeshDrawable* a_pDrawable, const unsigned int a_RenderTargetSlot);
		void RenderInstancedMeshBatch(size_t a_Index);
		//--------------------------------------
		
		//MeshDrawable
		//--------------------------------------
		//Render the font buffer
		void RenderFont(CFontDrawable* a_pFont);
		//--------------------------------------
	};
}
