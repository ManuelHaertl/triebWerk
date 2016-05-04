#pragma once
#include <IDrawable.h>
#include <vector>
#include <CGraphics.h>
#include <CCamera.h>
#include <CMeshDrawable.h>

namespace triebWerk
{
	class CRenderer
	{
	private:
		std::vector<IDrawable*> m_CommandList;
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

		void DrawScene();
	};
}
