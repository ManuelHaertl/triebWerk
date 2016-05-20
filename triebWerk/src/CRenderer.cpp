#include <CRenderer.h>
#include <iostream>
#include <algorithm>


triebWerk::CRenderer::CRenderer()
{
}

triebWerk::CRenderer::~CRenderer()
{
}

void triebWerk::CRenderer::Initialize(CGraphics * a_pGraphicsHandle, unsigned int a_ScreenWidth, unsigned int a_ScreenHeight)
{
	//Initialize rendercommands buffer
	m_pCommandBuffer = new IDrawable*[m_MaxDrawables];
	m_pTransparentMeshBuffer = new CMeshDrawable*[m_MaxDrawables];
	m_pOpaqueMeshBuffer = new CMeshDrawable*[m_MaxDrawables];
	m_CommandCounter = 0;

	m_ScreenHeight = a_ScreenHeight;
	m_ScreenWidth = a_ScreenWidth;
	m_pGraphicsHandle = a_pGraphicsHandle;

	float aspect = (float)m_ScreenWidth / (float)m_ScreenHeight;

	//Create Default Camera
	SetActiveCamera(CreateCamera(aspect, DirectX::XM_PIDIV4, 0.01f, 100.0f));
	m_pCurrentCamera->m_Transform.SetPosition(0, 0, -5);
}

void triebWerk::CRenderer::Shutdown()
{
	delete[] m_pCommandBuffer;
	delete[] m_pOpaqueMeshBuffer;
	delete[] m_pTransparentMeshBuffer;

	for (auto pCamera : m_CameraBuffer)
	{
		delete pCamera;
	}

	m_CameraBuffer.clear();
}

void triebWerk::CRenderer::AddRenderCommand(IDrawable* a_pRenderCommand)
{
	if (m_CommandCounter < m_MaxDrawables - 1)
	{
		//Sort the commands related to its type
		switch (a_pRenderCommand->GetType())
		{
		case IDrawable::EDrawableType::Mesh:
		{
			CMeshDrawable* pMeshDrawable = reinterpret_cast<CMeshDrawable*>(a_pRenderCommand);

			//Is the drawable valid if not dont add it to the buffer
			if (!CMeshDrawable::IsValidDrawable(pMeshDrawable))
			{
				break;
			}

			//sort out opaque and transparent
			switch (pMeshDrawable->m_RenderMode)
			{
			case CMeshDrawable::ERenderMode::CutOut:
			case CMeshDrawable::ERenderMode::Opaque:
			{
				m_pOpaqueMeshBuffer[m_OpaqueMeshCounter] = pMeshDrawable;
				m_OpaqueMeshCounter++;
				m_CommandCounter++;
			}break;
			case CMeshDrawable::ERenderMode::Transparent:
			{
				SortInsertTransperent(pMeshDrawable);
				m_TransparentMeshCounter++;
				m_CommandCounter++;
			}
			}

		}break;
		}

	}
}

void triebWerk::CRenderer::RenderMeshDrawables()
{
	//Sort transparent object from far to near
	SortTransparentObjects();

	//First draw the opaque objects
	for (size_t i = 0; i < m_OpaqueMeshCounter; i++)
	{
		RenderMesh(m_pOpaqueMeshBuffer[i]);
	}

	//Second draw now the sorted transparent objects
	for (size_t i = 0; i < m_TransparentMeshCounter; i++)
	{
		RenderMesh(m_pTransparentMeshBuffer[i]);
	}
}

triebWerk::CCamera* triebWerk::CRenderer::CreateCamera(float a_Aspect, float a_FOV, float a_Near, float a_Far)
{
	CCamera* pCamera = new CCamera(a_Aspect, a_FOV, a_Near, a_Far, m_ScreenHeight, m_ScreenWidth);
	m_CameraBuffer.push_back(pCamera);

	return pCamera;
}

