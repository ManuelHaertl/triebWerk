#include <CMesh.h>

triebWerk::CMesh::CMesh(ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext):
	m_pVertexBuffer(nullptr),
	m_VertexCount(0)
{
	//Quad
	SVertices vertices[] =
	{
		{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f },
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f },
		{ -0.5f, -0.5f, 0.5f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, 0.5f, 0.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f },
		{ -0.5f, -0.5, 0.5f, 0.0f, 1.0f },
	};

	D3D11_BUFFER_DESC vertexBufferDescription;
	memset(&vertexBufferDescription, 0, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDescription.ByteWidth = sizeof(SVertices) * 6;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hrError = a_pDevice->CreateBuffer(&vertexBufferDescription, NULL, &this->m_pVertexBuffer);

	D3D11_MAPPED_SUBRESOURCE subResourceVertexBuffer;
	a_pDeviceContext->Map(this->m_pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subResourceVertexBuffer);
	memcpy(subResourceVertexBuffer.pData, vertices, sizeof(vertices));
	a_pDeviceContext->Unmap(this->m_pVertexBuffer, NULL);

	m_VertexCount = 6;
}

triebWerk::CMesh::~CMesh()
{
}