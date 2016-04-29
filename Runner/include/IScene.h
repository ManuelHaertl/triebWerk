#pragma once
class IScene
{
public:
    IScene();
    virtual ~IScene();

    virtual void Start();
    virtual void Update();
    virtual void End();
};