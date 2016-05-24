#pragma once
#include <CWorld.h>

namespace triebWerk
{
    class IScene
    {
    public:
        CWorld* m_pWorld;

    public:
        IScene();
        virtual ~IScene();

        virtual void Start();
        virtual void Update();
        virtual void End();
        virtual void Pause();
        virtual void Resume();
    };
}