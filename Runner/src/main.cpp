#include <CEngine.h>
#include <CIntroScene.h>
#include <CValueUpdater.h>
#include <Shlobj.h>

void LoadConfig(triebWerk::SEngineConfiguration& a_rConfig);

int main()
{
    //_crtBreakAlloc = 161532;
#ifdef _DEBUG
	//Show it
#else
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
#endif

    // Initialize the engine
    triebWerk::SEngineConfiguration config;
    LoadConfig(config);

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

void LoadConfig(triebWerk::SEngineConfiguration& a_rConfig)
{
    a_rConfig.m_Name = "AZ-Tec Racer";
    a_rConfig.m_PhysicTimeStamp = 0.01f;
    a_rConfig.m_TargetFPS = 0;

    triebWerk::CTWFParser parser;
    triebWerk::CTWFData data;

    CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
    std::string path = my_documents;
    path += "\\My Games\\AZ-Tec Racer\\config.twf";

    parser.ParseData(path.c_str(), &data);

    if (data.m_ConfigurationTable.size() == 0)
    {
        a_rConfig.m_Width = 1600;
        a_rConfig.m_Height = 900;
        a_rConfig.m_Fullscreen = false;
        a_rConfig.m_VSync = false;
        a_rConfig.m_MasterVolume = 1.0f;
        a_rConfig.m_BGMVolume = 0.6f;
        a_rConfig.m_SFXVolume = 1.0f;
    }
    else
    {
        a_rConfig.m_Width = std::stoi(data.GetValue("width"));
        a_rConfig.m_Height = std::stoi(data.GetValue("height"));
        a_rConfig.m_Fullscreen = std::stoi(data.GetValue("fullscreen"));
        a_rConfig.m_VSync = std::stoi(data.GetValue("vsync"));
        a_rConfig.m_MasterVolume = std::stof(data.GetValue("mastervolume"));
        a_rConfig.m_BGMVolume = std::stof(data.GetValue("bgmvolume"));
        a_rConfig.m_SFXVolume = std::stof(data.GetValue("sfxvolume"));
    }
}