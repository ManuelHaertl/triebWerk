#include <CRenderer.h>
#include <iostream>
#include <algorithm>
#include <CEngine.h>
#include <CInstancedFontBatch.h>

triebWerk::CRenderer::CRenderer() 
	: m_pDefaultBlendState(nullptr)
	, m_pDefaultRasterizerState(nullptr)
	, m_pPostEffectBuffer(nullptr)
	, m_PostEffectCounter(0)
	, m_pCurrentCamera(nullptr)
{
}

triebWerk::CRenderer::~CRenderer()
{
}

void triebWerk::CRenderer::Initialize(CGraphics * a_pGraphicsHandle, unsigned int a_ScreenWidth, unsigned int a_ScreenHeight)
{
	//m_RenderBatch.Create(a_pGraphicsHandle);

	m_pRenderTargetList = new CRenderTarget[m_MaxRenderTargetCount];
	m_pPostEffectBuffer = new CPostEffectDrawable*[m_MaxPostEffects];

	for (size_t i = 0; i < m_MaxRenderTargetCount; i++)
	{
		m_pRenderTargetList[i].Initialize(a_pGraphicsHandle, a_ScreenWidth, a_ScreenHeight, i, true);
	}

	m_ScreenHeight = a_ScreenHeight;
	m_ScreenWidth = a_ScreenWidth;
	m_pGraphicsHandle = a_pGraphicsHandle;

	float aspect = (float)m_ScreenWidth / (float)m_ScreenHeight;

	//Create Default Camera
	SetActiveCamera(CreateCamera(aspect, DirectX::XM_PIDIV4, 0.01f, 1000.0f));
	m_pCurrentCamera->m_Transform.SetPosition(0, 0, -5);

	//Get default states
	m_pDefaultRasterizerState = a_pGraphicsHandle->GetDefaultRasterizerState();
	m_pDefaultBlendState = a_pGraphicsHandle->GetDefaultBlendState();

	m_RenderTargetCounter = 1;

	//Create Default RenderTarget Setup
	m_pDefaultPostEffect = CreatePostEffecthDrawable();
	m_pDefaultPostEffect->AddMaterial(CEngine::Instance().m_pResourceManager->GetMaterial("DefaultRenderTarget"));

	m_pRenderTargetList[0].m_pPostEffect = m_pDefaultPostEffect;


	m_ScreenAligendQuadProjection = DirectX::XMMatrixOrthographicLH(static_cast<float>(m_ScreenWidth), static_cast<float>(m_ScreenHeight), -0.1f, 100);
}

void triebWerk::CRenderer::Shutdown()
{
	//m_RenderBatch.Free();

	//m_pPlaneBuffer->Release();

	delete[] m_pRenderTargetList;
	delete[] m_pPostEffectBuffer;

	for (auto pCamera : m_CameraBuffer)
	{
		delete pCamera;
	}

	delete m_pDefaultPostEffect;

	m_CameraBuffer.clear();
}

