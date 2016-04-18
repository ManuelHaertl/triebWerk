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

	//Create Default Camera
	SetActiveCamera(CreateCamera(static_cast<float>(m_ScreenHeight / m_ScreenWidth), DirectX::XM_PIDIV4, 0.01f, 100.0f));
	m_pCurrentCamera->m_Transform.SetPosition(0, 0, -5);
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
	m_pCurrentCamera->Update();

	for (auto pRenderCommand : m_CommandList)
	{
		switch (pRenderCommand->GetType())
		{
		case IRenderCommand::ECommandType::Mesh:
		{
			CRenderCommandMesh* meshCommand = reinterpret_cast<CRenderCommandMesh*>(pRenderCommand);

			meshCommand->m_pMaterial->m_ConstantBuffer.SetConstantBuffer(this->m_pGraphicsHandle->GetDeviceContext(), meshCommand->m_Transformation, m_pCurrentCamera->GetViewMatrix(), m_pCurrentCamera->GetProjection());

			UINT stride = sizeof(CMesh::SVertex);
			UINT offset = 0;
			m_pGraphicsHandle->GetDeviceContext()->IASetVertexBuffers(0, 1, &meshCommand->m_pMesh->m_pVertexBuffer, &stride, &offset);

			// select which primtive type we are using
			m_pGraphicsHandle->GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			m_pGraphicsHandle->GetDeviceContext()->Draw(meshCommand->m_pMesh->m_VertexCount, 0);

		}break;
		}
	}

	m_pGraphicsHandle->Present();

	m_CommandList.clear();
}
