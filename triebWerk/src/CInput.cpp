#include <CInput.h>

triebWerk::CInput::CInput()
{
}

triebWerk::CInput::~CInput()
{
}

void triebWerk::CInput::Update(const float a_DeltaTime)
{
    m_Gamepad.Update(a_DeltaTime);
    m_Keyboard.Update();
    m_Mouse.Update();
}

void triebWerk::CInput::UpdateMSG(const MSG& a_rMsg)
{
    m_Keyboard.UpdateMSG(a_rMsg);
    m_Mouse.UpdateMSG(a_rMsg);
}