void triebWerk::CRenderer::AddRenderCommand(IDrawable* a_pRenderCommand)
{
	int renderSlot = a_pRenderCommand->GetRenderTargetSlot();

	m_CommandCounter++;

	if (m_CommandCounter < CRenderBatch::m_MaxDrawables - 1)
	{
		//Sort the commands related to its type
		switch (a_pRenderCommand->GetType())
		{
		case IDrawable::EDrawableType::Mesh:
		{
			//Cast the drawable to a meshdrawable
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
				//User defiend this to be instanced
				if (pMeshDrawable->m_DrawType == CMeshDrawable::EDrawType::DrawIndexedInstanced || pMeshDrawable->m_DrawType == CMeshDrawable::EDrawType::DrawInstanced)
				{
					InstanceBatching(pMeshDrawable, renderSlot);
					break;
				}

				//Add as normal command
				m_pRenderTargetList[renderSlot].m_RenderBatch.m_pOpaqueMeshBuffer[m_pRenderTargetList[renderSlot].m_RenderBatch.m_OpaqueMeshCounter] = pMeshDrawable;
				m_pRenderTargetList[renderSlot].m_RenderBatch.m_OpaqueMeshCounter++;

			}break;
			case CMeshDrawable::ERenderMode::Transparent:
			{
				//add as transparent drawable
				InsertTransparent(pMeshDrawable);
				m_pRenderTargetList[renderSlot].m_RenderBatch.m_TransparentMeshCounter++;
			}
			}break;
		}break;
		case IDrawable::EDrawableType::Font:
		{
			CFontDrawable* pFontDrawable = reinterpret_cast<CFontDrawable*>(a_pRenderCommand);
			
			//Add font if valid to render buffer
			if (CFontDrawable::IsValidDrawable(pFontDrawable))
			{
				m_pRenderTargetList[renderSlot].m_RenderBatch.m_pFontBuffer[m_pRenderTargetList[renderSlot].m_RenderBatch.m_FontCommandCount] = pFontDrawable;
				m_pRenderTargetList[renderSlot].m_RenderBatch.m_FontCommandCount++;
			}
		}break;
		case IDrawable::EDrawableType::PostEffect:
		{
			CPostEffectDrawable* pPostEffectDrawable = reinterpret_cast<CPostEffectDrawable*>(a_pRenderCommand);

			m_pPostEffectBuffer[m_PostEffectCounter] = pPostEffectDrawable;
			m_PostEffectCounter++;

			m_pRenderTargetList[pPostEffectDrawable->m_RenderTargetSlotToStartOff].m_pPostEffect = pPostEffectDrawable;

		}break;
		}

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

triebWerk::CFontDrawable * triebWerk::CRenderer::CreateFontDrawable()
{
	CFontDrawable* drawable = new CFontDrawable(m_pGraphicsHandle);

	return drawable;
}

triebWerk::CMeshDrawable* triebWerk::CRenderer::CreateMeshDrawable()
{
	CMeshDrawable* drawable = new CMeshDrawable();

	return drawable;
}

triebWerk::CPostEffectDrawable* triebWerk::CRenderer::CreatePostEffecthDrawable()
{
	CPostEffectDrawable* pDrawable = new CPostEffectDrawable();
	
	return pDrawable;
}

void triebWerk::CRenderer::DrawScene()
{
	//Update the camera to draw with
	m_pCurrentCamera->Update();

	for (size_t i = 0; i < m_MaxRenderTargetCount; i++)
	{
		if (m_pRenderTargetList[i].m_pPostEffect != nullptr)
		{
			m_pRenderTargetList[i].SetRenderTarget(0);
			m_pRenderTargetList[i].ClearRenderTarget(0);

			m_ActiveRenderTargetSlot = i;
			//Renders all Meshes in buffer
			RenderMeshDrawables();
			ResetRenderStates();
			//Render all fonts
			RenderFontDrawables();
			ResetRenderStates();
		}
	}

	m_pGraphicsHandle->SetBackBufferRenderTarget();
	m_pGraphicsHandle->ClearRenderTarget();

	for (size_t i = 0; i < m_MaxRenderTargetCount; i++)
	{
		//Draw Default Render Target if it has a effect
		if (m_pRenderTargetList[i].m_pPostEffect != nullptr)
		{
			DrawRenderTarget(&m_pRenderTargetList[i]);
		}
	}

	m_pGraphicsHandle->Present();

	//Reset all buffers
	for (size_t i = 0; i < m_MaxRenderTargetCount; i++)
	{
		m_pRenderTargetList[i].m_RenderBatch.Reset();
	}
	
	m_PostEffectCounter = 0;
	m_CommandCounter = 0;

	m_pRenderTargetList[0].m_pPostEffect = m_pDefaultPostEffect;
}

