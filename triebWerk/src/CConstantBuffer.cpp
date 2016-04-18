#include <CConstantBuffer.h>

triebWerk::CConstantBuffer::CConstantBuffer()
{
}

triebWerk::CConstantBuffer::~CConstantBuffer()
{
}

void triebWerk::CConstantBuffer::SetConstantBuffer(ID3D11DeviceContext * a_pDeviceContext, const DirectX::XMMATRIX & a_rWorldMatrix, const DirectX::XMMATRIX & a_rViewMatrix, const DirectX::XMMATRIX & a_rProjectionMatrix)
{
	//Force algin 16-bit to transpose
	DirectX::XMMATRIX proj = a_rProjectionMatrix;
	DirectX::XMMATRIX view = a_rViewMatrix;
	DirectX::XMMATRIX world = a_rWorldMatrix;

	SConstantBuffer vsConstData;
	vsConstData.Projection = DirectX::XMMatrixTranspose(proj);
	vsConstData.World = DirectX::XMMatrixTranspose(world);
	vsConstData.View = DirectX::XMMatrixTranspose(view);

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &vsConstData;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	D3D11_MAPPED_SUBRESOURCE subResourceConstantBuffer;
	a_pDeviceContext->Map(this->m_pConstantBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subResourceConstantBuffer);
	memcpy(subResourceConstantBuffer.pData, &vsConstData, sizeof(SConstantBuffer));
	a_pDeviceContext->Unmap(this->m_pConstantBuffer, NULL);

	a_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

void triebWerk::CConstantBuffer::InitializeConstantBufffer(ID3D11Device * a_pDevice)
{
	HRESULT hr;
	SConstantBuffer vsConstData;

	D3D11_BUFFER_DESC constantBufferDescription;
	constantBufferDescription.ByteWidth = sizeof(SConstantBuffer);
	constantBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDescription.MiscFlags = 0;
	constantBufferDescription.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &vsConstData;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	hr = a_pDevice->CreateBuffer(&constantBufferDescription, &initData, &m_pConstantBuffer);
}
