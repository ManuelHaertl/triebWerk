#include <CDebugCamera.h>
#include <CEngine.h>

triebWerk::CDebugCamera::CDebugCamera() :
	m_pMainCamera(nullptr),
    m_RotationX(0.0f),
    m_RotationY(0.0f)
{

}

triebWerk::CDebugCamera::~CDebugCamera()
{
}

void triebWerk::CDebugCamera::StartDebugging()
{
    m_pMainCamera = CEngine::Instance().m_pRenderer->GetCurrentActiveCamera();

    m_PreviousMousePosition = twMouse.GetPosition();
    m_pMainCamera->m_Transform.SetRotationDegrees(m_RotationY, m_RotationX, 0.0f);
}

void triebWerk::CDebugCamera::EndDebugging()
{
}

void triebWerk::CDebugCamera::Update()
{
    MouseRotation();
    MouseFOV();
    KeyboardMovement();
}

void triebWerk::CDebugCamera::MouseRotation()
{
    DirectX::XMINT2 currentMousePosition = twMouse.GetPosition();

    if (twMouse.IsState(triebWerk::EMouseButton::Left, triebWerk::EButtonState::Pressed))
    {
        m_RotationX += -static_cast<float>((m_PreviousMousePosition.x - currentMousePosition.x) * RotateSpeed);
        m_RotationY += -static_cast<float>((m_PreviousMousePosition.y - currentMousePosition.y) * RotateSpeed);

        m_pMainCamera->m_Transform.SetRotationDegrees(m_RotationY, m_RotationX, 0.0f);
    }

    m_PreviousMousePosition = currentMousePosition;
}

void triebWerk::CDebugCamera::MouseFOV()
{
    float amount = static_cast<float>(twMouse.GetWheelMovement());

    if (twKeyboard.IsState(triebWerk::EKey::Shift, triebWerk::EButtonState::Pressed))
        amount *= FastMovementSpeedFactor;

    if (amount != 0)
    {
        float fov = m_pMainCamera->GetFOV() + DirectX::XMConvertToRadians(amount * FOVZoomSpeed);
        m_pMainCamera->SetFOV(fov);
        std::cout << "FOV: " << DirectX::XMConvertToDegrees(fov) << std::endl;
    }
}

void triebWerk::CDebugCamera::KeyboardMovement()
{
    float speed = MovementSpeed;

    if (twKeyboard.IsState(triebWerk::EKey::Shift, triebWerk::EButtonState::Pressed))
        speed *= FastMovementSpeedFactor;

    // forward
    if (twKeyboard.IsState(triebWerk::EKey::W, triebWerk::EButtonState::Pressed))
    {
        DirectX::XMVECTOR position = m_pMainCamera->m_Transform.GetPosition();
        DirectX::XMVECTOR forward = DirectX::XMVectorScale(m_pMainCamera->m_Transform.GetForward(), speed * twTime->GetDeltaTime());
        m_pMainCamera->m_Transform.SetPosition(DirectX::XMVectorAdd(position, forward));
    }

    // backwards
    if (twKeyboard.IsState(triebWerk::EKey::S, triebWerk::EButtonState::Pressed))
    {
        DirectX::XMVECTOR position = m_pMainCamera->m_Transform.GetPosition();
        DirectX::XMVECTOR forward = DirectX::XMVectorScale(m_pMainCamera->m_Transform.GetForward(), speed * twTime->GetDeltaTime());
        m_pMainCamera->m_Transform.SetPosition(DirectX::XMVectorSubtract(position, forward));
    }

    // sidwards, right
    if (twKeyboard.IsState(triebWerk::EKey::D, triebWerk::EButtonState::Pressed))
    {
        DirectX::XMVECTOR position = m_pMainCamera->m_Transform.GetPosition();
        DirectX::XMVECTOR forward = DirectX::XMVectorScale(m_pMainCamera->m_Transform.GetSide(), speed * twTime->GetDeltaTime());
        m_pMainCamera->m_Transform.SetPosition(DirectX::XMVectorAdd(position, forward));
    }

    // sidewards left
    if (twKeyboard.IsState(triebWerk::EKey::A, triebWerk::EButtonState::Pressed))
    {
        DirectX::XMVECTOR position = m_pMainCamera->m_Transform.GetPosition();
        DirectX::XMVECTOR forward = DirectX::XMVectorScale(m_pMainCamera->m_Transform.GetSide(), speed * twTime->GetDeltaTime());
        m_pMainCamera->m_Transform.SetPosition(DirectX::XMVectorSubtract(position, forward));
    }

    // up
    if (twKeyboard.IsState(triebWerk::EKey::Space, triebWerk::EButtonState::Pressed))
    {
        DirectX::XMVECTOR position = m_pMainCamera->m_Transform.GetPosition();
        position.m128_f32[1] += speed * twTime->GetDeltaTime();
        m_pMainCamera->m_Transform.SetPosition(position);
    }

    // down
    if (twKeyboard.IsState(triebWerk::EKey::Z, triebWerk::EButtonState::Pressed))
    {
        DirectX::XMVECTOR position = m_pMainCamera->m_Transform.GetPosition();
        position.m128_f32[1] -= speed * twTime->GetDeltaTime();
        m_pMainCamera->m_Transform.SetPosition(position);
    }
}
