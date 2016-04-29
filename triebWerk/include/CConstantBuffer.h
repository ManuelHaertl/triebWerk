#pragma once
#include <d3d11shader.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <iostream>

namespace triebWerk
{
	class CConstantBuffer
	{
	public:
		struct SConstantBuffer
		{
			DirectX::XMMATRIX World;
			DirectX::XMMATRIX Projection;
			DirectX::XMMATRIX View;
		};

	public:
		ID3D11Buffer* m_pConstantBuffer;

		D3D11_SHADER_BUFFER_DESC BuffferDescription;
		std::vector<D3D11_SHADER_VARIABLE_DESC> Variables;
		std::vector<D3D11_SHADER_TYPE_DESC> Types;


	private:
		char* m_pBuffer;

	public:
		CConstantBuffer();
		~CConstantBuffer();


	public:
		void FillConstantBuffer(void* a_pPointer ...);

		void SetConstantBuffer(ID3D11DeviceContext* m_pDeviceContext, const DirectX::XMMATRIX& a_rWorldMatrix, const DirectX::XMMATRIX& a_rViewMatrix, const DirectX::XMMATRIX& a_rProjectionMatrix);
		void InitializeConstantBufffer(ID3D11Device* a_pDevice);

	private:

	};


}