#include <CInstancedMeshBatch.h>
#include <CRandom.h>

triebWerk::CInstancedMeshBatch::CInstancedMeshBatch() :
	m_InstanceCount(0),
	m_pInstanceBuffer(nullptr),
	m_pInstanceDataBuffer(nullptr),
	m_pGraphicsHandle(nullptr),
	m_SizeOfDataPerInstance(0)
{
}

triebWerk::CInstancedMeshBatch::~CInstancedMeshBatch()
{
	delete[] m_pInstanceDataBuffer;
}

void triebWerk::CInstancedMeshBatch::Initialize(CGraphics * a_pGraphicsHandle)
{
	m_pInstanceDataBuffer = new char[MAX_INSTANCE_COUNT * MAX_DATA_PER_INSTANCE];

	m_InstanceCount = 0;
	m_pGraphicsHandle = a_pGraphicsHandle;
}

//void triebWerk::CInstancedMeshBatch::Draw(CCamera* a_pCamera)
//{ 
//	auto pDeviceContext = m_pGraphicsHandle->GetDeviceContext();
//
//	//Build buffer with dyamic size, depends on instance count
//	D3D11_SUBRESOURCE_DATA instanceData;
//	D3D11_BUFFER_DESC instanceBufferDesc;
//
//	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	instanceBufferDesc.ByteWidth = static_cast<UINT>(MAX_DATA_PER_INSTANCE * m_InstanceCount);
//	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	instanceBufferDesc.CPUAccessFlags = 0;
//	instanceBufferDesc.MiscFlags = 0;
//	instanceBufferDesc.StructureByteStride = 0;
//
//	//set the actual per instance data
//	instanceData.pSysMem = m_pInstanceDataBuffer;
//	instanceData.SysMemPitch = 0;
//	instanceData.SysMemSlicePitch = 0;
//
//	m_pGraphicsHandle->GetDevice()->CreateBuffer(&instanceBufferDesc, &instanceData, &m_pInstanceBuffer);
//
//	unsigned int strides[2];
//	unsigned int offsets[2];
//	ID3D11Buffer* bufferPointers[2];
//
//	// Set the buffer strides.
//	strides[0] = DEBUG_pDrawable->m_Stride;
//	strides[1] = MAX_DATA_PER_INSTANCE;
//
//	// Set the buffer offsets.
//	offsets[0] = 0;
//	offsets[1] = 0;
//
//	bufferPointers[0] = m_Identifier.m_pMeshDeterminer->m_pVertexBuffer;
//	bufferPointers[1] = m_pInstanceBuffer;
//
//	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	// Set the vertex and pixel shaders that will be used to render this triangle.
//	pDeviceContext->VSSetShader(m_pMaterial->m_pVertexShader.m_pD3DVertexShader, 0, 0);
//	pDeviceContext->IASetInputLayout(m_pMaterial->m_pVertexShader.GetInputLayout());
//	pDeviceContext->PSSetShader(m_pMaterial->m_pPixelShader.m_pD3DPixelShader, 0, 0);
//    pDeviceContext->GSSetShader(nullptr, nullptr, 0);
//
//	//Set constant buffer for all instances.
//	m_pMaterial->m_ConstantBuffer.SetConstantBuffer(m_pGraphicsHandle->GetDeviceContext(), DirectX::XMMatrixIdentity(), a_pCamera->GetViewMatrix(), a_pCamera->GetProjection(), true);
//
//	//Draw all set textures.
//	for (size_t i = 0; i < m_pMaterial->m_pPixelShader.m_TextureCount; i++)
//	{
//		if (m_pMaterial->m_pPixelShader.m_pTextures[i] != nullptr)
//		{
//			ID3D11ShaderResourceView* pResourceView = DEBUG_pDrawable->m_Material.m_pPixelShader.m_pTextures[i]->GetShaderResourceView();
//			pDeviceContext->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
//		}
//	}
//
//	pDeviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
//	pDeviceContext->IASetIndexBuffer(m_Identifier.m_pMeshDeterminer->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
//
//	pDeviceContext->DrawIndexedInstanced(static_cast<UINT>(m_Identifier.m_pMeshDeterminer->m_IndexCount), static_cast<UINT>(this->m_InstanceCount), 0, 0, 0);
//	
//	//Release the directx instance buffer
//	m_pInstanceBuffer->Release();
//	m_pInstanceBuffer = nullptr;
//}

void triebWerk::CInstancedMeshBatch::SetBuffers()
{
	auto pDeviceContext = m_pGraphicsHandle->GetDeviceContext();

	//Build buffer with dyamic size, depends on instance count
	D3D11_SUBRESOURCE_DATA instanceData;
	D3D11_BUFFER_DESC instanceBufferDesc;

	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = static_cast<UINT>(MAX_DATA_PER_INSTANCE * m_InstanceCount);
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	//set the actual per instance data
	instanceData.pSysMem = m_pInstanceDataBuffer;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	m_pGraphicsHandle->GetDevice()->CreateBuffer(&instanceBufferDesc, &instanceData, &m_pInstanceBuffer);

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = DEBUG_pDrawable->m_Stride;
	strides[1] = MAX_DATA_PER_INSTANCE;

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = m_Identifier.m_pMeshDeterminer->m_pVertexBuffer;
	bufferPointers[1] = m_pInstanceBuffer;

	pDeviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
}

void triebWerk::CInstancedMeshBatch::AddDrawable(CMeshDrawable * a_pDrawable)
{
	//set the values per instance if the shader supports instance rendering
	if (m_InstanceCount <= MAX_INSTANCE_COUNT && a_pDrawable->m_Material.m_pVertexShader.m_SizeOfInstanceDataBytes != 0)
	{
		a_pDrawable->m_Material.m_pVertexShader.SetInstanceData(0, &a_pDrawable->m_Transformation, 64);

		memcpy(m_pInstanceDataBuffer + (m_InstanceCount * MAX_DATA_PER_INSTANCE), a_pDrawable->m_Material.m_pVertexShader.m_pCustomInstanceData, a_pDrawable->m_Material.m_pVertexShader.m_SizeOfInstanceDataBytes);

		m_InstanceCount++;
	}
}

void triebWerk::CInstancedMeshBatch::Reset()
{
	//Release the directx instance buffer
	m_pInstanceBuffer->Release();
	m_pInstanceBuffer = nullptr;

	m_InstanceCount = 0;
	m_Identifier.m_pMaterialDeterminer = 0;
	m_Identifier.m_pMeshDeterminer = nullptr;
	DEBUG_pDrawable = nullptr;
}
