#include <CDebugScene.h>

triebWerk::CMeshDrawable* mesh;
triebWerk::CPostEffectDrawable* effect;
triebWerk::CMeshDrawable* sunEffect[200];
triebWerk::CEntity* eps;
float speed = 1;
int counter = 0;

triebWerk::CMaterial* g_pFogMa = nullptr;
triebWerk::CMaterial* g_pPoint = nullptr;

CDebugScene::CDebugScene()
{
}


CDebugScene::~CDebugScene()
{
}

void CDebugScene::Start()
{
    m_Position = DirectX::XMVectorSet(0.0, 0.0, -10.0f, 0.0f);

    ResetCamera();
	CreatePlayground();
	//CreateMultipleObjects();
	CreateDebugFont();
}

void CDebugScene::Update()
{
    if (twKeyboard.IsState(triebWerk::EKey::F3, triebWerk::EButtonState::Down))
    {
        if (!twDebug->IsInDebug())
            twDebug->Enable();
        else
            twDebug->Disable();
    }

	float timer = twTime->GetTimeSinceStartup();

	if (g_pPoint != nullptr)
		g_pPoint->m_ConstantBuffer.SetValueInBuffer(4, &timer);

}

void CDebugScene::End()
{
}

void CDebugScene::Resume()
{
    ResetCamera();
}

void CDebugScene::Pause()
{
    m_Position = twRenderer->GetCurrentActiveCamera()->m_Transform.GetPosition();
}

void CDebugScene::CreatePlayground()
{
	auto entity = m_pWorld->CreateEntity();
	entity->m_Transform.SetPosition(0, 0, 0);
	triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_player");
	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTextureEmissiv"));
	mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_player_diff"));
	mesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_player_emissive_16"));
	entity->SetDrawable(mesh);
	m_pWorld->AddEntity(entity);

	{
		auto entity = m_pWorld->CreateEntity();
		entity->m_Transform.SetPosition(0, 0, 0);
		entity->m_Transform.SetScale(500, 500, 500);
		triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
		mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_cube");
		mesh->m_D3DStates.m_pRasterizerState = twGraphic->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
		mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
		entity->SetDrawable(mesh);
		m_pWorld->AddEntity(entity);
	}

	auto entityBloom = m_pWorld->CreateEntity();
	auto postEffect = twRenderer->CreatePostEffecthDrawable();
	postEffect->AddMaterial(twResourceManager->GetMaterial("Extract"));
	postEffect->AddMaterial(twResourceManager->GetMaterial("Blur"));
	float screenHeight = twWindow->GetScreenHeight();
	float screenWidth = twWindow->GetScreenWidth();
	float strength = 2.0f;

	postEffect->m_Materials[1].m_ConstantBuffer.SetValueInBuffer(4, &screenWidth);
	postEffect->m_Materials[1].m_ConstantBuffer.SetValueInBuffer(5, &screenHeight);
	postEffect->m_Materials[1].m_ConstantBuffer.SetValueInBuffer(6, &strength);

	postEffect->AddMaterial(twResourceManager->GetMaterial("Bloom"));
	postEffect->m_Materials[2].m_pPixelShader.SetTexture(1, twRenderer->GetRenderTarget(0)->GetSceneTexture());
	entityBloom->SetDrawable(postEffect);
	m_pWorld->AddEntity(entityBloom);
}

void CDebugScene::CreateDebugFont()
{
	auto font = twFontManager->LoadFont(twResourceManager->GetFontFace("Rubik-Regular"), 40);
	auto text = twFontManager->CreateText();
	text->Set(font, "Fonn", 1.0f);

	auto entity = m_pWorld->CreateEntity();
	entity->m_Transform.SetPosition(400.0f, 300.0f, 0.0f);

	auto fontDraw = twRenderer->CreateFontDrawable();
	fontDraw->m_pText = text;
	fontDraw->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
	DirectX::XMFLOAT3 t = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	fontDraw->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &t);

	entity->SetDrawable(fontDraw);
	m_pWorld->AddEntity(entity);
}

void CDebugScene::CreateMultipleObjects()
{
	const int range = 50;
	const int incrementer = 10;
	const int freeArea = 5;

	for (int x = -range; x < range; x += incrementer)
	{
		for (int y = -range; y < range; y += incrementer)
		{
			for (int z = -range; z < range; z += incrementer)
			{
				auto entity = m_pWorld->CreateEntity();
				entity->m_Transform.SetPosition(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

				triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
				mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_sphere");
				mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Sun"));
				if(g_pPoint == nullptr)
					g_pPoint = &mesh->m_Material;
				mesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("t_whitenoise"));

				entity->SetDrawable(mesh);
				m_pWorld->AddEntity(entity);

				/*auto entity = m_pWorld->CreateEntity();
				entity->m_Transform.SetPosition(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

				triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
				mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_cube");
				mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("TextureBlending"));
				mesh->m_Material.m_pPixelShader.SetTexture(0, twEngine.m_pResourceManager->GetTexture2D("t1"));
				mesh->m_Material.m_pPixelShader.SetTexture(1, twEngine.m_pResourceManager->GetTexture2D("t2"));
				mesh->m_Material.m_pPixelShader.SetTexture(2, twEngine.m_pResourceManager->GetTexture2D("t3"));

				float dif1T = twRandom::GetNumber(0.0f, 0.4f);


				float dif2T = twRandom::GetNumber(0.0f, 0.6f);;
				float dif3T = 0.0f;

				mesh->m_Material.m_pVertexShader.SetInstanceData(4, &dif1T, sizeof(float));
				mesh->m_Material.m_pVertexShader.SetInstanceData(5, &dif2T, sizeof(float));
				mesh->m_Material.m_pVertexShader.SetInstanceData(6, &dif3T, sizeof(float));

				entity->SetDrawable(mesh);
				m_pWorld->AddEntity(entity);*/
			}
		}
	}
}

void CDebugScene::ResetCamera()
{
    twDebug->Enable();
    twRenderer->GetCurrentActiveCamera()->m_Transform.SetPosition(m_Position);
}
