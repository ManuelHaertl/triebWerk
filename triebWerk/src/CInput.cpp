#include <CInput.h>

triebWerk::CInput::CInput()
{
}

triebWerk::CInput::~CInput()
{
}

bool triebWerk::CInput::Initialize()
{
    m_Gamepad = new CGamepad();
    return true;
}

bool triebWerk::CInput::Update(float a_DeltaTime)
{
    m_Gamepad->Update(a_DeltaTime);
    return true;
}

void triebWerk::CInput::Shutdown()
{
    delete m_Gamepad;
}