triebWerk::CRenderTarget * triebWerk::CRenderer::GetRenderTarget(unsigned int a_Slot)
{
	return &m_pRenderTargetList[a_Slot];
}

void triebWerk::CRenderer::ResizeRenderer(unsigned int a_ScreenWidth, unsigned int a_ScreenHeight)
{
	for (size_t i = 0; i < m_CameraBuffer.size(); i++)
	{
		m_CameraBuffer[i]->Resize(a_ScreenWidth, a_ScreenHeight);
	}

	for (size_t i = 0; i < m_RenderTargetCounter; i++)
	{
		m_pRenderTargetList[i].Resize(a_ScreenWidth, a_ScreenHeight);
	}

	m_ScreenAligendQuadProjection = DirectX::XMMatrixOrthographicLH(static_cast<float>(a_ScreenWidth), static_cast<float>(a_ScreenHeight), -0.1f, 100);

	m_ScreenHeight = a_ScreenHeight;
	m_ScreenWidth = a_ScreenWidth;
}

void triebWerk::CRenderer::RenderMeshDrawables()
{
	//Sort transparent object from far to near
	SortTransparentObjects();

	for (size_t i = 0; i < m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount; i++)
	{
		//if(m_pInstancedMeshBuffer[i].m_InstanceCount > 10)
		RenderInstancedMeshBatch(i);
	}

	//First draw the opaque objects
	for (size_t i = 0; i < m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_OpaqueMeshCounter; i++)
	{
		RenderMesh(m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pOpaqueMeshBuffer[i]);
	}

	//Second draw now the sorted transparent objects
	for (size_t i = 0; i < m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_TransparentMeshCounter; i++)
	{
		RenderMesh(m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pTransparentMeshBuffer[i]);
	}
}

void triebWerk::CRenderer::RenderFontDrawables()
{
	for (size_t i = 0; i < m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_FontCommandCount; i++)
	{
		RenderFont(m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pFontBuffer[i]);
	}
}

void triebWerk::CRenderer::SetResources(const CMaterial * a_pMaterial)
{
	ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();
	
	//Vertex Shader
	for (size_t i = 0; i < a_pMaterial->m_pVertexShader.m_TextureCount; i++)
	{
		if (a_pMaterial->m_pVertexShader.m_pTextures[i] != nullptr)
		{
			ID3D11ShaderResourceView* pResourceView = a_pMaterial->m_pVertexShader.m_pTextures[i]->GetShaderResourceView();
			pDeviceContext->VSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
		}
	}

	//Geometry Shader
	for (size_t i = 0; i < a_pMaterial->m_pGeometryShader.m_TextureCount; i++)
	{
		if (a_pMaterial->m_pGeometryShader.m_pTextures[i] != nullptr)
		{
			ID3D11ShaderResourceView* pResourceView = a_pMaterial->m_pGeometryShader.m_pTextures[i]->GetShaderResourceView();
			pDeviceContext->GSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
		}
	}

	//PixelShader
	for (size_t i = 0; i < a_pMaterial->m_pPixelShader.m_TextureCount; i++)
	{
		if (a_pMaterial->m_pPixelShader.m_pTextures[i] != nullptr)
		{
			ID3D11ShaderResourceView* pResourceView = a_pMaterial->m_pPixelShader.m_pTextures[i]->GetShaderResourceView();
			pDeviceContext->PSSetShaderResources(static_cast<UINT>(i), 1, &pResourceView);
		}
	}

}

void triebWerk::CRenderer::SetShader(const CMaterial * a_pMaterial)
{
	ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();

	//Vertex Shader
	pDeviceContext->VSSetShader(a_pMaterial->m_pVertexShader.m_pD3DVertexShader, 0, 0);
	
	//InputLayout
	pDeviceContext->IASetInputLayout(a_pMaterial->m_pVertexShader.GetInputLayout());

	//Geometry Shader
	pDeviceContext->GSSetShader(a_pMaterial->m_pGeometryShader.m_pD3DGeometryShader, 0, 0);

	//Pixel Shader
	pDeviceContext->PSSetShader(a_pMaterial->m_pPixelShader.m_pD3DPixelShader, 0, 0);

}

