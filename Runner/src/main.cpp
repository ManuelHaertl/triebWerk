#include <CEngine.h>
#include <CGameScene.h>
#include <CDebugScene.h>
#include <CMenuScene.h>
#include <CValueUpdater.h>


int main()
{
    //_crtBreakAlloc = 179147;

    // Initialize the engine
    triebWerk::SEngineConfiguration config;
    config.m_Name = "AZ-TecRunner";
    config.m_PhysicTimeStamp = 0.01f;

	triebWerk::CTWFParser t;
	triebWerk::CTWFData r;

	t.ParseData("C:\\Users\\alexander.klinger\\Documents\\My Games\\A2Tec\\config.twf", &r);

	if (r.m_ConfigurationTable.size() == 0)
	{
		config.m_Width = 1600;
		config.m_Height = 1000;
		config.m_Fullscreen = false;
		config.m_VSync = false;
		config.m_TargetFPS = 60;
		config.m_MasterVolume = 0.0f;
		config.m_BGMVolume = 1.0f;
		config.m_SFXVolume = 1.0f;
	}
	else
	{
		config.m_Width = std::stoi(r.GetValue("width"));
		config.m_Height = std::stoi(r.GetValue("height"));
		config.m_Fullscreen = std::stoi(r.GetValue("fullscreen"));
		config.m_VSync = std::stoi(r.GetValue("vsync"));
		config.m_TargetFPS = std::stoi(r.GetValue("fpslock"));
		config.m_MasterVolume = std::stof(r.GetValue("mastervolume"));
		config.m_BGMVolume = std::stof(r.GetValue("bgmvolume"));
		config.m_SFXVolume = std::stof(r.GetValue("sfxvolume"));
	}

	if (twEngine.Initialize(config) == false)
	{
		twEngine.Shutdown();
		return 0;
	}

    twResourceManager->LoadAllFilesInFolder("data");
    CValueUpdater valueUpdater;
    valueUpdater.Start();
    twSceneManager->AddScene(new CGameScene(), "Game");
    twSceneManager->AddScene(new CMenuScene(), "Menu");
    twSceneManager->AddScene(new CDebugScene(), "Debug");

    twSceneManager->SetActiveScene("Game");
    twSceneManager->SetActiveScene("Menu");

    // main loop, update game & engine
    bool run = true;
    while (run == true)
    {
        valueUpdater.Update();
        run = twEngine.Run();

        if (twKeyboard.IsState(triebWerk::EKey::D1, triebWerk::EButtonState::Down))
        {
            twSceneManager->SetActiveScene("Game");
        }
        if (twKeyboard.IsState(triebWerk::EKey::D2, triebWerk::EButtonState::Down))
        {
            twSceneManager->SetActiveScene("Debug");
        }
    }

    valueUpdater.End();
    twEngine.Shutdown();

    _CrtDumpMemoryLeaks();
    return 0;
}