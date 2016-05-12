#pragma once
#include <d3d11.h>
#include <Windows.h>
#include <d3dcompiler.h>
#include <CFileReader.h>
#include <CGraphics.h>
#include <CVertexShader.h>
#include <CPixelShader.h>
#include <CMaterial.h>

namespace triebWerk
{
	class CHLSLParser : CFileReader
	{
	private:
		const static UINT m_CompileFlags = D3DCOMPILE_DEBUG;
		
		const std::string m_VSEntryPoint = "VS_Main";
		const std::string m_PSEntryPoint = "PS_Main";
		const std::string m_HSEntryPoint = "HS_Main";
		const std::string m_GSEntryPoint = "GS_Main";
		const std::string m_DSEntryPoint = "DS_Main";
		const std::string m_CSEntryPoint = "CS_Main";

	private:
		ID3DBlob* m_pVSByteCode;
		ID3DBlob* m_pPSByteCode;
		ID3DBlob* m_pHSByteCode;
		ID3DBlob* m_pGSByteCode;
		ID3DBlob* m_pDSByteCode;
		ID3DBlob* m_pCSByteCode;

	public:
		CHLSLParser();
		~CHLSLParser();

	public:
		void ParseShader(const char* a_pShaderPath, CGraphics* a_pGraphicHandle, CMaterial* a_pMaterialOut);
	
	private:
		//TODO: Write this errors into the log
		void WriteCompileError(ID3DBlob* a_pMessage);
		//TODO: Handle Errors
		void CompileShader(const char* a_pShaderPath);
		ID3D11InputLayout* GetInputLayout(ID3DBlob* a_pShaderByteCode, CGraphics* a_pGraphicHandle);
		void SetConstantBuffers(ID3DBlob* a_pShaderByteCode, CConstantBuffer* a_pConstantBuffer);
		void SetBoundResources(ID3DBlob* a_pShaderbyteCode, IShader* a_PShader);
		void CreateVertexShader(CGraphics* a_pGraphicHandle, CVertexShader* a_pShaderOut);
		void CreatePixelShader(CGraphics* a_pGraphicHandle, CPixelShader* a_pShaderOut);
		void CreateHullShader();
		void CreateGeometryShader();
		void CreateDomainShader();
		void CreateComputeShader();

	private:
		DXGI_FORMAT DetermineInputFormat(const D3D11_SIGNATURE_PARAMETER_DESC& a_rSignature);
	};
}