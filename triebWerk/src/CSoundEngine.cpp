#include <CSoundEngine.h>
#include <CDebugLogfile.h>
#include <CResourceManager.h>

triebWerk::CSoundEngine::CSoundEngine() 
	: m_CurrentBackgroundMusic(nullptr)
	, m_BGMVolume(0.0f)
	, m_MasterVolume(0.0f)
	, m_SFXVolume(0.0f)
{
}

triebWerk::CSoundEngine::~CSoundEngine()
{
}

void triebWerk::CSoundEngine::Update()
{
	m_pDevice->update();
}

bool triebWerk::CSoundEngine::Initialize(CResourceManager* a_pResourceManager, const float a_MasterVolume, const float a_BGMVolume, const float a_SFXVolume)
{
	this->m_pDevice = irrklang::createIrrKlangDevice();
	if (!this->m_pDevice)
	{
		CDebugLogfile::Instance().LogfText(CDebugLogfile::ELogType::Error, false, "Error: Could not initialize the soundengine");
		return false;
	}

	m_pResourceManagerHandle = a_pResourceManager;

	this->m_pDevice->setSoundVolume(a_MasterVolume);
	m_MasterVolume = a_MasterVolume;
	m_BGMVolume = a_BGMVolume;
	m_SFXVolume = a_SFXVolume;


	return true;
}

void triebWerk::CSoundEngine::UpdateSoundVolumes()
{
	//m_pResourceManagerHandle->UpdateDefaultSoundVolumes(m_SFXVolume, m_BGMVolume);
}

void triebWerk::CSoundEngine::PlayBGM(CSound * a_pBGM, bool a_OverrideSameBGM, bool a_ShouldLoop)
{

	if (a_pBGM == nullptr)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Tried to play a nullptr music resource!");
		return;
	}
	else if(m_CurrentBackgroundMusic == nullptr)
	{
		this->m_CurrentBackgroundMusic = this->m_pDevice->play2D(a_pBGM->m_pSoundSource, a_ShouldLoop, false, true);
	}

	if (this->m_CurrentBackgroundMusic->getSoundSource() == a_pBGM->m_pSoundSource && a_OverrideSameBGM == true)
	{
		this->m_CurrentBackgroundMusic->stop();
		this->m_CurrentBackgroundMusic->drop();

		this->m_CurrentBackgroundMusic = this->m_pDevice->play2D(a_pBGM->m_pSoundSource, a_ShouldLoop, false, true);
	}
	else if (this->m_CurrentBackgroundMusic->getSoundSource() != a_pBGM->m_pSoundSource)
	{
		this->m_CurrentBackgroundMusic->stop();
		this->m_CurrentBackgroundMusic->drop();

		this->m_CurrentBackgroundMusic = this->m_pDevice->play2D(a_pBGM->m_pSoundSource, a_ShouldLoop, false, true);
	}
}

void triebWerk::CSoundEngine::PlaySFX(CSound * a_pSFX)
{
	m_pDevice->play2D(a_pSFX->m_pSoundSource);
}

void triebWerk::CSoundEngine::StopAllSounds()
{
	m_pDevice->stopAllSounds();
}

bool triebWerk::CSoundEngine::IsBGMFinished()
{
	return m_CurrentBackgroundMusic->isFinished();
}

float triebWerk::CSoundEngine::GetMasterVolume()
{
	return m_MasterVolume;
}

float triebWerk::CSoundEngine::GetBGMVolume()
{
	return m_BGMVolume;
}

float triebWerk::CSoundEngine::GetSFXVolume()
{
	return m_SFXVolume;
}

void triebWerk::CSoundEngine::SetMasterVolume(const float a_Volume)
{
	m_MasterVolume = a_Volume;
	m_pDevice->setSoundVolume(a_Volume);
}

void triebWerk::CSoundEngine::SetBGMVolume(const float a_Volume)
{
	m_BGMVolume = a_Volume;
	UpdateSoundVolumes();
	m_CurrentBackgroundMusic->setVolume(m_BGMVolume);
}

void triebWerk::CSoundEngine::SetSFXVolume(const float a_Volume)
{
	m_SFXVolume = a_Volume;
	UpdateSoundVolumes();
}

void triebWerk::CSoundEngine::CleanUp()
{
	this->m_pDevice->drop();
}
