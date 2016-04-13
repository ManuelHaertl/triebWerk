#include <iostream>
#include <CEngine.h>
#include <CPlayer.h>

int main()
{
    //_crtBreakAlloc = 176;
    if (twEngine.Initialize() == false)
    {
        twEngine.Shutdown();
        return 0;
    }

    auto player = twWorld->CreateEntity();
    player->SetBehaviour(new CPlayer());
    twWorld->AddEntity(player);

    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();
    }

    twEngine.Shutdown();
    _CrtDumpMemoryLeaks();
    return 0;
}