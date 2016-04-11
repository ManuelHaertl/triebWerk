#include <CGamepad.h>

triebWerk::CGamepad::CGamepad()
{
    for (size_t i = 0; i < XUSER_MAX_COUNT; ++i)
    {
        m_Controller[i].SetIndex(static_cast<DWORD>(i));
    }
}

triebWerk::CGamepad::~CGamepad()
{
}

void triebWerk::CGamepad::Update(const float a_DeltaTime)
{
    for (size_t i = 0; i < XUSER_MAX_COUNT; ++i)
    {
        m_Controller[i].Update(a_DeltaTime);
    }
}

bool triebWerk::CGamepad::IsConnected(const size_t a_ControllerIndex) const
{
    return m_Controller[a_ControllerIndex].m_IsConnected;
}

void triebWerk::CGamepad::SetRumbleOn(const size_t a_ControllerIndex, float a_LeftMotor, float a_RightMotor, const float a_Time)
{
    // calculate rumble strength
    if (a_LeftMotor > 1.0f) a_LeftMotor = 1.0f;
    else if (a_LeftMotor < 0.0f) a_LeftMotor = 0.0f;

    if (a_RightMotor > 1.0f) a_RightMotor = 1.0f;
    else if (a_RightMotor < 0.0f) a_RightMotor = 0.0f;

    unsigned short left = static_cast<unsigned short>(a_LeftMotor * 65535);
    unsigned short right = static_cast<unsigned short>(a_RightMotor * 65535);

    // enable vibration
    XINPUT_VIBRATION vibration = { 0 };
    vibration.wLeftMotorSpeed = left;
    vibration.wRightMotorSpeed = right;
    XInputSetState(static_cast<DWORD>(a_ControllerIndex), &vibration);

    m_Controller[a_ControllerIndex].m_RumbleHasEnded = false;
    m_Controller[a_ControllerIndex].m_RumbleTime = a_Time;
}

void triebWerk::CGamepad::SetRumbleOff(const size_t a_ControllerIndex)
{
    XINPUT_VIBRATION vibration = { 0 };
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(a_ControllerIndex, &vibration);

    m_Controller[a_ControllerIndex].m_RumbleHasEnded = true;
    m_Controller[a_ControllerIndex].m_RumbleTime = 0.0f;
}

short triebWerk::CGamepad::GetLeftAnalogX(const size_t a_ControllerIndex) const
{
    return m_Controller[a_ControllerIndex].m_LeftAnalogX;
}

short triebWerk::CGamepad::GetLeftAnalogY(const size_t a_ControllerIndex) const
{
    return m_Controller[a_ControllerIndex].m_LeftAnalogY;
}

short triebWerk::CGamepad::GetRightAnalogX(const size_t a_ControllerIndex) const
{
    return m_Controller[a_ControllerIndex].m_RightAnalogX;
}

short triebWerk::CGamepad::GetRightAnalogY(const size_t a_ControllerIndex) const
{
    return m_Controller[a_ControllerIndex].m_RightAnalogY;
}

short triebWerk::CGamepad::GetLeftTrigger(const size_t a_ControllerIndex) const
{
    return m_Controller[a_ControllerIndex].m_LeftTrigger;
}

short triebWerk::CGamepad::GetRightTrigger(const size_t a_ControllerIndex) const
{
    return m_Controller[a_ControllerIndex].m_RightTrigger;
}

bool triebWerk::CGamepad::IsState(const EGamepadButton::Type a_GamepadButton, const EButtonState::Type a_State, const size_t a_ControllerIndex) const
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_ButtonStates[a_GamepadButton];

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
