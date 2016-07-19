#include <CSoundEngine.h>
#include <CDebugLogfile.h>

triebWerk::CSoundEngine::CSoundEngine()
{
}

triebWerk::CSoundEngine::~CSoundEngine()
{
}

bool triebWerk::CSoundEngine::Initialize()
{
	this->m_pDevice = irrklang::createIrrKlangDevice();

	//this->m_pResourceManagerHandle = m_pResourceManagerHandle;

	//this->m_pDevice->setSoundVolume(CConfigManager::Instance().m_Config.m_MasterVolume);

	if (!this->m_pDevice)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void triebWerk::CSoundEngine::UpdateSoundVolumes()
{
	//--
}

void triebWerk::CSoundEngine::PlayBGM(CSound * a_pBGM, bool a_OverrideSameBGM, bool a_ShouldLoop)
{

	if (a_pBGM == nullptr)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Tried to play a nullptr music resource!");
		return;
	}
	else
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

bool triebWerk::CSoundEngine::IsBGMFinished()
{
	return m_CurrentBackgroundMusic->isFinished();
}

void triebWerk::CSoundEngine::CleanUp()
{
	this->m_pDevice->drop();
}
