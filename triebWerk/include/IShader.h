#pragma once
#include <CConstantBuffer.h>
#include <CTexture2D.h>

namespace triebWerk
{
	class IShader
	{
	public:
		enum class EShaderType
		{
			Vertex,
			Hull,
			Pixel,
			Domain,
			Geometry,
			Compute
		};

	protected:
		ID3D11InputLayout* m_pInputLayout;

	public:
		std::vector<D3D11_SHADER_INPUT_BIND_DESC> m_TextureDescriptions;
		std::vector<D3D11_SHADER_INPUT_BIND_DESC> m_SamplerDescriptions;
		EShaderType m_ShaderType;

		std::vector<CTexture2D*> m_Textures;

	public:
		IShader();
		virtual ~IShader();

	public:
		void SetInputLayout(ID3D11InputLayout* a_pInputLayout);
		ID3D11InputLayout* GetInputLayout();

	public:
		virtual void* GetD3D11Shader() = 0;

	};
}