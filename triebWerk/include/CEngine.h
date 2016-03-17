#pragma once
#include <CInput.h>
#include <CTime.h>
#include <CWorld.h>

namespace triebWerk
{
    class CEngine
    {
    public:
        CInput* m_pInput;
        CTime* m_pTime;
        CWorld* m_pWorld;

    private:
        CEngine();
        ~CEngine();

    public:
        static CEngine& Instance();

    public:
        bool Initialize();
        bool Run();
        void Shutdown();
    };
}