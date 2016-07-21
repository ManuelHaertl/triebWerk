#include <CCamera.h>
#include <iostream>
#include <CEngine.h>
#include <CRandom.h>

triebWerk::CCamera::CCamera() :
	m_Aspect(0.0f),
	m_FarPlane(0.0f),
	m_FOV(0.0f),
	m_NearPlane(0.0f),
	m_ScreenHeight(0),
	m_ScreenWidth(0),
	m_TimeToShake(0.0f),
	m_ShakePower(0.0f),
	m_Modified(false),
	m_IsShaking(false)
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

    CalculateView();
	CalculateProjection();
	CalculateUIProjection();
}

triebWerk::CCamera::~CCamera()
{
}

void triebWerk::CCamera::Update()
{
    // calculate View Matrix
    CalculateView();

    // calculate Projection Matrix
    if (m_Modified)
    {
        CalculateProjection();
        m_Modified = false;
    }

	if(m_TimeToShake > 0 && m_IsShaking)
	{ 
		float dt = CEngine::Instance().m_pTime->GetDeltaTime();
		m_TimeToShake -= dt;
		UpdateScreenShake(dt);
	}
	else if(m_IsShaking)
	{
		m_IsShaking = false;
		//m_Transform.SetPosition(m_ShakeStartPosition);
		m_TimeToShake = 0.0f;
		m_ShakePower = 0.0f;
	}
}

void triebWerk::CCamera::Resize(unsigned int a_NewScreenWidth, unsigned int a_ScreenHeight)
{
	m_Aspect = static_cast<float>(a_NewScreenWidth) / static_cast<float>(a_ScreenHeight);
	m_ScreenHeight = a_ScreenHeight;
	m_ScreenWidth = a_NewScreenWidth;

	CalculateProjection();
	CalculateUIProjection();
}

void triebWerk::CCamera::SetScreenShake(const float a_ShakeStrenght, const float a_ShakeTime)
{
	m_ShakePower = a_ShakeStrenght;
	m_TimeToShake = a_ShakeTime;
	m_IsShaking = true;

	m_BufferPosition = m_Transform.GetPosition();
}

DirectX::XMMATRIX & triebWerk::CCamera::GetViewMatrix()
{
	return m_ViewMatrix;
}

DirectX::XMMATRIX & triebWerk::CCamera::GetProjection()
{
	return m_ProjectionMatrix;
}

DirectX::XMMATRIX & triebWerk::CCamera::GetUIProjection()
{
	return m_UIProjectionMatrix;
}

void triebWerk::CCamera::SetAspect(const float a_Aspect)
{
	m_Aspect = a_Aspect;
	m_Modified = true;
}

void triebWerk::CCamera::SetFOV(const float a_FOV)
{
	m_FOV = a_FOV;
	m_Modified = true;
}

void triebWerk::CCamera::SetNear(const float a_NearPlane)
{
	m_NearPlane = a_NearPlane;
	m_Modified = true;
}

void triebWerk::CCamera::SetFar(const float a_FarPlane)
{
	m_FarPlane = a_FarPlane;
	m_Modified = true;
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

void triebWerk::CCamera::CalculateView()
{
    DirectX::XMVECTOR lookAt = DirectX::XMVectorAdd(m_Transform.GetPosition(), m_Transform.GetForward());
    m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Transform.GetPosition(), lookAt, m_Transform.GetUp());
}

void triebWerk::CCamera::CalculateProjection()
{
    m_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FOV, m_Aspect, m_NearPlane, m_FarPlane);
}

void triebWerk::CCamera::CalculateUIProjection()
{
	m_UIProjectionMatrix = DirectX::XMMatrixOrthographicLH(static_cast<float>(m_ScreenWidth), static_cast<float>(m_ScreenHeight), -0.1f, 100.0f);
}

void triebWerk::CCamera::UpdateScreenShake(const float a_DeltaTime)
{
	DirectX::XMVECTOR nextPos;

	nextPos.m128_f32[0] = CRandom::GetNumber(-1.0f, 1.0f) * a_DeltaTime * m_ShakePower * 100 + m_BufferPosition.m128_f32[0];
	nextPos.m128_f32[1] = CRandom::GetNumber(-1.0f, 1.0f) * a_DeltaTime * m_ShakePower * 100 + m_BufferPosition.m128_f32[1];

	nextPos.m128_f32[2] =m_Transform.GetPosition().m128_f32[2];

	m_BufferPosition = m_Transform.GetPosition();

	m_Transform.SetPosition(nextPos);
}
