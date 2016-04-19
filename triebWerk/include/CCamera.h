#pragma once
#include <DirectXMath.h>
#include <CTransform.h>
#include <d3d11.h>

namespace triebWerk
{
	class CCamera
	{
	public:
		CTransform m_Transform;

	private:
		DirectX::XMMATRIX m_ViewMatrix;
		DirectX::XMMATRIX m_ProjectionMatrix;

		unsigned int m_ScreenHeight;
		unsigned int m_ScreenWidth;
		float m_Aspect;
		float m_FOV;
		float m_NearPlane;
		float m_FarPlane;

		bool m_Modified;

		D3D11_VIEWPORT m_Viewport;

	public:
		CCamera();
		CCamera(float a_Aspect, float a_FOV, float a_Near, float a_Far, unsigned int m_ScreenHeight, unsigned int m_ScreenWidth);
		~CCamera();

	public:
		void Update();

		DirectX::XMMATRIX& GetViewMatrix();
		DirectX::XMMATRIX& GetProjection();

		void SetAspect(const float a_Aspect);
		void SetFOV(const float a_FOV);
		void SetNear(const float a_NearPlane);
		void SetFar(const float a_FarPlane);

		float GetAspect() const;
		float GetFOV() const;
		float GetNear() const;
		float GetFar() const;
	private:
		void CalculateProjection();
		void DetermineViewport();
	};
}
