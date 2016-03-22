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

        void Update(float a_DeltaTime);

        bool IsConnected(size_t a_ControllerIndex);
        void SetRumbleOn(size_t a_ControllerIndex, float a_LeftMotor, float a_RightMotor, float a_Time);
        void SetRumbleOff(size_t a_ControllerIndex);
        short GetLeftAnalogX(size_t a_ControllerIndex);
        short GetLeftAnalogY(size_t a_ControllerIndex);
        short GetRightAnalogX(size_t a_ControllerIndex);
        short GetRightAnalogY(size_t a_ControllerIndex);
        short GetLeftTrigger(size_t a_ControllerIndex);
        short GetRightTrigger(size_t a_ControllerIndex);
        bool LeftBumper(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool RightBumper(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool LeftTrigger(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool RightTrigger(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool A(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool B(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool X(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool Y(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool Start(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool Back(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool LeftThumb(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool RightThumb(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool DigitalLeft(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool DigitalRight(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool DigitalUp(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool DigitalDown(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool LeftAnalogLeft(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool LeftAnalogRight(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool LeftAnalogUp(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool LeftAnalogDown(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool RightAnalogLeft(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool RightAnalogRight(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool RightAnalogUp(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);
        bool RightAnalogDown(size_t a_ControllerIndex, EButtonState::Type a_ButtonState);

    private:
        bool IsButtonPressed(EButtonState::Type a_Current, EButtonState::Type a_ToCheck);
    };
}