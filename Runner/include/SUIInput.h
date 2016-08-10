#pragma once
struct SUIInput
{
    bool m_Left;
    bool m_Right;
    bool m_Up;
    bool m_Down;
    bool m_LeftHold;
    bool m_RightHold;
    bool m_LeftUp;
    bool m_RightUp;

    bool m_ButtonHold;

    bool m_Select;
    bool m_Back;
    bool m_Pause;

    SUIInput()
        : m_Left(false)
        , m_Right(false)
        , m_Up(false)
        , m_Down(false)
        , m_LeftHold(false)
        , m_RightHold(false)
        , m_LeftUp(false)
        , m_RightUp(false)
        , m_Select(false)
        , m_Back(false)
        , m_Pause(false)
    { }
};