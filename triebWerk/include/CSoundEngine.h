#pragma once
#include <irrKlang\irrKlang.h>
#include <CSound.h>


namespace triebWerk
{
	class CResourceManager;

	class CSoundEngine
	{
	private:
		irrklang::ISound* m_CurrentBackgroundMusic;
		float m_MasterVolume;
		float m_BGMVolume;
		float m_SFXVolume;

	public:
		irrklang::ISoundEngine* m_pDevice;

	private:
		CResourceManager* m_pResourceManagerHandle;

	public:
		CSoundEngine();
		~CSoundEngine();

	public:
		void Update();
		bool Initialize(CResourceManager* a_pResourceManager, const float a_MasterVolume, const float a_BGMVolume, const float a_SFXVolume);
		void PlayBGM(CSound* a_pBGM, bool a_OverrideSameBGM, bool a_ShouldLoop);
		void PlaySFX(CSound* a_pSFX);
		void StopAllSounds();
		bool IsBGMFinished();

		float GetMasterVolume();
		float GetBGMVolume();
		float GetSFXVolume();

		void SetMasterVolume(const float a_Volume);
		void SetBGMVolume(const float a_Volume);
		void SetSFXVolume(const float a_Volume);

		void CleanUp();

	private:
		void UpdateSoundVolumes();
	};


}

