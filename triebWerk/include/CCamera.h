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

		DirectX::XMMATRIX m_UIViewMatrix;
		DirectX::XMMATRIX m_UIProjectionMatrix;

		unsigned int m_ScreenHeight;
		unsigned int m_ScreenWidth;
		float m_Aspect;
		float m_FOV;
		float m_NearPlane;
		float m_FarPlane;

		bool m_Modified;

		D3D11_VIEWPORT m_Viewport;

		float m_TimeToShake;
		float m_ShakePower;
		DirectX::XMVECTOR m_ShakeStartPosition;
		DirectX::XMVECTOR m_BufferPosition;
		bool m_IsShaking;

	public:
		CCamera();
		CCamera(float a_Aspect, float a_FOV, float a_Near, float a_Far, unsigned int a_ScreenHeight, unsigned int a_ScreenWidth);
		~CCamera();

	public:
		void Update();

		//Resize the aspect and the ui projection
		void Resize(unsigned int a_NewScreenWidth, unsigned int a_NewScreenHeight);

		void SetScreenShake(const float a_ShakeStrenght, const float a_ShakeTime);

		DirectX::XMMATRIX& GetViewMatrix();
		DirectX::XMMATRIX& GetProjection();
		DirectX::XMMATRIX& GetUIProjection();

		void SetAspect(const float a_Aspect);
		void SetFOV(const float a_FOV);
		void SetNear(const float a_NearPlane);
		void SetFar(const float a_FarPlane);

		float GetAspect() const;
		float GetFOV() const;
		float GetNear() const;
		float GetFar() const;

	private:
        void CalculateView();
		void CalculateProjection();
		void CalculateUIProjection();
		
		void UpdateScreenShake(const float a_DeltaTimer);
	};
}
