#pragma once
#include <CTexture2D.h>
#include <CVertexShader.h>
#include <CPixelShader.h>

namespace triebWerk
{
	class CMaterial
	{
	public:
		CVertexShader* m_pVertexShader;
		CPixelShader* m_pPixelShader;

	public:
		CMaterial();
		~CMaterial();
	};
}