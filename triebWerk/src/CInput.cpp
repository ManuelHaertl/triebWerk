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

bool triebWerk::CInput::Update()
{
    m_Gamepad->Update();
    return true;
}

void triebWerk::CInput::Shutdown()
{
    delete m_Gamepad;
}
