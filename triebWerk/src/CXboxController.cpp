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
    m_RightTrigger(0),
    m_LeftAnalogLeft(EButtonState::Released),
    m_LeftAnalogRight(EButtonState::Released),
    m_LeftAnalogUp(EButtonState::Released),
    m_LeftAnalogDown(EButtonState::Released),
    m_RightAnalogLeft(EButtonState::Released),
    m_RightAnalogRight(EButtonState::Released),
    m_RightAnalogUp(EButtonState::Released),
    m_RightAnalogDown(EButtonState::Released),
    m_LeftBumper(EButtonState::Released),
    m_RightBumper(EButtonState::Released),
    m_LeftTriggerState(EButtonState::Released),
    m_RightTriggerState(EButtonState::Released),
    m_A(EButtonState::Released),
    m_B(EButtonState::Released),
    m_X(EButtonState::Released),
    m_Y(EButtonState::Released),
    m_DigitalUp(EButtonState::Released),
    m_DigitalDown(EButtonState::Released),
    m_DigitalLeft(EButtonState::Released),
    m_DigitalRight(EButtonState::Released),
    m_Start(EButtonState::Released),
    m_Back(EButtonState::Released),
    m_LeftThumb(EButtonState::Released),
    m_RightThumb(EButtonState::Released)
{
}

triebWerk::CXboxController::~CXboxController()
{
}

void triebWerk::CXboxController::SetIndex(DWORD a_Index)
{
    m_Index = a_Index;
}

void triebWerk::CXboxController::Update(float a_DeltaTime)
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

void triebWerk::CXboxController::CheckRumble(float a_DeltaTime)
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

