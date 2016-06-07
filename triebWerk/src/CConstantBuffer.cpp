#include <CConstantBuffer.h>

triebWerk::CConstantBuffer::CConstantBuffer() :
	m_pConstantBuffer(nullptr),
	m_pBuffer(nullptr),
	m_BufferSize(0)
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

bool triebWerk::CConstantBuffer::CompareConstantBuffer(const char * a_pBufferA, const char * a_pBufferB, size_t a_BufferSize)
{
	if (a_BufferSize <= 196)
	{
		return true;
	}
	else
	{
		if (memcmp(a_pBufferA + 196, a_pBufferB + 196, a_BufferSize-196) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

//void triebWerk::CConstantBuffer::FillConstantBufferWithSpecialValues(int a_NumberOfArguments ...)
//{
//	va_list arguments;
//	va_start(arguments, a_NumberOfArguments);
//
//	if (a_NumberOfArguments > m_Variables.size() - 3)
//	{
//		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Tried to write in a none existing constant buffer index!");
//		return;
//	}
//
//	for (int x = 0; x < a_NumberOfArguments; x++)
//	{
//		void* p = va_arg(arguments, void*);
//
//		memcpy(m_pBuffer + m_Variables[3 + x].StartOffset, p, m_Variables[3 + x].Size);
//	}
//
//	va_end(arguments);
//}

void triebWerk::CConstantBuffer::SetValueInBuffer(int a_IndexOfValue, void * a_pValueAdress)
{
	if (a_IndexOfValue >= m_Variables.size())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: Tried to write in a none existing constant buffer index!");
		return;
	}

	memcpy(m_pBuffer + m_Variables[a_IndexOfValue].StartOffset, a_pValueAdress, m_Variables[a_IndexOfValue].Size);
}

void triebWerk::CConstantBuffer::SetConstantBuffer(ID3D11DeviceContext * a_pDeviceContext, const DirectX::XMMATRIX & a_rWorldMatrix, const DirectX::XMMATRIX & a_rViewMatrix, const DirectX::XMMATRIX & a_rProjectionMatrix, bool a_IsInstancing)
{
	if (m_pConstantBuffer == nullptr)
	{
		return;
	}

	//Force algin 16-bit to transpose
	DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(a_rWorldMatrix);
	DirectX::XMMATRIX proj = DirectX::XMMatrixTranspose(a_rProjectionMatrix);
	DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(a_rViewMatrix);

	//world = DirectX::XMMatrixTranspose(world);
	//proj = DirectX::XMMatrixTranspose(proj);
	//view = DirectX::XMMatrixTranspose(view);

	float is = static_cast<float>(a_IsInstancing);

	memcpy(m_pBuffer, &world, 64);
	memcpy(m_pBuffer + 64, &proj, 64);
	memcpy(m_pBuffer + 128, &view, 64);
	memcpy(m_pBuffer + 192, &is, 4);

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = m_pBuffer;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	D3D11_MAPPED_SUBRESOURCE subResourceConstantBuffer;
	a_pDeviceContext->Map(this->m_pConstantBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subResourceConstantBuffer);
	memcpy(subResourceConstantBuffer.pData, m_pBuffer, m_BuffferDescription.Size);
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

	GetBufferSize();
	m_pBuffer = new char[m_BuffferDescription.Size];

	D3D11_BUFFER_DESC constantBufferDescription;
	constantBufferDescription.ByteWidth = m_BuffferDescription.Size;
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

	if (FAILED(hr))
	{
		m_pConstantBuffer;
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: constantbuffer creation failed!");
	}
}

char* triebWerk::CConstantBuffer::GetBufferPoint()
{
	return m_pBuffer;
}

size_t triebWerk::CConstantBuffer::GetBufferSize()
{
	//If Buffer size was calculated earlier
	if (m_BufferSize > 0)
	{
		return m_BufferSize;
	}

	//Calculate the precise size of the buffer without aligment 
	size_t value = 0;
	
	for (size_t i = 0; i < m_Variables.size(); i++)
	{
		value += m_Variables[i].Size;
	}
	m_BufferSize = value;
	return value;
}
