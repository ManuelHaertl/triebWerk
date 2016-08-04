#include <CDebugScene.h>

triebWerk::CMeshDrawable* mesh;
triebWerk::CPostEffectDrawable* effect;
triebWerk::CMeshDrawable* sunEffect[200];
triebWerk::CEntity* eps;
float timeTo = 0.0f;
int counter = 0;
float g_Shrinking = 10.0f;

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
	twActiveUIWorld->SetReferenceResolution(1200.0f, 800.0f, triebWerk::CUIWorld::EScreenMatchState::Width);

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


	if (twKeyboard.IsState(triebWerk::EKey::U, triebWerk::EButtonState::Down))
	{
		twRenderer->GetCurrentActiveCamera()->SetScreenShake(0.1f, 1.6f);
	}

	if (twKeyboard.IsState(triebWerk::EKey::Q, triebWerk::EButtonState::Down))
	{
		float t = -2.0f;
		g_pFogMa->m_ConstantBuffer.SetValueInBuffer(4, &t);
	}
	if (twKeyboard.IsState(triebWerk::EKey::Y, triebWerk::EButtonState::Down))
	{
		float t = -4.0f;
		g_pFogMa->m_ConstantBuffer.SetValueInBuffer(4, &t);
	}

	if (twKeyboard.IsState(triebWerk::EKey::E, triebWerk::EButtonState::Pressed))
	{

		g_Shrinking -= twTime->GetDeltaTime() * 3;

		//std::cout << g_Shrinking << std::endl;

		if (g_Shrinking < 0.0f)
			g_Shrinking = 0;

		g_pFogMa->m_ConstantBuffer.SetValueInBuffer(9, &g_Shrinking);
	}

	if (twKeyboard.IsState(triebWerk::EKey::R, triebWerk::EButtonState::Pressed))
	{

		g_Shrinking += twTime->GetDeltaTime() * 3;

		//std::cout << g_Shrinking << std::endl;

		g_pFogMa->m_ConstantBuffer.SetValueInBuffer(9, &g_Shrinking);
	}

	if (twKeyboard.IsState(triebWerk::EKey::Z, triebWerk::EButtonState::Pressed))
	{

		float rand = twRandom::GetNumber(-5.0f, 5.0f);

		g_pFogMa->m_ConstantBuffer.SetValueInBuffer(10, &rand);
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
	auto fog = twActiveWorld->CreateEntity();
	fog->m_Transform.SetPosition(0, 0, 0);
	fog->m_Transform.SetRotationDegrees(0.0f, 0, 0);
	fog->m_Transform.SetScale(10, 10, 10);

	auto fogMesh = twRenderer->CreateMeshDrawable();
	fogMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	fogMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	fogMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Fog"));
	fogMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_fog_02"));
	fogMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
	fog->SetDrawable(fogMesh);

	twActiveWorld->AddEntity(fog);

	{
		auto fog = twActiveWorld->CreateEntity();
		fog->m_Transform.SetPosition(0, 0.0f, 0);
		fog->m_Transform.SetRotationDegrees(50.0f, 0, 0);
		fog->m_Transform.SetScale(10, 10, 10);
		auto fogMesh = twRenderer->CreateMeshDrawable();
		fogMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
		fogMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
		fogMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Fog"));
		fogMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_fog_01"));
		fogMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
		fog->SetDrawable(fogMesh);

		twActiveWorld->AddEntity(fog);

	}

	{
		auto fog = twActiveWorld->CreateEntity();
		fog->m_Transform.SetPosition(0, 0.0f, 0);
		fog->m_Transform.SetRotationDegrees(50.0f, 30, 0);
		fog->m_Transform.SetScale(10, 10, 10);
		auto fogMesh = twRenderer->CreateMeshDrawable();
		fogMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
		fogMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
		fogMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Fog"));
		fogMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_fog_03"));
		fogMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
		fog->SetDrawable(fogMesh);

		twActiveWorld->AddEntity(fog);

	}
}

void CDebugScene::CreateDebugFont()
{
	//auto font = twFontManager->LoadFont(twResourceManager->GetFontFace("Rubik-Regular"), 40);
	//auto text = twFontManager->CreateText();
	//text->Set(font, "Font", 1.0f);

	//auto entity = m_pWorld->CreateEntity();
	//entity->m_Transform.SetPosition(400.0f, 300.0f, 0.0f);

	//auto fontDraw = twRenderer->CreateFontDrawable();
	//fontDraw->m_pText = text;
	//fontDraw->m_Material.SetMaterial(twResourceManager->GetMaterial("StandardFont"));
	//DirectX::XMFLOAT3 t = DirectX::XMFLOAT3(0.0f, 0.0f, 0.8f);
	//fontDraw->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &t);

	//entity->SetDrawable(fontDraw);
	//m_pWorld->AddEntity(entity);
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