void triebWerk::CRenderer::RemoveCamera(CCamera * a_pCamera)
{
	for (size_t i = 0; i < m_CameraBuffer.size(); i++)
	{
		if (m_CameraBuffer[i] == a_pCamera)
		{
			delete m_CameraBuffer[i];
			m_CameraBuffer.erase(m_CameraBuffer.begin() + i);
		}
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

triebWerk::CMeshDrawable* triebWerk::CRenderer::CreateMeshDrawable()
{
	CMeshDrawable* drawable = new CMeshDrawable();

	return drawable;
}

void triebWerk::CRenderer::DrawScene()
{
	m_pGraphicsHandle->ClearRenderTarget();

	//Update the camera to draw with
	m_pCurrentCamera->Update();

	//Renders all Meshes in buffer
	RenderMeshDrawables();


	m_pGraphicsHandle->Present();

	m_Transperency.clear();
	m_OpaqueMeshCounter = 0;
	m_TransparentMeshCounter = 0;
	m_CommandCounter = 0;
}

void triebWerk::CRenderer::RenderMesh(CMeshDrawable * a_pDrawable)
{
	ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();

	//Set Vertex and InputLayout
	pDeviceContext->VSSetShader(a_pDrawable->m_Material.m_pVertexShader.m_pD3DVertexShader, 0, 0);
	pDeviceContext->IASetInputLayout(a_pDrawable->m_Material.m_pVertexShader.GetInputLayout());

	//Set pixelshader to use
	pDeviceContext->PSSetShader(a_pDrawable->m_Material.m_pPixelShader.m_pD3DPixelShader, 0, 0);

	//Set constantbuffer
	a_pDrawable->m_Material.m_ConstantBuffer.SetConstantBuffer(pDeviceContext, a_pDrawable->m_Transformation, m_pCurrentCamera->GetViewMatrix(), m_pCurrentCamera->GetProjection());

	//for (size_t i = 0; i < a_pDrawable->m_Material.m_pVertexShader.m_Textures.size(); i++)
	//{
	//	ID3D11ShaderResourceView* pResourceView = a_pDrawable->m_Material.m_pVertexShader.m_Textures[i]->GetShaderResourceView();
	//	m_pGraphicsHandle->GetDeviceContext()->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
	//}

	//Draw all set textures
	for (size_t i = 0; i < a_pDrawable->m_Material.m_pPixelShader.m_TextureCount; i++)
	{
		if (a_pDrawable->m_Material.m_pPixelShader.m_pTextures[i] != nullptr)
		{
			ID3D11ShaderResourceView* pResourceView = a_pDrawable->m_Material.m_pPixelShader.m_pTextures[i]->GetShaderResourceView();
			pDeviceContext->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
		}
	}

	//set the vertex buffer and index buffer
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &a_pDrawable->m_pMesh->m_pVertexBuffer, &a_pDrawable->m_Stride, &offset);
	pDeviceContext->IASetIndexBuffer(a_pDrawable->m_pMesh->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	pDeviceContext->IASetPrimitiveTopology(a_pDrawable->m_Topology);
	pDeviceContext->DrawIndexed(static_cast<UINT>(a_pDrawable->m_pMesh->m_IndexCount), 0, 0);
}

void triebWerk::CRenderer::SortInsertTransperent(CMeshDrawable * a_pDrawable)
{
	//Get the distance between object and camera
	a_pDrawable->DEBUG_Distance = DirectX::XMVector4LengthEst(DirectX::XMVectorSubtract(a_pDrawable->m_Transformation.r[3], m_pCurrentCamera->m_Transform.GetPosition())).m128_f32[0];

	m_pTransparentMeshBuffer[m_TransparentMeshCounter] = a_pDrawable;
}

bool HowToSort(triebWerk::CMeshDrawable * a_pDraw1, triebWerk::CMeshDrawable * a_pDraw2)
{
	if (a_pDraw1->DEBUG_Distance > a_pDraw2->DEBUG_Distance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void triebWerk::CRenderer::SortTransparentObjects()
{
	//Sort transparent meshs form far to near
	std::sort(m_pTransparentMeshBuffer, m_pTransparentMeshBuffer + m_TransparentMeshCounter, HowToSort);
}
