#pragma once
#include <d3d11shader.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <iostream>
#include <CDebugLogfile.h>

namespace triebWerk
{
	class CConstantBuffer
	{
	public:
		ID3D11Buffer* m_pConstantBuffer;

		D3D11_SHADER_BUFFER_DESC m_BuffferDescription;
		std::vector<D3D11_SHADER_VARIABLE_DESC> m_Variables;
		std::vector<D3D11_SHADER_TYPE_DESC> m_Types;
		
		size_t m_BufferSize;

	private:
		char* m_pBuffer;

	public:
		CConstantBuffer();
		~CConstantBuffer();

	public:
		static bool CompareConstantBuffer(const char* a_pBufferA, const char* a_pBufferB, size_t a_BufferSize);

	public:
		//
		//void FillConstantBufferWithSpecialValues(int a_NumberOfArguments ...);
		
		//Set a index identical to the index in the hlsl conatant buffer and set a address to the value
		//Keep in mind that the first three values will be set by the engine (view, world, projection)
		void SetValueInBuffer(int a_IndexOfValue, void* a_pValueAdress);

		void SetConstantBuffer(ID3D11DeviceContext* m_pDeviceContext, const DirectX::XMMATRIX& a_rWorldMatrix, const DirectX::XMMATRIX& a_rViewMatrix, const DirectX::XMMATRIX& a_rProjectionMatrix, bool a_Instancing);
		void InitializeConstantBufffer(ID3D11Device* a_pDevice);
		char* GetBufferPoint();
		size_t GetBufferSize();

	private:


	};


}