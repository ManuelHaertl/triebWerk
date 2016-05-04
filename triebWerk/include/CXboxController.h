#pragma once
#include <Windows.h>
#include <Xinput.h>

#include <EButtonState.h>
#include <EGamepadButton.h>

namespace triebWerk
{
    class CXboxController
    {
    public:
        static const char DEADZONE_TRIGGER = 30;           // Range: 0 - 255
        static const short DEADZONE_LEFT_ANALOG = 12500;   // Range: -32.768 - 32.767
        static const short DEADZONE_RIGHT_ANALOG = 12500;  // Range: -32.768 - 32.767

    private:
        static const unsigned int HighestButtonValue = 23;
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

        EButtonState::Type m_ButtonStates[HighestButtonValue];

    public:
        CXboxController();
        ~CXboxController();

        void SetIndex(const DWORD a_Index);
        void Update(const float a_DeltaTime);

    private:
        void CheckRumble(const float a_DeltaTime);
        void CheckButtons(const XINPUT_STATE a_State);
        short DeadzoneCheck(const short a_A, const short a_B, const short a_Deadzone);
    };
}