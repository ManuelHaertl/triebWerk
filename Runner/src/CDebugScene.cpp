#include <CDebugScene.h>

triebWerk::CMeshDrawable* mesh;
triebWerk::CPostEffectDrawable* effect;
triebWerk::CMeshDrawable* sunEffect[200];
triebWerk::CEntity* eps;
float timeTo = 0.0f;
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
	CreateMultipleObjects();
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

	if (twKeyboard.IsState(triebWerk::EKey::R, triebWerk::EButtonState::Down))
	{
		effect->RemoveMaterial(0);
	};

	if (twKeyboard.IsState(triebWerk::EKey::U, triebWerk::EButtonState::Down))
	{
		twRenderer->GetCurrentActiveCamera()->SetScreenShake(0.1f, 1.6f);
	};

	float timer = twTime->GetTimeSinceStartup();

	if (g_pPoint != nullptr)
		g_pPoint->m_ConstantBuffer.SetValueInBuffer(4, &timer);

	if (twKeyboard.IsState(triebWerk::EKey::C, triebWerk::EButtonState::Pressed))
	{
		timeTo += 1.0f * twTime->GetDeltaTime();

		effect->m_Materials[1]->m_ConstantBuffer.SetValueInBuffer(4, &timeTo);
	}
	else
	{
		timeTo = 0.0f;
	}
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
	entity->m_Transform.SetScale(500, 5000, 500);
	auto mesh = twRenderer->CreateMeshDrawable();
	mesh->m_pMesh = twResourceManager->GetMesh("ms_cube");
	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	mesh->m_D3DStates.m_pRasterizerState = twGraphic->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
	mesh->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardColor"));
	entity->SetDrawable(mesh);

	m_pWorld->AddEntity(entity);

	//auto entity = m_pWorld->CreateEntity();
	//entity->m_Transform.SetPosition(0, 0, 0);
	//triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	//mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("");
	//mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTextureEmissiv"));
	//mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_player_diff"));
	//mesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_player_emissive_16"));
	//entity->SetDrawable(mesh);
	//m_pWorld->AddEntity(entity);

	//{
	//	auto entity = m_pWorld->CreateEntity();
	//	entity->m_Transform.SetPosition(0, 0, 0);
	//	entity->m_Transform.SetScale(500, 500, 500);
	//	triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	//	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_cube");
	//	mesh->m_D3DStates.m_pRasterizerState = twGraphic->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
	//	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
	//	entity->SetDrawable(mesh);
	//	m_pWorld->AddEntity(entity);
	//}

	auto entityBloom = m_pWorld->CreateEntity();
	effect = twRenderer->CreatePostEffecthDrawable();
	//postEffect->AddMaterial(twResourceManager->GetMaterial("Extract"));
	//postEffect->AddMaterial(twResourceManager->GetMaterial("Blur"));
	//float screenHeight = twWindow->GetScreenHeight();
	//float screenWidth = twWindow->GetScreenWidth();
	//float strength = 1.0f;

	//postEffect->m_Materials[1].m_ConstantBuffer.SetValueInBuffer(4, &screenWidth);
	//postEffect->m_Materials[1].m_ConstantBuffer.SetValueInBuffer(5, &screenHeight);
	//postEffect->m_Materials[1].m_ConstantBuffer.SetValueInBuffer(6, &strength);

	//postEffect->AddMaterial(twResourceManager->GetMaterial("Bloom"));
	//postEffect->m_Materials[2].m_pPixelShader.SetTexture(1, twRenderer->GetRenderTarget(0)->GetSceneTexture());
	effect->AddMaterial(twResourceManager->GetMaterial("LensDistortion"));
	float power = 1.0f;
	effect->m_Materials[0]->m_ConstantBuffer.SetValueInBuffer(4, &power);
	effect->AddMaterial(twResourceManager->GetMaterial("Shockwave"));
	effect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));


	entityBloom->SetDrawable(effect);
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

				DirectX::XMFLOAT3 color = DirectX::XMFLOAT3(twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f));

				triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
				mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_sphere");
				mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Sun"));
				if(g_pPoint == nullptr)
					g_pPoint = &mesh->m_Material;
				mesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("t_whitenoise"));
				mesh->m_Material.m_pVertexShader.SetInstanceData(4, &color, sizeof(DirectX::XMFLOAT3));

				entity->SetDrawable(mesh);
				m_pWorld->AddEntity(entity);
			}
		}
	}
}

void CDebugScene::ResetCamera()
{
    twDebug->Enable();
    twRenderer->GetCurrentActiveCamera()->m_Transform.SetPosition(m_Position);
}
