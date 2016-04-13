#include <iostream>
#include <CEngine.h>
#include <CPlayer.h>
#include <CMeshDrawable.h>

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

	triebWerk::CMeshDrawable* a = new triebWerk::CMeshDrawable();
	a->m_pMesh = new triebWerk::CMesh(twEngine.m_pGraphics->GetDevice(), twEngine.m_pGraphics->GetDeviceContext());

    auto test1 = twWorld->CreateEntity();
	test1->SetDrawable(a);
    twWorld->AddEntity(test1);

    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();
    }

	delete 	a->m_pMesh;
	twWorld->RemoveEntity(test1);

    twEngine.Shutdown();
    _CrtDumpMemoryLeaks();
    return 0;
}