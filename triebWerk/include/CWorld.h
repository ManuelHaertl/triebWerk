#pragma once
namespace triebWerk
{
    class CWorld
    {
    public:
        CWorld();
        ~CWorld();

    public:
        bool Initialize();
        bool Update();
        void Shutdown();
    };
}