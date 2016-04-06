#pragma once
#include <CXboxController.h>

namespace triebWerk
{
    class CGamepad
    {
    private:
        CXboxController m_Controller[4];

    public:
        CGamepad();
        ~CGamepad();

        void Update(const float a_DeltaTime);

        bool IsConnected(const size_t a_ControllerIndex) const;
        void SetRumbleOn(const size_t a_ControllerIndex, float a_LeftMotor, float a_RightMotor, const float a_Time);
        void SetRumbleOff(const size_t a_ControllerIndex);
        short GetLeftAnalogX(const size_t a_ControllerIndex) const;
        short GetLeftAnalogY(const size_t a_ControllerIndex) const;
        short GetRightAnalogX(const size_t a_ControllerIndex) const;
        short GetRightAnalogY(const size_t a_ControllerIndex) const;
        short GetLeftTrigger(const size_t a_ControllerIndex) const;
        short GetRightTrigger(const size_t a_ControllerIndex) const;

        bool IsState(const EGamepadButton::Type a_GamepadButton, const EButtonState::Type a_State, const size_t a_ControllerIndex) const;
    };
}