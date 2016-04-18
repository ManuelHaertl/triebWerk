#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

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

	private:
		ID3D11Buffer* m_pConstantBuffer;

	public:
		CConstantBuffer();
		~CConstantBuffer();

	public:
		void SetConstantBuffer(ID3D11DeviceContext* m_pDeviceContext, const DirectX::XMMATRIX& a_rWorldMatrix, const DirectX::XMMATRIX& a_rViewMatrix, const DirectX::XMMATRIX& a_rProjectionMatrix);
		void InitializeConstantBufffer(ID3D11Device* a_pDevice);

	private:

	};
}