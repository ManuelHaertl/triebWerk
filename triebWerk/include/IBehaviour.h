#pragma once
namespace triebWerk
{
    class IBehaviour
    {
    public:
        IBehaviour();
        virtual ~IBehaviour();

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void End() = 0;
    };
}