#pragma once
#include <irrKlang\irrKlang.h>
#include <CID.h>

namespace triebWerk
{
	class CSound
	{
	public:
		enum class ESoundType
		{
			SFX,
			BGM
		};

	public:
		irrklang::ISoundSource* m_pSoundSource;
		ESoundType m_SoundType;
		CID m_SoundID;

	public:
		CSound();
		~CSound();
	};
}