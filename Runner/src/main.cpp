#include <CEngine.h>
#include <CIntroScene.h>
#include <CValueUpdater.h>
#include <Shlobj.h>

int main()
{
    //_crtBreakAlloc = 179147;

    // Initialize the engine
    triebWerk::SEngineConfiguration config;
    config.m_Name = "AZ-TecRunner";
    config.m_PhysicTimeStamp = 0.01f;

	triebWerk::CTWFParser t;
	triebWerk::CTWFData r;

	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	std::string path = my_documents;
	path += "\\My Games\\AZ-Tec Racer\\config.twf";

	t.ParseData(path.c_str(), &r);

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

    twSceneManager->AddScene(new CIntroScene(), "Intro");
    twSceneManager->SetActiveScene("Intro");

    CValueUpdater valueUpdater;
    valueUpdater.Start();

    // main loop, update game & engine
    bool run = true;
    while (run == true)
    {
        valueUpdater.Update();
        run = twEngine.Run();
    }

    valueUpdater.End();
    twEngine.Shutdown();

    _CrtDumpMemoryLeaks();
    return 0;
}