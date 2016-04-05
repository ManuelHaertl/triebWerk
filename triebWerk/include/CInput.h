#pragma once
#include <CGamepad.h>
#include <CKeyboard.h>
#include <CMouse.h>

namespace triebWerk
{
    class CInput
    {
    public:
        CGamepad m_Gamepad;
        CKeyboard m_Keyboard;
        CMouse m_Mouse;

    public:
        CInput();
        ~CInput();

    public:
        void Update(const float a_DeltaTime);
        void UpdateMSG(const MSG& a_rMsg);
    };
}