#include <CXboxController.h>

triebWerk::CXboxController::CXboxController() :
    m_Index(0),
    m_RumbleTime(0.0f),
    m_IsConnected(false),
    m_RumbleHasEnded(false),
    m_LeftAnalogX(0),
    m_LeftAnalogY(0),
    m_RightAnalogX(0),
    m_RightAnalogY(0),
    m_LeftTrigger(0),
    m_RightTrigger(0)
{
    for (size_t i = 0; i < HighestButtonValue; ++i)
    {
        m_ButtonStates[i] = EButtonState::Released;
    }
}

triebWerk::CXboxController::~CXboxController()
{
}

void triebWerk::CXboxController::SetIndex(const DWORD a_Index)
{
    m_Index = a_Index;
}

void triebWerk::CXboxController::Update(const float a_DeltaTime)
{
    XINPUT_STATE state = { 0 };
    DWORD result = XInputGetState(m_Index, &state);

    // Check connection
    switch (result)
    {
    case ERROR_SUCCESS:
        m_IsConnected = true;
        CheckButtons(state);
        CheckRumble(a_DeltaTime);
        break;
    case ERROR_DEVICE_NOT_CONNECTED:
        m_IsConnected = false;
        break;
    }
}

void triebWerk::CXboxController::CheckRumble(const float a_DeltaTime)
{
    if (m_RumbleHasEnded == false)
    {
        m_RumbleTime -= a_DeltaTime;

        if (m_RumbleTime <= 0.0f)
        {
            XINPUT_VIBRATION vibration = { 0 };
            vibration.wLeftMotorSpeed = 0;
            vibration.wRightMotorSpeed = 0;
            XInputSetState(m_Index, &vibration);

            m_RumbleHasEnded = true;
        }
    }
}

