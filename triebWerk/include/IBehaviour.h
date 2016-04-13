#pragma once

namespace triebWerk
{
    class CEntity;

    class IBehaviour
    {
    public:
        CEntity* m_pEntity;

    public:
        IBehaviour();
        virtual ~IBehaviour();

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void End() = 0;
    };
}