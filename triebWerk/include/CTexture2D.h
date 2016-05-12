#pragma once
#include <d3d11.h>
#include <vector>

namespace triebWerk
{
	class CTexture2D
	{
	private:
		ID3D11Texture2D *m_pTexture;
		ID3D11ShaderResourceView* m_pShaderResourceView;
		unsigned int m_Height;
		unsigned int m_Width;

	public:
		CTexture2D();
		~CTexture2D();

	public:
		void SetTexture(unsigned int a_Width, unsigned int a_Height, ID3D11Texture2D* a_Texture, ID3D11ShaderResourceView* a_ShaderView);
		ID3D11ShaderResourceView* GetShaderResourceView() const;
		ID3D11Texture2D* GetD3D11Texture() const;

		unsigned int GetHeight() const;
		unsigned int GetWidth() const;
	};
}