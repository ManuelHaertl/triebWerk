#pragma once
#include <CTexture2D.h>
#include <CVertexShader.h>
#include <CPixelShader.h>
#include <CConstantBuffer.h>

namespace triebWerk
{
	class CMaterial
	{
	public:
		CVertexShader* m_pVertexShader;
		CPixelShader* m_pPixelShader;
		CConstantBuffer m_ConstantBuffer;

	public:
		CMaterial();
		~CMaterial();
	};
}