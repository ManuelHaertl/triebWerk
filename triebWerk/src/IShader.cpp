#include <IShader.h>
#include <iostream>

triebWerk::IShader::IShader() :
	m_pInputLayout(nullptr),
	m_pTextures(nullptr),
	m_TextureCount(0)

{
}

triebWerk::IShader::~IShader()
{
	if (m_pTextures != nullptr)
	{
		delete[] m_pTextures;
		m_pTextures = nullptr;
	}

}

void triebWerk::IShader::SetInputLayout(ID3D11InputLayout* a_pInputLayout)
{
	m_pInputLayout = a_pInputLayout;
}

void triebWerk::IShader::InitializeTextureBuffer()
{
	m_TextureCount = m_TextureDescriptions.size();
	if (m_TextureDescriptions.size() > 0)
	{
		m_pTextures = new CTexture2D*[m_TextureDescriptions.size()]{ nullptr };
	}

}

ID3D11InputLayout * triebWerk::IShader::GetInputLayout() const
{
	return m_pInputLayout;
}

void triebWerk::IShader::SetTexture(const size_t a_Index, CTexture2D * a_pTexture)
{
	if (a_pTexture == nullptr)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Tried to add nullptr as Texture!");
		return;
	}
	if (a_Index > m_TextureDescriptions.size() - 1 || m_TextureDescriptions.size() == 0)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Tried to add a Texture in a none a existing slot!");
		return;
	}

	m_pTextures[a_Index] = a_pTexture;

}
