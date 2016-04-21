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
	//mesh->m_Material.m_pTexture = twEngine.m_pResourceManager->GetTexture2D("texture.png");

    auto test1 = twWorld->CreateEntity();
    test1->SetBehaviour(new CPlayer());

	twWorld->AddEntity(test1);

    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();

		if (twKeyboard.IsState(triebWerk::EKey::A, triebWerk::EButtonState::Down))
		{
			twEngine.m_pWindow->ChangeWindowSettings(true, 1920, 1080);
		}
		if (twKeyboard.IsState(triebWerk::EKey::S, triebWerk::EButtonState::Down))
		{
			twEngine.m_pWindow->ChangeWindowSettings(false, 800, 800);
		}

		if (twKeyboard.IsState(triebWerk::EKey::D, triebWerk::EButtonState::Down))
		{
			twEngine.m_pWindow->ChangeWindowSettings(true, 800, 600);
		}

    }

    twEngine.Shutdown();
    _CrtDumpMemoryLeaks();
    return 0;
}