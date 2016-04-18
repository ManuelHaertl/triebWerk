#pragma once
#include <CTexture2D.h>
#include <CConstantBuffer.h>

namespace triebWerk
{
	class CMaterial
	{
	public:
		CTexture2D* m_pTexture;
		CConstantBuffer m_ConstantBuffer;

	public:
		CMaterial();
		~CMaterial();
	};
}