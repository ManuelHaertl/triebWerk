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

    //auto player = twWorld->CreateEntity();
    //player->SetBehaviour(new CPlayer());
    //twWorld->AddEntity(player);

	twEngine.m_pResourceManager->LoadAllFilesInFolder("data");

	triebWerk::CMeshDrawable* mesh = new triebWerk::CMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube.obj");
	mesh->m_Material.m_ConstantBuffer.InitializeConstantBufffer(twEngine.m_pGraphics->GetDevice());
	mesh->m_Material.m_pTexture = twEngine.m_pResourceManager->GetTexture2D("texture.png");
	//triebWerk::CMeshDrawable* mesh2 = new triebWerk::CMeshDrawable();
	//mesh2->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube.obj");
	//mesh2->m_Material.m_ConstantBuffer.InitializeConstantBufffer(twEngine.m_pGraphics->GetDevice());
	//
	//auto test2 = twWorld->CreateEntity();
	//test2->SetDrawable(mesh2);
	//test2->m_Transform.SetPosition(2, 0, 0);

    auto test1 = twWorld->CreateEntity();
	test1->SetDrawable(mesh);

	twWorld->AddEntity(test1);
	//twWorld->AddEntity(test2);

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