void triebWerk::CXboxController::CheckButtons(const XINPUT_STATE a_State)
{
    // Axis Checks
    m_LeftAnalogX = DeadzoneCheck(a_State.Gamepad.sThumbLX, a_State.Gamepad.sThumbLY, DEADZONE_LEFT_ANALOG);
    m_LeftAnalogY = DeadzoneCheck(a_State.Gamepad.sThumbLY, a_State.Gamepad.sThumbLX, DEADZONE_LEFT_ANALOG);
    m_RightAnalogX = DeadzoneCheck(a_State.Gamepad.sThumbRX, a_State.Gamepad.sThumbRY, DEADZONE_RIGHT_ANALOG);
    m_RightAnalogY = DeadzoneCheck(a_State.Gamepad.sThumbRY, a_State.Gamepad.sThumbRX, DEADZONE_RIGHT_ANALOG);

    // Left Bumper
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
    {
        if (m_ButtonStates[EGamepadButton::LB] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::LB] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::LB] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::LB] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::LB] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::LB] = EButtonState::Released;
    }

    // Right Bumper
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
    {
        if (m_ButtonStates[EGamepadButton::RB] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::RB] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::RB] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::RB] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::RB] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::RB] = EButtonState::Released;
    }

    // Back
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
    {
        if (m_ButtonStates[EGamepadButton::Back] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::Back] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::Back] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::Back] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::Back] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::Back] = EButtonState::Released;
    }

    // Start
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_START)
    {
        if (m_ButtonStates[EGamepadButton::Start] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::Start] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::Start] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::Start] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::Start] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::Start] = EButtonState::Released;
    }

    // Left Thumb
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
    {
        if (m_ButtonStates[EGamepadButton::LeftThumb] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::LeftThumb] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::LeftThumb] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::LeftThumb] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::LeftThumb] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::LeftThumb] = EButtonState::Released;
    }

    // Right Thumb
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
    {
        if (m_ButtonStates[EGamepadButton::RightThumb] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::RightThumb] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::RightThumb] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::RightThumb] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::RightThumb] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::RightThumb] = EButtonState::Released;
    }

    // A
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_A)
    {
        if (m_ButtonStates[EGamepadButton::A] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::A] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::A] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::A] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::A] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::A] = EButtonState::Released;
    }

    // B
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_B)
    {
        if (m_ButtonStates[EGamepadButton::B] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::B] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::B] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::B] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::B] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::B] = EButtonState::Released;
    }

    // X
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_X)
    {
        if (m_ButtonStates[EGamepadButton::X] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::X] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::X] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::X] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::X] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::X] = EButtonState::Released;
    }

    // Y
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
    {
        if (m_ButtonStates[EGamepadButton::Y] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::Y] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::Y] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::Y] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::Y] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::Y] = EButtonState::Released;
    }

    // Digital Pad Up
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
    {
        if (m_ButtonStates[EGamepadButton::DigitalUp] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::DigitalUp] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::DigitalUp] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::DigitalUp] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::DigitalUp] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::DigitalUp] = EButtonState::Released;
    }

    // Digital Pad Down
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
    {
        if (m_ButtonStates[EGamepadButton::DigitalDown] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::DigitalDown] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::DigitalDown] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::DigitalDown] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::DigitalDown] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::DigitalDown] = EButtonState::Released;
    }

    // Digital Pad Left
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
    {
        if (m_ButtonStates[EGamepadButton::DigitalLeft] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::DigitalLeft] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::DigitalLeft] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::DigitalLeft] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::DigitalLeft] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::DigitalLeft] = EButtonState::Released;
    }

    // Digital Pad Right
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        if (m_ButtonStates[EGamepadButton::DigitalRight] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::DigitalRight] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::DigitalRight] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::DigitalRight] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::DigitalRight] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::DigitalRight] = EButtonState::Released;
    }

    // Left Analog Left
    if (-a_State.Gamepad.sThumbLX > DEADZONE_LEFT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::LAnalogLeft] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::LAnalogLeft] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::LAnalogLeft] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::LAnalogLeft] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::LAnalogLeft] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::LAnalogLeft] = EButtonState::Released;
    }

    // Left Analog Right
    if (a_State.Gamepad.sThumbLX > DEADZONE_LEFT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::LAnalogRight] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::LAnalogRight] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::LAnalogRight] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::LAnalogRight] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::LAnalogRight] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::LAnalogRight] = EButtonState::Released;
    }

    // Left Analog Up
    if (a_State.Gamepad.sThumbLY > DEADZONE_LEFT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::LAnalogUp] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::LAnalogUp] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::LAnalogUp] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::LAnalogUp] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::LAnalogUp] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::LAnalogUp] = EButtonState::Released;
    }

    // Left Analog Down
    if (-a_State.Gamepad.sThumbLY > DEADZONE_LEFT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::LAnalogDown] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::LAnalogDown] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::LAnalogDown] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::LAnalogDown] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::LAnalogDown] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::LAnalogDown] = EButtonState::Released;
    }

    // Right Analog Left
    if (-a_State.Gamepad.sThumbRX > DEADZONE_RIGHT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::RAnalogLeft] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::RAnalogLeft] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::RAnalogLeft] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::RAnalogLeft] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::RAnalogLeft] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::RAnalogLeft] = EButtonState::Released;
    }

    // Right Analog Right
    if (-a_State.Gamepad.sThumbRX > DEADZONE_RIGHT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::RAnalogRight] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::RAnalogRight] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::RAnalogRight] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::RAnalogRight] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::RAnalogRight] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::RAnalogRight] = EButtonState::Released;
    }

    // Right Analog Up
    if (a_State.Gamepad.sThumbRY > DEADZONE_RIGHT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::RAnalogUp] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::RAnalogUp] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::RAnalogUp] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::RAnalogUp] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::RAnalogUp] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::RAnalogUp] = EButtonState::Released;
    }

    // Right Analog Down
    if (-a_State.Gamepad.sThumbRY > DEADZONE_RIGHT_ANALOG)
    {
        if (m_ButtonStates[EGamepadButton::RAnalogDown] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::RAnalogDown] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::RAnalogDown] = EButtonState::Pressed;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::RAnalogDown] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::RAnalogDown] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::RAnalogDown] = EButtonState::Released;
    }

    // Left Trigger
    if (a_State.Gamepad.bLeftTrigger > DEADZONE_TRIGGER)
    {
        if (m_ButtonStates[EGamepadButton::LT] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::LT] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::LT] = EButtonState::Pressed;

        m_LeftTrigger = a_State.Gamepad.bLeftTrigger;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::LT] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::LT] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::LT] = EButtonState::Released;

        m_LeftTrigger = 0;
    }

    // Right Trigger
    if (a_State.Gamepad.bRightTrigger > DEADZONE_TRIGGER)
    {
        if (m_ButtonStates[EGamepadButton::RT] == EButtonState::Released)
            m_ButtonStates[EGamepadButton::RT] = EButtonState::Down;
        else
            m_ButtonStates[EGamepadButton::RT] = EButtonState::Pressed;

        m_RightTrigger = a_State.Gamepad.bRightTrigger;
    }
    else
    {
        if (m_ButtonStates[EGamepadButton::RT] == EButtonState::Pressed)
            m_ButtonStates[EGamepadButton::RT] = EButtonState::Up;
        else
            m_ButtonStates[EGamepadButton::RT] = EButtonState::Released;

        m_RightTrigger = 0;
    }
}

short triebWerk::CXboxController::DeadzoneCheck(const short a_FirstAxis, const short a_SecondAxis, const short a_Deadzone)
{
    int axis1 = static_cast<int>(a_FirstAxis);
    int axis2 = static_cast<int>(a_SecondAxis);

    if (axis1 < 0)
        axis1 *= -1;
    if (axis2 < 0)
        axis2 *= -1;

    if (axis1 + axis2 > a_Deadzone)
        return a_FirstAxis;
    else
        return 0;
}
