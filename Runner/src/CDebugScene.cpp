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
    CreateTestCubes();
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

	if (twKeyboard.IsState(triebWerk::EKey::F, triebWerk::EButtonState::Pressed))
	{
		speed += (1.0f * twTime->GetDeltaTime());
		mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);
	}

	if (twKeyboard.IsState(triebWerk::EKey::G, triebWerk::EButtonState::Pressed))
	{
		speed -= 1.0f * twTime->GetDeltaTime();
		mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);
	}

	//if (twKeyboard.IsState(triebWerk::EKey::X, triebWerk::EButtonState::Pressed))
	//{
	//	eps->RemoveDrawable();
	//}

	if (twKeyboard.IsState(triebWerk::EKey::C, triebWerk::EButtonState::Down))
	{
		twAudio->PlaySFX(twResourceManager->GetSound("SFX_Forcefield"));
	}

	if (twKeyboard.IsState(triebWerk::EKey::H, triebWerk::EButtonState::Down))
	{
		mesh->m_D3DStates.m_pRasterizerState->Release();
		mesh->m_D3DStates.m_pRasterizerState = twEngine.m_pGraphics->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
	}

	if (twKeyboard.IsState(triebWerk::EKey::J, triebWerk::EButtonState::Down))
	{
		mesh->m_D3DStates.m_pRasterizerState->Release();
		mesh->m_D3DStates.m_pRasterizerState = twEngine.m_pGraphics->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);
	}

	float time = twTime->GetTimeSinceStartup();
	for (int i = 0; i < counter; i++)
	{
		sunEffect[i]->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &time);
	}

	g_pFogMa->m_ConstantBuffer.SetValueInBuffer(4, &time);
	g_pPoint->m_ConstantBuffer.SetValueInBuffer(4, &time);
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

void CDebugScene::CreateTestCubes()
{
	/*auto text = twFontManager->CreateText();
	text->SetText("HalloTest");
	text->SetPixelSize(12);
	text->SetFont(twResourceManager->GetFont("Rubik-Regular"));
	text->CreateTexture();

	auto entity = m_pWorld->CreateEntity();
	entity->m_Transform.SetPosition(1.0f, 50.0f, 1.0f);
	entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);
	triebWerk::CFontDrawable* pFont = twRenderer->CreateFontDrawable();
	pFont->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardFont"));
	pFont->SetText(text);
	entity->SetDrawable(pFont);
	m_pWorld->AddEntity(entity);
*/

//	auto entity = m_pWorld->CreateEntity();
//	entity->m_Transform.SetPosition(0, 0, 0);

//	mesh = twRenderer->CreateMeshDrawable();
//	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("points2");
//	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("PointExplosion"));
//	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
//	mesh->m_Material.m_pGeometryShader.SetTexture(0, twResourceManager->GetTexture2D("noise"));
//	DirectX::XMFLOAT3 colorBlock = { twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f) };
//	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &colorBlock);
//	mesh->SetRenderTarget(0);
//	speed = 0;
//	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);
//	mesh->m_D3DStates.m_pRasterizerState = twEngine.m_pGraphics->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
//	speed = 0.01f;
//	entity->SetDrawable(mesh);
//	m_pWorld->AddEntity(entity);
//
	eps = m_pWorld->CreateEntity();
	effect = twRenderer->CreatePostEffecthDrawable();
	effect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));
	//effect->m_Materials[0].m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("WhiteNoise"));
	effect->m_RenderTargetSlotToStartOff = 0;
	eps->SetDrawable(effect);
	m_pWorld->AddEntity(eps);

	{

	auto entity = m_pWorld->CreateEntity();
	entity->m_Transform.SetPosition(0, 2, 0);
	entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

	triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_shadow_05x05");
	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("FogShader"));
	mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_fog_03"));
	mesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise2"));
	g_pFogMa = &mesh->m_Material;
	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	mesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;

	entity->SetDrawable(mesh);
	m_pWorld->AddEntity(entity);
	}

	//auto entity = m_pWorld->CreateEntity();
	//entity->m_Transform.SetPosition(0,0,0);
	//entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

	//triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	//mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_grid");
	//mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("WireframeGrid"));
	//mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	//DirectX::XMFLOAT3 lineColor = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	//DirectX::XMFLOAT3 faceColor = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	//mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &lineColor);
	//mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &faceColor);

	//entity->SetDrawable(mesh);
	//m_pWorld->AddEntity(entity);

	auto entity = m_pWorld->CreateEntity();
	entity->m_Transform.SetPosition(0,0,0);
	entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

	triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_grid");
	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	DirectX::XMFLOAT3 lineColor = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &lineColor);

	entity->SetDrawable(mesh);
	m_pWorld->AddEntity(entity);

	{
		auto entity = m_pWorld->CreateEntity();
		entity->m_Transform.SetPosition(0, 0, 0);
		entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

		triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
		mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_sphere");
		mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Sun"));
		mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
		g_pPoint = &mesh->m_Material;
		mesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("t_whitenoise"));

		entity->SetDrawable(mesh);
		m_pWorld->AddEntity(entity);
	}

	////auto o = twRenderer->GetRenderTarget(1);
	////o->m_PlaneTransform.SetPosition(0, 0, -0.1f);

	//auto entity2 = m_pWorld->CreateEntity();
	//entity2->m_Transform.SetPosition(0, 0, 0);

	//triebWerk::CMeshDrawable* mesh2 = twRenderer->CreateMeshDrawable();
	//mesh2->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_05x30x12_base");
	//mesh2->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
	//mesh2->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	//mesh2->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &t);

	//entity->SetDrawable(mesh2);
	//m_pWorld->AddEntity(entity2);

    /*const int range = 10;
    const int incrementer = 5;
    const int freeArea = 1;

    for (int x = -range; x < range; x += incrementer)
    {
        for (int y = -range; y < range; y += incrementer)
        {
            for (int z = -range; z < range; z += incrementer)
            {
				auto entity = m_pWorld->CreateEntity();
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
				m_pWorld->AddEntity(entity);
            }
        }
    }*/
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

void CDebugScene::ResetCamera()
{
    twDebug->Enable();
    twRenderer->GetCurrentActiveCamera()->m_Transform.SetPosition(m_Position);
}
