#pragma once
#include <EButtonState.h>
#include <Windows.h>
#include <Xinput.h>

namespace triebWerk
{
    class CXboxController
    {
    private:
        const char DEADZONE_TRIGGER = 30;           // Range: 0 - 255
        const short DEADZONE_LEFT_ANALOG = 12500;   // Range: -32.768 - 32.767
        const short DEADZONE_RIGHT_ANALOG = 12500;  // Range: -32.768 - 32.767

        DWORD m_Index;

    public:
        float m_RumbleTime;
        bool m_IsConnected;
        bool m_RumbleHasEnded;

        short m_LeftAnalogX;
        short m_LeftAnalogY;
        short m_RightAnalogX;
        short m_RightAnalogY;
        short m_LeftTrigger;
        short m_RightTrigger;

        EButtonState::Type m_LeftAnalogLeft;
        EButtonState::Type m_LeftAnalogRight;
        EButtonState::Type m_LeftAnalogUp;
        EButtonState::Type m_LeftAnalogDown;

        EButtonState::Type m_RightAnalogLeft;
        EButtonState::Type m_RightAnalogRight;
        EButtonState::Type m_RightAnalogUp;
        EButtonState::Type m_RightAnalogDown;

        EButtonState::Type m_LeftBumper;
        EButtonState::Type m_RightBumper;

        EButtonState::Type m_LeftTriggerState;
        EButtonState::Type m_RightTriggerState;

        EButtonState::Type m_A;
        EButtonState::Type m_B;
        EButtonState::Type m_X;
        EButtonState::Type m_Y;

        EButtonState::Type m_DigitalUp;
        EButtonState::Type m_DigitalDown;
        EButtonState::Type m_DigitalLeft;
        EButtonState::Type m_DigitalRight;

        EButtonState::Type m_Start;
        EButtonState::Type m_Back;

        EButtonState::Type m_LeftThumb;
        EButtonState::Type m_RightThumb;

    public:
        CXboxController();
        ~CXboxController();

        void SetIndex(DWORD a_Index);
        void Update();

    private:
        void CheckRumble();
        void CheckButtons(XINPUT_STATE a_State);
        short DeadzoneCheck(short a_A, short a_B, short a_Deadzone);
    };
}