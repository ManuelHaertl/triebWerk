#include <iostream>
#include <CEngine.h>
#include <CPlayer.h>

int main()
{
    if (twEngine.Initialize() == false)
    {
        twEngine.Shutdown();
        return 0;
    }

    triebWerk::CEntity* player = twWorld->CreateEntity();
    player->m_pBehaviour = new CPlayer();
    twWorld->AddEntity(player);

    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();
    }

    twEngine.Shutdown();
    return 0;
}