void triebWerk::CRenderer::SetSpefificStates(const CMeshDrawable::SD3D11States * a_pDrawabelStates)
{
	ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();

	if (a_pDrawabelStates->m_pRasterizerState != nullptr)
	{
		pDeviceContext->RSSetState(a_pDrawabelStates->m_pRasterizerState);
	}
	else
	{
		pDeviceContext->RSSetState(m_pDefaultRasterizerState);
	}

	if(a_pDrawabelStates->m_pBlendState != nullptr)
	{
		pDeviceContext->OMSetBlendState(a_pDrawabelStates->m_pBlendState, 0, 0xffffffff);
	}
	else
	{
		pDeviceContext->OMSetBlendState(m_pDefaultBlendState, 0, 0xffffffff);
	}
}

void triebWerk::CRenderer::ResetRenderStates()
{
	ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();
	pDeviceContext->RSSetState(m_pDefaultRasterizerState);
	pDeviceContext->OMSetBlendState(m_pDefaultBlendState, 0, 0xffffffff);
}

void triebWerk::CRenderer::DrawRenderTarget(CRenderTarget* a_pRenderTarget)
{
	//used to swap the rendertarget doublebuffer
	bool swapRenderTarget = true;

	m_pGraphicsHandle->GetDeviceContext()->CopyResource(a_pRenderTarget->m_DefaultSceneTexture.GetD3D11Texture(), a_pRenderTarget->m_Texture[0].GetD3D11Texture());

	//Draw every effect in the drawable
	for (unsigned int i = 0; i < a_pRenderTarget->m_pPostEffect->m_Materials.size(); i++)
	{
		if (i == a_pRenderTarget->m_pPostEffect->m_Materials.size()-1)
		{	
			//if this is the last effect draw it to screen
			m_pGraphicsHandle->SetBackBufferRenderTarget();
			swapRenderTarget = !swapRenderTarget;
		}
		else
		{
			//use the rendertarget which is not in use
			int swapBufferSlot = static_cast<int>(swapRenderTarget);
			a_pRenderTarget->SetRenderTarget(static_cast<unsigned short>(swapBufferSlot));
			a_pRenderTarget->ClearRenderTarget(static_cast<unsigned short>(swapBufferSlot));

			//swap the buffers so the current rendertarget is in use and the old one will be cleared
			swapRenderTarget = !swapRenderTarget;
		}

		//set the rendertarget where the prevoius effect was drawn into
		a_pRenderTarget->m_pPostEffect->m_Materials[i].m_pPixelShader.SetTexture(0, &a_pRenderTarget->m_Texture[swapRenderTarget]);

		//set resources and shader
		SetShader(&a_pRenderTarget->m_pPostEffect->m_Materials[i]);

		//offset the next rendertarget so it wont be culled - not happy with this solution at the moment but it works 
		a_pRenderTarget->m_PlaneTransform.SetPosition(0, 0, static_cast<float>(i * -0.01f));
		a_pRenderTarget->m_pPostEffect->m_Materials[i].m_ConstantBuffer.SetConstantBuffer(m_pGraphicsHandle->GetDeviceContext(), a_pRenderTarget->m_PlaneTransform.GetTransformation(), DirectX::XMMatrixIdentity(), m_ScreenAligendQuadProjection, false);

		SetResources(&a_pRenderTarget->m_pPostEffect->m_Materials[i]);

		UINT offset = 0;
		m_pGraphicsHandle->GetDeviceContext()->IASetVertexBuffers(0, 1, &a_pRenderTarget->m_pPlaneBuffer, &a_pRenderTarget->m_Stride, &offset);

		m_pGraphicsHandle->GetDeviceContext()->Draw(a_pRenderTarget->m_VertexCount, 0);
	}
}

