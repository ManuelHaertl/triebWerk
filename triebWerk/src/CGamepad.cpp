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

void triebWerk::CGamepad::Update(float a_DeltaTime)
{
    for (size_t i = 0; i < XUSER_MAX_COUNT; ++i)
    {
        m_Controller[i].Update(a_DeltaTime);
    }
}

bool triebWerk::CGamepad::IsConnected(size_t a_ControllerIndex)
{
    return m_Controller[a_ControllerIndex].m_IsConnected;
}

void triebWerk::CGamepad::SetRumbleOn(size_t a_ControllerIndex, float a_LeftMotor, float a_RightMotor, float a_Time)
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
    XInputSetState(a_ControllerIndex, &vibration);

    m_Controller[a_ControllerIndex].m_RumbleHasEnded = false;
    m_Controller[a_ControllerIndex].m_RumbleTime = a_Time;
}

void triebWerk::CGamepad::SetRumbleOff(size_t a_ControllerIndex)
{
    XINPUT_VIBRATION vibration = { 0 };
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(a_ControllerIndex, &vibration);

    m_Controller[a_ControllerIndex].m_RumbleHasEnded = true;
    m_Controller[a_ControllerIndex].m_RumbleTime = 0.0f;
}

short triebWerk::CGamepad::GetLeftAnalogX(size_t a_ControllerIndex)
{
    return m_Controller[a_ControllerIndex].m_LeftAnalogX;
}

short triebWerk::CGamepad::GetLeftAnalogY(size_t a_ControllerIndex)
{
    return m_Controller[a_ControllerIndex].m_LeftAnalogY;
}

short triebWerk::CGamepad::GetRightAnalogX(size_t a_ControllerIndex)
{
    return m_Controller[a_ControllerIndex].m_RightAnalogX;
}

short triebWerk::CGamepad::GetRightAnalogY(size_t a_ControllerIndex)
{
    return m_Controller[a_ControllerIndex].m_RightAnalogY;
}

short triebWerk::CGamepad::GetLeftTrigger(size_t a_ControllerIndex)
{
    return m_Controller[a_ControllerIndex].m_LeftTrigger;
}

short triebWerk::CGamepad::GetRightTrigger(size_t a_ControllerIndex)
{
    return m_Controller[a_ControllerIndex].m_RightTrigger;
}

bool triebWerk::CGamepad::LeftBumper(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_LeftBumper;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::RightBumper(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_RightBumper;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::LeftTrigger(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_LeftTriggerState;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::RightTrigger(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_RightTriggerState;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::A(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_A;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::B(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_B;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::X(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_X;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::Y(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_Y;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::Start(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_Start;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::Back(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_Back;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::LeftThumb(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_LeftThumb;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::RightThumb(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_RightThumb;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::DigitalLeft(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_DigitalLeft;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::DigitalRight(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_DigitalRight;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::DigitalUp(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_DigitalUp;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::DigitalDown(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_DigitalDown;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::LeftAnalogLeft(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_LeftAnalogLeft;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::LeftAnalogRight(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_LeftAnalogRight;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::LeftAnalogUp(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_LeftAnalogUp;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::LeftAnalogDown(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_LeftAnalogDown;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::RightAnalogLeft(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_RightAnalogLeft;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::RightAnalogRight(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_RightAnalogRight;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::RightAnalogUp(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_RightAnalogUp;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::RightAnalogDown(size_t a_ControllerIndex, EButtonState::Type a_ButtonState)
{
    EButtonState::Type current = m_Controller[a_ControllerIndex].m_RightAnalogDown;
    return IsButtonPressed(current, a_ButtonState);
}

bool triebWerk::CGamepad::IsButtonPressed(EButtonState::Type a_Current, EButtonState::Type a_ToCheck)
{
    switch (a_ToCheck)
    {
    case EButtonState::Pressed:
    {
        bool value = (a_Current == EButtonState::Pressed) || (a_Current == EButtonState::Down);
        return value;
    }
    case EButtonState::Released:
    {
        bool value = (a_Current == EButtonState::Released) || (a_Current == EButtonState::Up);
        return value;
    }
    default:
    {
        bool value = (a_Current == a_ToCheck);
        return value;
    }
    }
}
