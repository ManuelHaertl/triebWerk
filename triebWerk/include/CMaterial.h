#pragma once
#include <CTexture2D.h>

namespace triebWerk
{
	class CMaterial
	{
	public:
		CTexture2D* m_pTexture;

	public:
		CMaterial();
		~CMaterial();
	};
}