void triebWerk::CRenderer::DrawMesh(const CMeshDrawable * a_pDrawable)
{
	ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();

	switch (a_pDrawable->m_DrawType)
	{
	case CMeshDrawable::EDrawType::Draw:
	{
		//set the vertex buffer and index buffer
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &a_pDrawable->m_pMesh->m_pVertexBuffer, &a_pDrawable->m_Stride, &offset);

		pDeviceContext->IASetPrimitiveTopology(a_pDrawable->m_Topology);
		pDeviceContext->Draw(a_pDrawable->m_pMesh->m_VertexCount, 0);
	}break;

	case CMeshDrawable::EDrawType::DrawIndexed:
	{
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &a_pDrawable->m_pMesh->m_pVertexBuffer, &a_pDrawable->m_Stride, &offset);
		pDeviceContext->IASetIndexBuffer(a_pDrawable->m_pMesh->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		pDeviceContext->IASetPrimitiveTopology(a_pDrawable->m_Topology);
		pDeviceContext->DrawIndexed(static_cast<UINT>(a_pDrawable->m_pMesh->m_IndexCount), 0, 0);
 
	}break;
	
	case CMeshDrawable::EDrawType::DrawIndexedInstanced:
	{

	}break;
	
	case CMeshDrawable::EDrawType::DrawInstanced:
	{

	}break;
	}
}

void triebWerk::CRenderer::RenderFont(CFontDrawable * a_pDrawable)
{
	//ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();

	a_pDrawable->m_Material.m_pPixelShader.SetTexture(0, &a_pDrawable->m_pText->m_pFont->m_LetterMap);

	////Set the shader pipleline
	//SetShader(&a_pDrawable->m_Material);

	////Set constant buffer
	//a_pDrawable->m_Material.m_ConstantBuffer.SetConstantBuffer(pDeviceContext, a_pDrawable->m_Transformation, DirectX::XMMatrixIdentity(), m_pCurrentCamera->GetUIProjection(), true);

	////set the resource needed by the shader pipeline 
	//SetResources(&a_pDrawable->m_Material);

	////Draw the font vertex buffer
	//UINT offset = 0;
	//pDeviceContext->IASetVertexBuffers(0, 1, &a_pDrawable->m_pVertexBuffer, &a_pDrawable->m_Stride, &offset);

	//pDeviceContext->IASetPrimitiveTopology(a_pDrawable->m_Topology);
	//pDeviceContext->Draw(a_pDrawable->m_VertexCount, 0);

	CInstancedFontBatch::Draw(a_pDrawable, m_pGraphicsHandle->GetDevice(), m_pGraphicsHandle->GetDeviceContext(), m_pCurrentCamera);
}

void triebWerk::CRenderer::RenderMesh(CMeshDrawable * a_pDrawable)
{
	ID3D11DeviceContext* pDeviceContext = m_pGraphicsHandle->GetDeviceContext();
	
	//Check if specific states must be set
	SetSpefificStates(&a_pDrawable->m_D3DStates);

	//Set the shader pipleline
	SetShader(&a_pDrawable->m_Material);

	//Set constant buffer
	a_pDrawable->m_Material.m_ConstantBuffer.SetConstantBuffer(pDeviceContext, a_pDrawable->m_Transformation, m_pCurrentCamera->GetViewMatrix(), m_pCurrentCamera->GetProjection(), false);

	//set the resource needed by the shader pipeline 
	SetResources(&a_pDrawable->m_Material);

	//Draw the actual mesh
	DrawMesh(a_pDrawable);
}

