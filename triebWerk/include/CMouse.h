#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <Winuser.h>

#include <EButtonState.h>
#include <EMouse.h>

namespace triebWerk
{
    class CMouse
    {
    private:
        static const unsigned short HighestMouseValue = 2;
        EButtonState::Type m_MouseState[HighestMouseValue];

        DirectX::XMINT2 m_Position;
        short m_WheelMovement;

        bool m_UpdateMouse;
        EMouse::Type m_UpdateMouseType;
        EButtonState::Type m_UpdateButtonState;

    public:
        CMouse();
        ~CMouse();

        void Update();
        void UpdateMSG(const MSG& a_rMSG);
        bool IsState(const EMouse::Type a_Mouse, const EButtonState::Type a_State) const;
        DirectX::XMINT2 GetPosition() const;
        short GetWheelMovement() const;
    };
}