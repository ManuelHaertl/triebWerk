#include <CEngine.h>
#include <CSceneManager.h>

int main()
{
    //_crtBreakAlloc = 220;

    // Initialize the engine
    triebWerk::SEngineConfiguration config;
    config.m_Name = "AZ-TecRunner";
    config.m_Width = 1200;
    config.m_Height = 800;
    config.m_Fullscreen = false;
    config.m_VSync = false;
    config.m_TargetFPS = 60;
    config.m_PhysicTimeStamp = 0.016666f;

    if (twEngine.Initialize(config) == false)
    {
        twEngine.Shutdown();
        return 0;
    }

    // initialize the scene manager (game)
    CSceneManager sceneManager;
    sceneManager.Initialize();
    sceneManager.ChangeScene(EScenes::Game);

    // main loop, update game & engine
    bool run = true;
    while (run == true)
    {
        run = false;

        run |= !sceneManager.Update();
        run |= !twEngine.Run();

        run = !run;
    }

    // shutdown first the game and then the engine
    sceneManager.Shutdown();
    twEngine.Shutdown();

    _CrtDumpMemoryLeaks();
    return 0;
}