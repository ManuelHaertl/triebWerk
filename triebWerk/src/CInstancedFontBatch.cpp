#include <CInstancedFontBatch.h>

triebWerk::CInstancedFontBatch::CInstancedFontBatch()
{
}

triebWerk::CInstancedFontBatch::~CInstancedFontBatch()
{
}

void triebWerk::CInstancedFontBatch::Draw(CFontDrawable* a_pDrawable, ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, CCamera* a_pCamera)
{
	ID3D11Buffer* pInstanceBuffer = nullptr;

	auto pDeviceContext = a_pDeviceContext;

	//Build buffer with dyamic size, depends on instance count
	D3D11_SUBRESOURCE_DATA instanceData;
	D3D11_BUFFER_DESC instanceBufferDesc;

	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = static_cast<UINT>(sizeof(SLetterInfo) * a_pDrawable->m_pText->m_LetterCount);
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	//set the actual per instance data
	instanceData.pSysMem = a_pDrawable->m_pText->m_pLetterInfo;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	a_pDevice->CreateBuffer(&instanceBufferDesc, &instanceData, &pInstanceBuffer);

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = a_pDrawable->m_Stride;
	strides[1] = sizeof(SLetterInfo);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = a_pDrawable->m_pVertexBuffer;
	bufferPointers[1] = pInstanceBuffer;

	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	pDeviceContext->VSSetShader(a_pDrawable->m_Material.m_pVertexShader.m_pD3DVertexShader, 0, 0);
	pDeviceContext->IASetInputLayout(a_pDrawable->m_Material.m_pVertexShader.GetInputLayout());
	pDeviceContext->PSSetShader(a_pDrawable->m_Material.m_pPixelShader.m_pD3DPixelShader, 0, 0);
	pDeviceContext->GSSetShader(nullptr, nullptr, 0);

	//Set constant buffer for all instances.
	a_pDrawable->m_Material.m_ConstantBuffer.SetConstantBuffer(pDeviceContext, a_pDrawable->m_Transformation, DirectX::XMMatrixIdentity(), a_pCamera->GetUIProjection(), true);

	//Draw all set textures.
	for (size_t i = 0; i < a_pDrawable->m_Material.m_pPixelShader.m_TextureCount; i++)
	{
		if (a_pDrawable->m_Material.m_pPixelShader.m_pTextures[i] != nullptr)
		{
			ID3D11ShaderResourceView* pResourceView = a_pDrawable->m_Material.m_pPixelShader.m_pTextures[i]->GetShaderResourceView();
			pDeviceContext->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
		}
	}

	pDeviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	pDeviceContext->DrawInstanced(a_pDrawable->m_VertexCount, static_cast<UINT>(a_pDrawable->m_pText->m_LetterCount), 0, 0);

	//Release the directx instance buffer
	pInstanceBuffer->Release();
	pInstanceBuffer = nullptr;
}
