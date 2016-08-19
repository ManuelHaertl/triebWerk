#pragma once

namespace triebWerk
{
	struct SWindowConfig
	{
		int m_WindowStyle;
		char* m_WindowName;
		int m_IconID;
	};

    struct SEngineConfiguration
    {
        const char* m_Name;
        unsigned short m_Width;
        unsigned short m_Height;
        bool m_Fullscreen;
        bool m_VSync;
        unsigned short m_TargetFPS;
        float m_PhysicTimeStamp;
		float m_MasterVolume;
		float m_SFXVolume;
		float m_BGMVolume;
		SWindowConfig m_WindowConfig;
    };
}