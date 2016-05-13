#include <CEngine.h>
#include <CSceneManager.h>

int main()
{
    //_crtBreakAlloc = 53368;

    // Initialize the engine
    if (twEngine.Initialize() == false)
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