#include <CRenderer.h>
#include <iostream>

triebWerk::CRenderer::CRenderer()
{
}

triebWerk::CRenderer::~CRenderer()
{
}

void triebWerk::CRenderer::Initialize(CGraphics * a_pGraphicsHandle)
{
	m_pGraphicsHandle = a_pGraphicsHandle;
}

void triebWerk::CRenderer::AddRenderCommand(IRenderCommand* a_pRenderCommand)
{
	m_CommandList.push_back(a_pRenderCommand);
}

void triebWerk::CRenderer::DrawScene()
{
	m_pGraphicsHandle->ClearRenderTarget();

	for (auto pRenderCommand : m_CommandList)
	{
		switch (pRenderCommand->GetType())
		{
		case IRenderCommand::ECommandType::Mesh:
		{
			CRenderCommandMesh* meshRenderer = reinterpret_cast<CRenderCommandMesh*>(pRenderCommand);

			UINT stride = sizeof(CMesh::SVertices);
			UINT offset = 0;
			m_pGraphicsHandle->GetDeviceContext()->IASetVertexBuffers(0, 1, &meshRenderer->m_pMesh->m_pVertexBuffer, &stride, &offset);

			// select which primtive type we are using
			m_pGraphicsHandle->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			m_pGraphicsHandle->GetDeviceContext()->Draw(meshRenderer->m_pMesh->m_VertexCount, 0);

		}break;
		}
	}

	m_pGraphicsHandle->Present();

	m_CommandList.clear();
}
