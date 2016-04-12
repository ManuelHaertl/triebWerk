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

    auto test1 = twWorld->CreateEntity();
    test1->SetBehaviour(new CPlayer());
    test1->SetBehaviour(new CPlayer());
    test1->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    test1->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
    test1->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
    test1->GetPhysicEntity()->AddCollider(twPhysic->CreateAABB());
    test1->GetPhysicEntity()->AddCollider(twPhysic->CreateAABB());
    test1->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    twWorld->AddEntity(test1);
    test1->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    test1->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
    test1->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
    test1->GetPhysicEntity()->AddCollider(twPhysic->CreateAABB());
    test1->GetPhysicEntity()->AddCollider(twPhysic->CreateAABB());
    test1->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    twWorld->RemoveEntity(test1);

    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();
    }

    twEngine.Shutdown();
    _CrtDumpMemoryLeaks();
    return 0;
}