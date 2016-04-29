#pragma once
#include <IShader.h>

namespace triebWerk
{
	class CVertexShader : public IShader
	{
	public:
		ID3D11VertexShader* m_pD3DVertexShader;

	public:
		CVertexShader();
		~CVertexShader();

	public:
		void* GetD3D11Shader() final;
	};
}