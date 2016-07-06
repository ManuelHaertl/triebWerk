#pragma once
#include <irrKlang\irrKlang.h>
#include <CSound.h>

namespace triebWerk
{
	class CSoundEngine
	{
	private:
		irrklang::ISound* m_CurrentBackgroundMusic;

	public:
		irrklang::ISoundEngine* m_pDevice;

	private:
		//CResourceManager* m_pResourceManagerHandle;

	public:
		CSoundEngine();
		~CSoundEngine();

	public:
		bool Initialize();
		void UpdateSoundVolumes();
		void PlayBGM(CSound* a_pBGM, bool a_OverrideSameBGM, bool a_ShouldLoop);
		void PlaySFX(CSound* a_pSFX);
		bool IsBGMFinished();
		void CleanUp();
	};
}

