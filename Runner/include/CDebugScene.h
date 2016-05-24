#pragma once
#include <CEngine.h>

class CDebugScene : public triebWerk::IScene
{
public:
    CDebugScene();
    ~CDebugScene();

    void Start();
    void Update();
    void End();

private:
    void CreateTestCubes();
};