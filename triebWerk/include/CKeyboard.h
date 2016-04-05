#pragma once
#include <Windows.h>

#include <EButtonState.h>
#include <EKey.h>

namespace triebWerk
{
    class CKeyboard
    {
    private:
        static const unsigned int HighestKeyValue = 0xFE;
        EButtonState::Type m_KeyState[HighestKeyValue];

        // Update Key values for Buttonstate Released & Pressed
        // because windows doesn't send a message every "tick"
        bool m_UpdateKey;
        unsigned int m_UpdateKeyValue;
        EButtonState::Type m_UpdateButtonState;


    public:
        CKeyboard();
        ~CKeyboard();

        void Update();
        void UpdateMSG(const MSG& a_rMSG);
        bool IsState(const EKey::Type a_Key, const EButtonState::Type a_State) const;
    };
}