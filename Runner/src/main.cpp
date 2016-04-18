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

    auto player = twWorld->CreateEntity();
    player->SetBehaviour(new CPlayer());
    twWorld->AddEntity(player);

	twEngine.m_pResourceManager->LoadAllFilesInFolder("data");

	triebWerk::CMeshDrawable* mesh = new triebWerk::CMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube.obj");
	mesh->m_Material.m_ConstantBuffer.InitializeConstantBufffer(twEngine.m_pGraphics->GetDevice());

    auto test1 = twWorld->CreateEntity();
	test1->SetDrawable(mesh);

	twWorld->AddEntity(test1);

    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();
    }

	twWorld->RemoveEntity(test1);


    twEngine.Shutdown();
    _CrtDumpMemoryLeaks();
    return 0;
}