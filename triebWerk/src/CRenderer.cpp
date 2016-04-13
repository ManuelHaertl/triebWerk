#include <CRenderer.h>
#include <iostream>

triebWerk::CRenderer::CRenderer()
{
}

triebWerk::CRenderer::~CRenderer()
{
}

void triebWerk::CRenderer::Initialize(CGraphics * a_pGraphicsHandle, unsigned int a_ScreenWidth, unsigned int a_ScreenHeight)
{
	m_ScreenHeight = a_ScreenHeight;
	m_ScreenWidth = a_ScreenWidth;
	m_pGraphicsHandle = a_pGraphicsHandle;

	SetActiveCamera(CreateCamera(m_ScreenHeight / m_ScreenWidth, DirectX::XM_PIDIV2, -0.01f, 100.0f));

}

void triebWerk::CRenderer::Shutdown()
{
	for (auto pCamera : m_CameraBuffer)
	{
		delete pCamera;
	}

	m_CameraBuffer.clear();
}

void triebWerk::CRenderer::AddRenderCommand(IRenderCommand* a_pRenderCommand)
{
	m_CommandList.push_back(a_pRenderCommand);
}

triebWerk::CCamera* triebWerk::CRenderer::CreateCamera(float a_Aspect, float a_FOV, float a_Near, float a_Far)
{
	CCamera* pCamera = new CCamera(a_Aspect, a_FOV, a_Near, a_Far, m_ScreenHeight, m_ScreenWidth);
	m_CameraBuffer.push_back(pCamera);

	return pCamera;
}

void triebWerk::CRenderer::RemoveCamera(CCamera * a_Camera)
{
	for (size_t i = 0; i < m_CameraBuffer.size(); i++)
	{
		delete m_CameraBuffer[i];
		m_CameraBuffer.erase(m_CameraBuffer.begin() + i);
	}
}

void triebWerk::CRenderer::SetActiveCamera(CCamera * a_pCamera)
{
	m_pCurrentCamera = a_pCamera;
}

triebWerk::CCamera* triebWerk::CRenderer::GetCurrentActiveCamera()
{
	return m_pCurrentCamera;
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
