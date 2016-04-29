#pragma once
#include <IShader.h>

namespace triebWerk
{
	class CPixelShader : public IShader
	{
	public:
		ID3D11PixelShader* m_pD3DPixelShader;

	public:
		CPixelShader();
		~CPixelShader();

	public:
		void* GetD3D11Shader() final;
	};
}