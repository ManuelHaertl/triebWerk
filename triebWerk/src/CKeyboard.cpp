#include <CKeyboard.h>

triebWerk::CKeyboard::CKeyboard() :
    m_UpdateKey(false),
    m_UpdateKeyValue(0),
    m_UpdateButtonState(EButtonState::Released)
{
    for (size_t i = 0; i < HighestKeyValue; ++i)
    {
        m_KeyState[i] = EButtonState::Released;
    }
}

triebWerk::CKeyboard::~CKeyboard()
{
}

void triebWerk::CKeyboard::Update()
{
    if (m_UpdateKey == true)
    {
        m_KeyState[m_UpdateKeyValue] = m_UpdateButtonState;
        m_UpdateKey = false;
    }
}

void triebWerk::CKeyboard::UpdateMSG(const MSG & a_rMSG)
{
    switch (a_rMSG.message)
    {
    case WM_KEYDOWN:
    {
        if (m_KeyState[a_rMSG.wParam] == EButtonState::Released)
        {
            m_KeyState[a_rMSG.wParam] = EButtonState::Down;
            m_UpdateKey = true;
            m_UpdateKeyValue = static_cast<unsigned int>(a_rMSG.wParam);
            m_UpdateButtonState = EButtonState::Pressed;
        }
        else
        {
            m_KeyState[a_rMSG.wParam] = EButtonState::Pressed;
        }

        break;
    }

    case WM_KEYUP:
    {
        if (m_KeyState[a_rMSG.wParam] == EButtonState::Pressed)
        {
            m_KeyState[a_rMSG.wParam] = EButtonState::Up;
            m_UpdateKey = true;
            m_UpdateKeyValue = a_rMSG.wParam;
            m_UpdateButtonState = EButtonState::Released;
        }
        else
        {
            m_KeyState[a_rMSG.wParam] = EButtonState::Released;
        }

        break;
    }

    default:
        break;
    }
}

bool triebWerk::CKeyboard::IsState(const EKey::Type a_Key, const EButtonState::Type a_State) const
{
    EButtonState::Type current = m_KeyState[a_Key];

    switch (a_State)
    {
    case EButtonState::Pressed:
    {
        bool value = (current == EButtonState::Pressed) || (current == EButtonState::Down);
        return value;
    }
    case EButtonState::Released:
    { 
        bool value = (current == EButtonState::Released) || (current == EButtonState::Up);
        return value;
    }
    default:
    {
        bool value = (current == a_State);
        return value;
    }
    }
}