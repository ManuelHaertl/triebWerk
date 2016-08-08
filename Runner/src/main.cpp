#include <CEngine.h>
#include <CIntroScene.h>
#include <CValueUpdater.h>

int main()
{
    //_crtBreakAlloc = 179147;

    // Initialize the engine
    triebWerk::SEngineConfiguration config;
    config.m_Name = "AZ-TecRunner";
    config.m_Width = 1600;
    config.m_Height = 1000;
    config.m_Fullscreen = false;
    config.m_VSync = false;
    config.m_TargetFPS = 60;
    config.m_PhysicTimeStamp = 0.01f;
	config.m_MasterVolume = 0.0f;
	config.m_BGMVolume = 1.0f;
	config.m_SFXVolume = 1.0f;

    if (twEngine.Initialize(config) == false)
    {
        twEngine.Shutdown();
        return 0;
    }

    twSceneManager->AddScene(new CIntroScene(), "Intro");
    twSceneManager->SetActiveScene("Intro");

    CValueUpdater valueUpdater;
    valueUpdater.Start();

    // main loop, update game & engine
    bool run = true;
    while (run == true)
    {
        valueUpdater.Update();
        run = twEngine.Run();
    }

    valueUpdater.End();
    twEngine.Shutdown();

    _CrtDumpMemoryLeaks();
    return 0;
}