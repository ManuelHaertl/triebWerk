#include <CMouse.h>
#include <iostream>

triebWerk::CMouse::CMouse() :
    m_UpdateMouse(false),
    m_UpdateMouseType(EMouseButton::Left),
    m_UpdateButtonState(EButtonState::Released),
    m_Position(0, 0),
    m_WheelMovement(0)
{
    for (size_t i = 0; i < HighestMouseValue; ++i)
    {
        m_MouseState[i] = EButtonState::Released;
    }
}

triebWerk::CMouse::~CMouse()
{
}

void triebWerk::CMouse::Update()
{
    if (m_UpdateMouse == true)
    {
        m_MouseState[m_UpdateMouseType] = m_UpdateButtonState;
        m_UpdateMouse = false;
    }

    m_WheelMovement = 0;
}

void triebWerk::CMouse::UpdateMSG(const MSG& a_rMSG)
{
    switch (a_rMSG.message)
    {
    case WM_LBUTTONDOWN:
    {
        m_MouseState[EMouseButton::Left] = EButtonState::Down;

        m_UpdateMouse = true;
        m_UpdateMouseType = EMouseButton::Left;
        m_UpdateButtonState = EButtonState::Pressed;
        break;
    }

    case WM_LBUTTONUP:
    {
        m_MouseState[EMouseButton::Left] = EButtonState::Up;

        m_UpdateMouse = true;
        m_UpdateMouseType = EMouseButton::Left;
        m_UpdateButtonState = EButtonState::Released;
        break;
    }

    case WM_RBUTTONDOWN:
    {
        m_MouseState[EMouseButton::Left] = EButtonState::Down;

        m_UpdateMouse = true;
        m_UpdateMouseType = EMouseButton::Right;
        m_UpdateButtonState = EButtonState::Pressed;
        break;
    }

    case WM_RBUTTONUP:
    {
        m_MouseState[EMouseButton::Left] = EButtonState::Up;

        m_UpdateMouse = true;
        m_UpdateMouseType = EMouseButton::Right;
        m_UpdateButtonState = EButtonState::Released;
        break;
    }

    case WM_MBUTTONDOWN:
    {
        m_MouseState[EMouseButton::Left] = EButtonState::Down;

        m_UpdateMouse = true;
        m_UpdateMouseType = EMouseButton::Middle;
        m_UpdateButtonState = EButtonState::Pressed;
        break;
    }

    case WM_MBUTTONUP:
    {
        m_MouseState[EMouseButton::Left] = EButtonState::Up;

        m_UpdateMouse = true;
        m_UpdateMouseType = EMouseButton::Middle;
        m_UpdateButtonState = EButtonState::Released;
        break;
    }

    case WM_MOUSEMOVE:
    {
        m_Position.x = a_rMSG.lParam & 0xffff;
        m_Position.y = (a_rMSG.lParam >> 16) & 0xffff;
        break;
    }

    case WM_MOUSEWHEEL:
    {
        m_WheelMovement = (a_rMSG.wParam >> 16) & 0xffff;
        break;
    }

    default:
        return;
    }
}

bool triebWerk::CMouse::IsState(const EMouseButton::Type a_Mouse, const EButtonState::Type a_State) const
{
    EButtonState::Type current = m_MouseState[a_Mouse];

    switch (a_State)
    {
    case EButtonState::Pressed:
    {
        bool value = (current == EButtonState::Pressed) || (current == EButtonState::Down);
        return value;
    }
    case EButtonState::Released:
    {
        bool value = (current == EButtonState::Released) || (current == EButtonState::Up);
        return value;
    }
    default:
    {
        bool value = (current == a_State);
        return value;
    }
    }
}

DirectX::XMINT2 triebWerk::CMouse::GetPosition() const
{
    return m_Position;
}

short triebWerk::CMouse::GetWheelMovement() const
{
    return m_WheelMovement;
}
