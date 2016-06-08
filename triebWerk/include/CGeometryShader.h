#pragma once
#include <IShader.h>

namespace triebWerk
{
	class CGeometryShader : public IShader
	{
	public:
		ID3D11GeometryShader* m_pD3DGeometryShader;

	public:
		CGeometryShader();
		~CGeometryShader();

	public:
		void* GetD3D11Shader() final;
	};
}