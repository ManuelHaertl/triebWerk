#pragma once
#include <CGamepad.h>

namespace triebWerk
{
    class CInput
    {
    public:
        CGamepad* m_Gamepad;

    public:
        CInput();
        ~CInput();

    public:
        bool Initialize();
        bool Update();
        void Shutdown();
    };
}