#pragma once
#include <CCamera.h>
#include <DirectXMath.h>

namespace triebWerk
{
	class CDebugCamera
	{
	private:
        const float RotateSpeed = 0.3f;
        const float MovementSpeed = 10.0f;
        const float SlowMovementSpeedFactor = 0.2f;
        const float FastMovementSpeedFactor = 3.0f;

		triebWerk::CCamera* m_pMainCamera;
		DirectX::XMINT2 m_PreviousMousePosition;

        float m_RotationX;
        float m_RotationY;

	public:
		CDebugCamera();
		~CDebugCamera();

	public:
        void StartDebugging();
        void EndDebugging();
		void Update();

    private:
        void MouseRotation();
        void KeyboardMovement();
	};
}