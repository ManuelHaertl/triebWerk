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

	float aspect = (float)m_ScreenWidth / (float)m_ScreenHeight;

	//Create Default Camera
	SetActiveCamera(CreateCamera(aspect, DirectX::XM_PIDIV4, 0.01f, 100.0f));
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

void triebWerk::CRenderer::AddRenderCommand(IDrawable* a_pRenderCommand)
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

triebWerk::CMeshDrawable* triebWerk::CRenderer::CreateMeshDrawable()
{
	CMeshDrawable* drawable = new CMeshDrawable();

	return drawable;
}

void triebWerk::CRenderer::ZSortTransparency()
{
	for (size_t i = 0; i < m_CommandList.size(); ++i)
	{
		switch (m_CommandList[i]->GetType())
		{
		case IDrawable::EDrawableType::Mesh:
		{
			CMeshDrawable* meshCommand = reinterpret_cast<CMeshDrawable*>(m_CommandList[i]);

			if (meshCommand->m_Transparency == true)
			{
				for (size_t j = 0; j < m_Transperency.size(); ++j)
				{
					DirectX::XMVECTOR test = meshCommand->m_Transformation.r[3];

					DirectX::XMVECTOR dis = DirectX::XMVector4LengthEst(DirectX::XMVectorSubtract(test, m_pCurrentCamera->m_Transform.GetPosition()));
					if (m_Transperency[j]->DEBUG_Distance > dis.m128_f32[0])
					{
						meshCommand->DEBUG_Distance = dis.m128_f32[0];
						m_Transperency.push_back(meshCommand);
						break;
					}
					else
					{
						meshCommand->DEBUG_Distance = dis.m128_f32[0];
						m_Transperency.insert(m_Transperency.begin() + j, meshCommand);
						break;
					}

					int a = 0;
				}

				if (m_Transperency.size() == 0)
				{
					DirectX::XMVECTOR dis = DirectX::XMVector4LengthEst(DirectX::XMVectorSubtract(meshCommand->m_Transformation.r[3], m_pCurrentCamera->m_Transform.GetPosition()));
					
					meshCommand->DEBUG_Distance = dis.m128_f32[0];
					m_Transperency.push_back(meshCommand);

				}

				m_CommandList.erase(m_CommandList.begin()+ i);
				--i;
			}

		}break;
		}
	}
}

void triebWerk::CRenderer::DrawScene()
{
	m_pGraphicsHandle->ClearRenderTarget();
	m_pCurrentCamera->Update();

	ZSortTransparency();

	for (auto pRenderCommand : m_CommandList)
	{
		switch (pRenderCommand->GetType())
		{
		case IDrawable::EDrawableType::Mesh:
		{
			CMeshDrawable* meshCommand = reinterpret_cast<CMeshDrawable*>(pRenderCommand);
			
			//Set Vertex and InputLayout
			this->m_pGraphicsHandle->GetDeviceContext()->VSSetShader(meshCommand->m_Material.m_pVertexShader.m_pD3DVertexShader, 0, 0);
			this->m_pGraphicsHandle->GetDeviceContext()->IASetInputLayout(meshCommand->m_Material.m_pVertexShader.GetInputLayout());

			this->m_pGraphicsHandle->GetDeviceContext()->PSSetShader(meshCommand->m_Material.m_pPixelShader.m_pD3DPixelShader, 0, 0);

			meshCommand->m_Material.m_ConstantBuffer.SetConstantBuffer(this->m_pGraphicsHandle->GetDeviceContext(), meshCommand->m_Transformation, m_pCurrentCamera->GetViewMatrix(), m_pCurrentCamera->GetProjection());

			for(size_t i = 0; i <  meshCommand->m_Material.m_pVertexShader.m_Textures.size(); i++)
			{
				ID3D11ShaderResourceView* pResourceView = meshCommand->m_Material.m_pVertexShader.m_Textures[i]->GetShaderResourceView();
				m_pGraphicsHandle->GetDeviceContext()->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
			}

			for (size_t i = 0; i < meshCommand->m_Material.m_pPixelShader.m_Textures.size(); i++)
			{
				ID3D11ShaderResourceView* pResourceView = meshCommand->m_Material.m_pPixelShader.m_Textures[i]->GetShaderResourceView();
				m_pGraphicsHandle->GetDeviceContext()->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
			}

			UINT offset = 0;
			m_pGraphicsHandle->GetDeviceContext()->IASetVertexBuffers(0, 1, &meshCommand->m_pMesh->m_pVertexBuffer, &meshCommand->m_Stride, &offset);
			m_pGraphicsHandle->GetDeviceContext()->IASetIndexBuffer(meshCommand->m_pMesh->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			m_pGraphicsHandle->GetDeviceContext()->IASetPrimitiveTopology(meshCommand->m_Topology);
			m_pGraphicsHandle->GetDeviceContext()->DrawIndexed(static_cast<UINT>(meshCommand->m_pMesh->m_IndexCount), 0, 0);

		}break;
		}
	}

	for (auto meshCommand : m_Transperency)
	{
		//Set Vertex and InputLayout
		this->m_pGraphicsHandle->GetDeviceContext()->VSSetShader(meshCommand->m_Material.m_pVertexShader.m_pD3DVertexShader, 0, 0);
		this->m_pGraphicsHandle->GetDeviceContext()->IASetInputLayout(meshCommand->m_Material.m_pVertexShader.GetInputLayout());

		this->m_pGraphicsHandle->GetDeviceContext()->PSSetShader(meshCommand->m_Material.m_pPixelShader.m_pD3DPixelShader, 0, 0);

		meshCommand->m_Material.m_ConstantBuffer.SetConstantBuffer(this->m_pGraphicsHandle->GetDeviceContext(), meshCommand->m_Transformation, m_pCurrentCamera->GetViewMatrix(), m_pCurrentCamera->GetProjection());

		for (size_t i = 0; i < meshCommand->m_Material.m_pVertexShader.m_Textures.size(); i++)
		{
			ID3D11ShaderResourceView* pResourceView = meshCommand->m_Material.m_pVertexShader.m_Textures[i]->GetShaderResourceView();
			m_pGraphicsHandle->GetDeviceContext()->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
		}

		for (size_t i = 0; i < meshCommand->m_Material.m_pPixelShader.m_Textures.size(); i++)
		{
			ID3D11ShaderResourceView* pResourceView = meshCommand->m_Material.m_pPixelShader.m_Textures[i]->GetShaderResourceView();
			m_pGraphicsHandle->GetDeviceContext()->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
		}

		UINT offset = 0;
		m_pGraphicsHandle->GetDeviceContext()->IASetVertexBuffers(0, 1, &meshCommand->m_pMesh->m_pVertexBuffer, &meshCommand->m_Stride, &offset);

		m_pGraphicsHandle->GetDeviceContext()->IASetIndexBuffer(meshCommand->m_pMesh->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		m_pGraphicsHandle->GetDeviceContext()->IASetPrimitiveTopology(meshCommand->m_Topology);
		m_pGraphicsHandle->GetDeviceContext()->DrawIndexed(static_cast<UINT>(meshCommand->m_pMesh->m_IndexCount), 0, 0);
	}

	m_pGraphicsHandle->Present();

	m_Transperency.clear();
	m_CommandList.clear();
}
