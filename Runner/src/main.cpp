#include <iostream>
#include <CEngine.h>
#include <CPlayer.h>
#include <CMeshDrawable.h>

int main()
{
   // _crtBreakAlloc = 180;
    if (twEngine.Initialize() == false)
    {
        twEngine.Shutdown();
        return 0;
    }

    twEngine.m_pResourceManager->LoadAllFilesInFolder("data");

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