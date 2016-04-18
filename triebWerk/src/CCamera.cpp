#include <CCamera.h>

triebWerk::CCamera::CCamera() :
	m_Aspect(0.0f),
	m_FarPlane(0.0f),
	m_FOV(0.0f),
	m_NearPlane(0.0f),
	m_ScreenHeight(0),
	m_ScreenWidth(0)
{
	m_ProjectionMatrix = DirectX::XMMatrixIdentity();
	m_ViewMatrix = DirectX::XMMatrixIdentity();
}

triebWerk::CCamera::CCamera(float a_Aspect, float a_FOV, float a_Near, float a_Far, unsigned int a_ScreenHeight, unsigned int a_ScreenWidth)
{
	m_Aspect = a_Aspect;
	m_FarPlane = a_Far;
	m_FOV = a_FOV;
	m_NearPlane = a_Near;
	m_ScreenHeight = a_ScreenHeight;
	m_ScreenWidth = a_ScreenWidth;

	CalculateProjection();

	DetermineViewport();
}

triebWerk::CCamera::~CCamera()
{
}

void triebWerk::CCamera::Update()
{
	DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(DirectX::XMVector3Rotate(m_Transform.GetPosition(), m_Transform.GetRotation()), At, Up);
}

DirectX::XMMATRIX & triebWerk::CCamera::GetViewMatrix()
{
	return m_ViewMatrix;
}

DirectX::XMMATRIX & triebWerk::CCamera::GetProjection()
{
	return m_ProjectionMatrix;
}

void triebWerk::CCamera::SetAspect(const float a_Aspect)
{
	m_Aspect = a_Aspect;
}

void triebWerk::CCamera::SetFOV(const float a_FOV)
{
	m_FOV = a_FOV;
}

void triebWerk::CCamera::SetNear(const float a_NearPlane)
{
	m_NearPlane = a_NearPlane;
}

void triebWerk::CCamera::SetFar(const float a_FarPlane)
{
	m_FarPlane = a_FarPlane;
}

float triebWerk::CCamera::GetAspect() const
{
	return m_Aspect;
}

float triebWerk::CCamera::GetFOV() const
{
	return m_FOV;
}

float triebWerk::CCamera::GetNear() const
{
	return m_NearPlane;
}

float triebWerk::CCamera::GetFar() const
{
	return m_FarPlane;
}

void triebWerk::CCamera::CalculateProjection()
{
	m_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FOV, m_Aspect, m_NearPlane, m_FarPlane);
}

void triebWerk::CCamera::DetermineViewport()
{

}
