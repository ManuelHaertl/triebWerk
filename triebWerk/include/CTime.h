#pragma once
namespace triebWerk
{
    class CTime
    {
    public:
        CTime();
        ~CTime();

    public:
        bool Initialize();
        void Update();
        void Shutdown();
    };
}