void triebWerk::CXboxController::CheckButtons(XINPUT_STATE a_State)
{
    // Axis Checks
    m_LeftAnalogX = DeadzoneCheck(a_State.Gamepad.sThumbLX, a_State.Gamepad.sThumbLY, DEADZONE_LEFT_ANALOG);
    m_LeftAnalogY = DeadzoneCheck(a_State.Gamepad.sThumbLY, a_State.Gamepad.sThumbLX, DEADZONE_LEFT_ANALOG);
    m_RightAnalogX = DeadzoneCheck(a_State.Gamepad.sThumbRX, a_State.Gamepad.sThumbRY, DEADZONE_RIGHT_ANALOG);
    m_RightAnalogY = DeadzoneCheck(a_State.Gamepad.sThumbRY, a_State.Gamepad.sThumbRX, DEADZONE_RIGHT_ANALOG);

    // Left Bumper
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
    {
        if (m_LeftBumper == EButtonState::Released)
            m_LeftBumper = EButtonState::Down;
        else
            m_LeftBumper = EButtonState::Pressed;
    }
    else
    {
        if (m_LeftBumper == EButtonState::Pressed)
            m_LeftBumper = EButtonState::Up;
        else
            m_LeftBumper = EButtonState::Released;
    }

    // Right Bumper
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
    {
        if (m_RightBumper == EButtonState::Released)
            m_RightBumper = EButtonState::Down;
        else
            m_RightBumper = EButtonState::Pressed;
    }
    else
    {
        if (m_RightBumper == EButtonState::Pressed)
            m_RightBumper = EButtonState::Up;
        else
            m_RightBumper = EButtonState::Released;
    }

    // Back
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
    {
        if (m_Back == EButtonState::Released)
            m_Back = EButtonState::Down;
        else
            m_Back = EButtonState::Pressed;
    }
    else
    {
        if (m_Back == EButtonState::Pressed)
            m_Back = EButtonState::Up;
        else
            m_Back = EButtonState::Released;
    }

    // Start
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_START)
    {
        if (m_Start == EButtonState::Released)
            m_Start = EButtonState::Down;
        else
            m_Start = EButtonState::Pressed;
    }
    else
    {
        if (m_Start == EButtonState::Pressed)
            m_Start = EButtonState::Up;
        else
            m_Start = EButtonState::Released;
    }

    // Left Thumb
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
    {
        if (m_LeftThumb == EButtonState::Released)
            m_LeftThumb = EButtonState::Down;
        else
            m_LeftThumb = EButtonState::Pressed;
    }
    else
    {
        if (m_LeftThumb == EButtonState::Pressed)
            m_LeftThumb = EButtonState::Up;
        else
            m_LeftThumb = EButtonState::Released;
    }

    // Right Thumb
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
    {
        if (m_RightThumb == EButtonState::Released)
            m_RightThumb = EButtonState::Down;
        else
            m_RightThumb = EButtonState::Pressed;
    }
    else
    {
        if (m_RightThumb == EButtonState::Pressed)
            m_RightThumb = EButtonState::Up;
        else
            m_RightThumb = EButtonState::Released;
    }

    // A
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_A)
    {
        if (m_A == EButtonState::Released)
            m_A = EButtonState::Down;
        else
            m_A = EButtonState::Pressed;
    }
    else
    {
        if (m_A == EButtonState::Pressed)
            m_A = EButtonState::Up;
        else
            m_A = EButtonState::Released;
    }

    // B
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_B)
    {
        if (m_B == EButtonState::Released)
            m_B = EButtonState::Down;
        else
            m_B = EButtonState::Pressed;
    }
    else
    {
        if (m_B == EButtonState::Pressed)
            m_B = EButtonState::Up;
        else
            m_B = EButtonState::Released;
    }

    // X
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_X)
    {
        if (m_X == EButtonState::Released)
            m_X = EButtonState::Down;
        else
            m_X = EButtonState::Pressed;
    }
    else
    {
        if (m_X == EButtonState::Pressed)
            m_X = EButtonState::Up;
        else
            m_X = EButtonState::Released;
    }

    // Y
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
    {
        if (m_Y == EButtonState::Released)
            m_Y = EButtonState::Down;
        else
            m_Y = EButtonState::Pressed;
    }
    else
    {
        if (m_Y == EButtonState::Pressed)
            m_Y = EButtonState::Up;
        else
            m_Y = EButtonState::Released;
    }

    // Digital Pad Up
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
    {
        if (m_DigitalUp == EButtonState::Released)
            m_DigitalUp = EButtonState::Down;
        else
            m_DigitalUp = EButtonState::Pressed;
    }
    else
    {
        if (m_DigitalUp == EButtonState::Pressed)
            m_DigitalUp = EButtonState::Up;
        else
            m_DigitalUp = EButtonState::Released;
    }

    // Digital Pad Down
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
    {
        if (m_DigitalDown == EButtonState::Released)
            m_DigitalDown = EButtonState::Down;
        else
            m_DigitalDown = EButtonState::Pressed;
    }
    else
    {
        if (m_DigitalDown == EButtonState::Pressed)
            m_DigitalDown = EButtonState::Up;
        else
            m_DigitalDown = EButtonState::Released;
    }

    // Digital Pad Left
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
    {
        if (m_DigitalLeft == EButtonState::Released)
            m_DigitalLeft = EButtonState::Down;
        else
            m_DigitalLeft = EButtonState::Pressed;
    }
    else
    {
        if (m_DigitalLeft == EButtonState::Pressed)
            m_DigitalLeft = EButtonState::Up;
        else
            m_DigitalLeft = EButtonState::Released;
    }

    // Digital Pad Right
    if (a_State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        if (m_DigitalRight == EButtonState::Released)
            m_DigitalRight = EButtonState::Down;
        else
            m_DigitalRight = EButtonState::Pressed;
    }
    else
    {
        if (m_DigitalRight == EButtonState::Pressed)
            m_DigitalRight = EButtonState::Up;
        else
            m_DigitalRight = EButtonState::Released;
    }

    // Left Analog Left
    if (-a_State.Gamepad.sThumbLX > DEADZONE_LEFT_ANALOG)
    {
        if (m_LeftAnalogLeft == EButtonState::Released)
            m_LeftAnalogLeft = EButtonState::Down;
        else
            m_LeftAnalogLeft = EButtonState::Pressed;
    }
    else
    {
        if (m_LeftAnalogLeft == EButtonState::Pressed)
            m_LeftAnalogLeft = EButtonState::Up;
        else
            m_LeftAnalogLeft = EButtonState::Released;
    }

    // Left Analog Right
    if (a_State.Gamepad.sThumbLX > DEADZONE_LEFT_ANALOG)
    {
        if (m_LeftAnalogRight == EButtonState::Released)
            m_LeftAnalogRight = EButtonState::Down;
        else
            m_LeftAnalogRight = EButtonState::Pressed;
    }
    else
    {
        if (m_LeftAnalogRight == EButtonState::Pressed)
            m_LeftAnalogRight = EButtonState::Up;
        else
            m_LeftAnalogRight = EButtonState::Released;
    }

    // Left Analog Up
    if (a_State.Gamepad.sThumbLY > DEADZONE_LEFT_ANALOG)
    {
        if (m_LeftAnalogUp == EButtonState::Released)
            m_LeftAnalogUp = EButtonState::Down;
        else
            m_LeftAnalogUp = EButtonState::Pressed;
    }
    else
    {
        if (m_LeftAnalogUp == EButtonState::Pressed)
            m_LeftAnalogUp = EButtonState::Up;
        else
            m_LeftAnalogUp = EButtonState::Released;
    }

    // Left Analog Down
    if (-a_State.Gamepad.sThumbLY > DEADZONE_LEFT_ANALOG)
    {
        if (m_LeftAnalogDown == EButtonState::Released)
            m_LeftAnalogDown = EButtonState::Down;
        else
            m_LeftAnalogDown = EButtonState::Pressed;
    }
    else
    {
        if (m_LeftAnalogDown == EButtonState::Pressed)
            m_LeftAnalogDown = EButtonState::Up;
        else
            m_LeftAnalogDown = EButtonState::Released;
    }

    // Right Analog Left
    if (-a_State.Gamepad.sThumbRX > DEADZONE_RIGHT_ANALOG)
    {
        if (m_RightAnalogLeft == EButtonState::Released)
            m_RightAnalogLeft = EButtonState::Down;
        else
            m_RightAnalogLeft = EButtonState::Pressed;
    }
    else
    {
        if (m_RightAnalogLeft == EButtonState::Pressed)
            m_RightAnalogLeft = EButtonState::Up;
        else
            m_RightAnalogLeft = EButtonState::Released;
    }

    // Right Analog Right
    if (-a_State.Gamepad.sThumbRX > DEADZONE_RIGHT_ANALOG)
    {
        if (m_RightAnalogRight == EButtonState::Released)
            m_RightAnalogRight = EButtonState::Down;
        else
            m_RightAnalogRight = EButtonState::Pressed;
    }
    else
    {
        if (m_RightAnalogRight == EButtonState::Pressed)
            m_RightAnalogRight = EButtonState::Up;
        else
            m_RightAnalogRight = EButtonState::Released;
    }

    // Right Analog Up
    if (a_State.Gamepad.sThumbRY > DEADZONE_RIGHT_ANALOG)
    {
        if (m_RightAnalogUp == EButtonState::Released)
            m_RightAnalogUp = EButtonState::Down;
        else
            m_RightAnalogUp = EButtonState::Pressed;
    }
    else
    {
        if (m_RightAnalogUp == EButtonState::Pressed)
            m_RightAnalogUp = EButtonState::Up;
        else
            m_RightAnalogUp = EButtonState::Released;
    }

    // Right Analog Down
    if (-a_State.Gamepad.sThumbRY > DEADZONE_RIGHT_ANALOG)
    {
        if (m_RightAnalogDown == EButtonState::Released)
            m_RightAnalogDown = EButtonState::Down;
        else
            m_RightAnalogDown = EButtonState::Pressed;
    }
    else
    {
        if (m_RightAnalogDown == EButtonState::Pressed)
            m_RightAnalogDown = EButtonState::Up;
        else
            m_RightAnalogDown = EButtonState::Released;
    }

    // Left Trigger
    if (a_State.Gamepad.bLeftTrigger > DEADZONE_TRIGGER)
    {
        if (m_LeftTrigger == EButtonState::Released)
            m_LeftTrigger = EButtonState::Down;
        else
            m_LeftTrigger = EButtonState::Pressed;

        m_LeftTrigger = a_State.Gamepad.bLeftTrigger;
    }
    else
    {
        if (m_LeftTrigger == EButtonState::Pressed)
            m_LeftTrigger = EButtonState::Up;
        else
            m_LeftTrigger = EButtonState::Released;

        m_LeftTrigger = 0;
    }

    // Right Trigger
    if (a_State.Gamepad.bRightTrigger > DEADZONE_TRIGGER)
    {
        if (m_RightTrigger == EButtonState::Released)
            m_RightTrigger = EButtonState::Down;
        else
            m_RightTrigger = EButtonState::Pressed;

        m_RightTrigger = a_State.Gamepad.bRightTrigger;
    }
    else
    {
        if (m_RightTrigger == EButtonState::Pressed)
            m_RightTrigger = EButtonState::Up;
        else
            m_RightTrigger = EButtonState::Released;

        m_RightTrigger = 0;
    }
}

short triebWerk::CXboxController::DeadzoneCheck(short a_FirstAxis, short a_SecondAxis, short a_Deadzone)
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