void triebWerk::CRenderer::RenderInstancedMeshBatch(size_t a_Index)
{
	auto pDeviceContext = m_pGraphicsHandle->GetDeviceContext();

	CInstancedMeshBatch* pMeshBatch = &m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[a_Index];

	SetSpefificStates(&pMeshBatch->DEBUG_pDrawable->m_D3DStates);

	//Set the shader pipleline
	SetShader(pMeshBatch->m_pMaterial);

	pMeshBatch->m_pMaterial->m_ConstantBuffer.SetConstantBuffer(m_pGraphicsHandle->GetDeviceContext(), DirectX::XMMatrixIdentity(), m_pCurrentCamera->GetViewMatrix(), m_pCurrentCamera->GetProjection(), true);

	//set the resource needed by the shader pipeline 
	SetResources(pMeshBatch->m_pMaterial);

	//Set the buffers
	pMeshBatch->SetBuffers();

	//Draw Buffer
	pDeviceContext->DrawIndexedInstanced(static_cast<UINT>(pMeshBatch->m_Identifier.m_pMeshDeterminer->m_IndexCount), static_cast<UINT>(pMeshBatch->m_InstanceCount), 0, 0, 0);

	//Reset the MeshBatch
	pMeshBatch->Reset();

	////Draw the InstanceBatch
	//m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[a_Index].Draw(m_pCurrentCamera);
	////Resets the InstanceBatch for the next frame
	//m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[a_Index].Reset();
}

void triebWerk::CRenderer::InsertTransparent(CMeshDrawable * a_pDrawable)
{	
	//Get the distance between object and camera
	a_pDrawable->DEBUG_Distance = DirectX::XMVector4LengthEst(DirectX::XMVectorSubtract(a_pDrawable->m_Transformation.r[3], m_pCurrentCamera->m_Transform.GetPosition())).m128_f32[0];

	m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pTransparentMeshBuffer[m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_TransparentMeshCounter] = a_pDrawable;
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
	if (m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_TransparentMeshCounter > 0)
	{
		//Sort transparent meshs form far to near
		std::sort(m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pTransparentMeshBuffer, m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_pTransparentMeshBuffer + m_pRenderTargetList[m_ActiveRenderTargetSlot].m_RenderBatch.m_TransparentMeshCounter, HowToSort);
	}
}

void triebWerk::CRenderer::InstanceBatching(CMeshDrawable * a_pDrawable, const unsigned int a_RenderTargetSlot)
{
	bool createNewInstanceBatch = true;
	size_t batchCount = m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount;

	//Can the drawable be instanced in any existing batch
	for (size_t i = 0; i < batchCount; i++)
	{
		if (a_pDrawable->m_pMesh == m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[i].m_Identifier.m_pMeshDeterminer &&
			a_pDrawable->m_Material.m_ID.GetHash() == m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[i].m_Identifier.m_pMaterialDeterminer)
			//CConstantBuffer::CompareConstantBuffer(m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[i].m_Identifier.m_pConstantBuffer,
			//a_pDrawable->m_Material.m_ConstantBuffer.GetBufferPoint(), a_pDrawable->m_Material.m_ConstantBuffer.m_BufferSize)
		{
			m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[i].AddDrawable(a_pDrawable);
			createNewInstanceBatch = false;
			break;
		}
	}

	//if not create a new instance batch and set the informationsz
	if (createNewInstanceBatch && m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount < m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_MaxInstancedMeshBatch)
	{
		m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount].m_Identifier.m_pMaterialDeterminer = a_pDrawable->m_Material.m_ID.GetHash();
		m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount].m_Identifier.m_pMeshDeterminer = a_pDrawable->m_pMesh;
		m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount].m_pMaterial = &a_pDrawable->m_Material;
		m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount].DEBUG_pDrawable = a_pDrawable;
		m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount].m_Identifier.m_pConstantBuffer = a_pDrawable->m_Material.m_ConstantBuffer.GetBufferPoint();
		m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_pInstancedMeshBuffer[m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount].AddDrawable(a_pDrawable);
		m_pRenderTargetList[a_RenderTargetSlot].m_RenderBatch.m_InstancedMeshBatchCount++;
	}
}
