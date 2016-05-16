#include <CConstantBuffer.h>

triebWerk::CConstantBuffer::CConstantBuffer() :
	m_pConstantBuffer(nullptr),
	m_pBuffer(nullptr)
{
}

triebWerk::CConstantBuffer::~CConstantBuffer()
{
	if (m_pBuffer != nullptr)
	{
		delete m_pBuffer;
		m_pBuffer = nullptr;
	}

	if (m_pConstantBuffer != nullptr)
	{
		m_pConstantBuffer->Release();
	}
}

void triebWerk::CConstantBuffer::FillConstantBufferWithSpecialValues(int a_NumberOfArguments ...)
{
	va_list arguments;
	va_start(arguments, a_NumberOfArguments);

	for (int x = 0; x < a_NumberOfArguments; x++)
	{
		void* p = va_arg(arguments, void*);

		memcpy(m_pBuffer + Variables[3 + x].StartOffset, p, Variables[3 + x].Size);
	}

	va_end(arguments);
}

void triebWerk::CConstantBuffer::SetValueInBuffer(int a_IndexOfValue, void * a_pValueAdress)
{
	memcpy(m_pBuffer + Variables[a_IndexOfValue].StartOffset, a_pValueAdress, Variables[a_IndexOfValue].Size);
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

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = m_pBuffer;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	D3D11_MAPPED_SUBRESOURCE subResourceConstantBuffer;
	a_pDeviceContext->Map(this->m_pConstantBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subResourceConstantBuffer);
	memcpy(subResourceConstantBuffer.pData, m_pBuffer, BuffferDescription.Size);
	a_pDeviceContext->Unmap(this->m_pConstantBuffer, NULL);

	a_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	a_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

void triebWerk::CConstantBuffer::InitializeConstantBufffer(ID3D11Device * a_pDevice)
{
	HRESULT hr;
	if (m_pBuffer != nullptr)
	{
		delete m_pBuffer;
		m_pBuffer = nullptr;
	}

	if (m_pConstantBuffer != nullptr)
	{
		m_pConstantBuffer->Release();
	}

	m_pBuffer = new char[BuffferDescription.Size];

	D3D11_BUFFER_DESC constantBufferDescription;
	constantBufferDescription.ByteWidth = BuffferDescription.Size;
	constantBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDescription.MiscFlags = 0;
	constantBufferDescription.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = m_pBuffer;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	hr = a_pDevice->CreateBuffer(&constantBufferDescription, &initData, &m_pConstantBuffer);
}
