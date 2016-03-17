#pragma once
namespace triebWerk
{
    class CInput
    {
    public:
        CInput();
        ~CInput();

    public:
        bool Initialize();
        bool Update();
        void Shutdown();
    };
}