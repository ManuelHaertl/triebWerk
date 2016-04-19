#pragma once
#include <CCamera.h>
#include <DirectXMath.h>

namespace triebWerk
{
	class CDebugCamera
	{
	private:
		triebWerk::CCamera* m_pMainCamera;
		float m_RotationX;
		float m_RotationY;
		DirectX::XMINT2 m_PreviousMousePosition;

		float m_ZoomSpeed;

	public:
		CDebugCamera();
		~CDebugCamera();

	public:
		void Update();

		void SetZoomSpeed(float a_Speed);

	};
}