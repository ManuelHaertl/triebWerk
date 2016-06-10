#include <CEngine.h>
#include <CGameScene.h>
#include <CDebugScene.h>

int main()
{
    //_crtBreakAlloc = 266734;

    // Initialize the engine
    triebWerk::SEngineConfiguration config;
    config.m_Name = "AZ-TecRunner";
    config.m_Width = 1200;
    config.m_Height = 800;
    config.m_Fullscreen = false;
    config.m_VSync = false;
    config.m_TargetFPS = 6000;
    config.m_PhysicTimeStamp = 0.01f;

    if (twEngine.Initialize(config) == false)
    {
        twEngine.Shutdown();
        return 0;
    }

    twResourceManager->LoadAllFilesInFolder("data");

    twSceneManager->AddScene(new CGameScene(), "Game");
    twSceneManager->AddScene(new CDebugScene(), "Debug");

    twSceneManager->SetActiveScene("Debug");

    // main loop, update game & engine
    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();

        if (twKeyboard.IsState(triebWerk::EKey::D1, triebWerk::EButtonState::Down))
        {
            twSceneManager->SetActiveScene("Game");
        }
        if (twKeyboard.IsState(triebWerk::EKey::D2, triebWerk::EButtonState::Down))
        {
            twSceneManager->SetActiveScene("Debug");
        }
    }

    twEngine.Shutdown();

    _CrtDumpMemoryLeaks();
    return 0;
}