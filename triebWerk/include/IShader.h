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
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_InputInstanceDescriptions;
		EShaderType m_ShaderType;

		//Holds the texture pointers
		CTexture2D** m_pTextures;
		//Number of Textures set by the client
		size_t m_TextureCount;

	public:
		IShader();
		virtual ~IShader();

	public:
		void SetInputLayout(ID3D11InputLayout* a_pInputLayout);
		void InitializeTextureBuffer();
		ID3D11InputLayout* GetInputLayout() const;

	public:
		virtual void* GetD3D11Shader() = 0;
		//Set a texture with the same index as in the hlsl file
		void SetTexture(const size_t a_Index, CTexture2D* a_pTexture);

	};
}