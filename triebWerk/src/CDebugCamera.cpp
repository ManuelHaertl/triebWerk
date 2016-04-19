#include <CDebugCamera.h>
#include <CEngine.h>

triebWerk::CDebugCamera::CDebugCamera() :
	m_pMainCamera(nullptr),
	m_RotationX(0),
	m_RotationY(0),
	m_ZoomSpeed(6)
{
}

triebWerk::CDebugCamera::~CDebugCamera()
{
}

void triebWerk::CDebugCamera::Update()
{
	if (m_pMainCamera == nullptr)
	{
		m_pMainCamera = CEngine::Instance().m_pRenderer->GetCurrentActiveCamera();
	}

	short zoom = twMouse.GetWheelMovement();
	if (zoom != 0)
	{
		float t = zoom * m_ZoomSpeed * twTime->GetDeltaTime();
		m_pMainCamera->m_Transform.SetPosition(0, 0, m_pMainCamera->m_Transform.GetPosition().m128_f32[2] + t);
	}

	if (twMouse.IsState(triebWerk::EMouseButton::Left, triebWerk::EButtonState::Pressed))
	{
		DirectX::XMINT2 currentMousePosition = twMouse.GetPosition();
		float xvel = static_cast<float>((m_PreviousMousePosition.x - currentMousePosition.x) * 1000);
		m_RotationX += xvel * twTime->GetDeltaTime();

		float yvel = static_cast<float>((m_PreviousMousePosition.y - currentMousePosition.y) * 1000);
		m_RotationY += yvel * twTime->GetDeltaTime();

		m_pMainCamera->m_Transform.SetRotation(DirectX::XMQuaternionMultiply(DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0, 1, 0, 0), DirectX::XMConvertToRadians(-m_RotationX)), DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(-1, 0, 0, 0), DirectX::XMConvertToRadians(m_RotationY))));
		
		m_PreviousMousePosition = twMouse.GetPosition();
	}
	else
	{
		m_PreviousMousePosition = twMouse.GetPosition();
	}

}

void triebWerk::CDebugCamera::SetZoomSpeed(float a_Speed)
{
	m_ZoomSpeed = a_Speed;
}
