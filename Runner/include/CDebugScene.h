#pragma once
#include <IScene.h>
#include <CEngine.h>

class CDebugScene : public IScene
{
public:
    CDebugScene();
    ~CDebugScene();

    void Start() override;
    void Update() override;
    void End() override;

private:
    void CreateTestCubes();
};