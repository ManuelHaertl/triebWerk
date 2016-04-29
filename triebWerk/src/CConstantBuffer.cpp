#include <CConstantBuffer.h>

triebWerk::CConstantBuffer::CConstantBuffer() :
	m_pBuffer(nullptr),
	m_pConstantBuffer(nullptr)
{
}

triebWerk::CConstantBuffer::~CConstantBuffer()
{
	if (m_pBuffer != nullptr)
		delete m_pBuffer;
}

void triebWerk::CConstantBuffer::FillConstantBuffer(void *a_pPointer ...)
{
	va_list vl;
	va_start(vl, a_pPointer);

	void* p;

	for (p = a_pPointer; p != NULL; p = va_arg(vl, void *)) 
	{
		printf("%p\n", p);
	}
}

void triebWerk::CConstantBuffer::SetConstantBuffer(ID3D11DeviceContext * a_pDeviceContext, const DirectX::XMMATRIX & a_rWorldMatrix, const DirectX::XMMATRIX & a_rViewMatrix, const DirectX::XMMATRIX & a_rProjectionMatrix)
{
	//Force algin 16-bit to transpose
	DirectX::XMMATRIX world = a_rWorldMatrix;
	DirectX::XMMATRIX proj = a_rProjectionMatrix;
	DirectX::XMMATRIX view = a_rViewMatrix;

	world = DirectX::XMMatrixTranspose(world);
	proj = DirectX::XMMatrixTranspose(proj);
	view = DirectX::XMMatrixTranspose(view);

	memcpy(m_pBuffer, &world, 64);
	memcpy(m_pBuffer + 64, &proj, 64);
	memcpy(m_pBuffer + 128, &view, 64);

	//DirectX::XMMATRIX world1;
	//DirectX::XMMATRIX proj1;
	//DirectX::XMMATRIX view1;

	//memcpy(&world1, buffer, 64);
	//memcpy(&proj1, buffer + 64, 64);
	//memcpy(&view1, buffer + 128, 64);

	SConstantBuffer temp;
	temp.World = world;
	temp.Projection = proj;
	temp.View = view;

	int i = sizeof(SConstantBuffer);

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = m_pBuffer;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	D3D11_MAPPED_SUBRESOURCE subResourceConstantBuffer;
	a_pDeviceContext->Map(this->m_pConstantBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subResourceConstantBuffer);
	memcpy(subResourceConstantBuffer.pData, m_pBuffer, sizeof(SConstantBuffer));
	a_pDeviceContext->Unmap(this->m_pConstantBuffer, NULL);

	a_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

void triebWerk::CConstantBuffer::InitializeConstantBufffer(ID3D11Device * a_pDevice)
{
	//m_pBuffer = new char[BuffferDescription.Size];
	m_pBuffer = new char[192];

	HRESULT hr;

	D3D11_BUFFER_DESC constantBufferDescription;
	constantBufferDescription.ByteWidth = sizeof(SConstantBuffer);
	constantBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDescription.MiscFlags = 0;
	constantBufferDescription.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &m_pBuffer;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	hr = a_pDevice->CreateBuffer(&constantBufferDescription, &initData, &m_pConstantBuffer);
}
