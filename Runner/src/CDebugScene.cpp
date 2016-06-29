#include <CDebugScene.h>

triebWerk::CMeshDrawable* mesh;
triebWerk::CPostEffectDrawable* effect;
triebWerk::CMeshDrawable* sunEffect;
triebWerk::CEntity* eps;
float speed = 1;


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

	sunEffect->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &time);

	//effect->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &time);
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
	//eps = m_pWorld->CreateEntity();
	//effect = twRenderer->CreatePostEffecthDrawable();
	////effect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));

	//effect->AddMaterial(twResourceManager->GetMaterial("ScanLines"));
	//effect->m_RenderTargetSlotToStartOff = 0;
	//eps->SetDrawable(effect);
	//m_pWorld->AddEntity(eps);

	////auto o = twRenderer->GetRenderTarget(1);
	////o->m_PlaneTransform.SetPosition(0, 0, -0.1f);

	//auto entity = m_pWorld->CreateEntity();
	//entity->m_Transform.SetPosition(0,0,0);

	//triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
	//mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_obs_5x5x12_base");
	//mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
	////mesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("noise"));
	//mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	//mesh->m_D3DStates.m_pRasterizerState = twEngine.m_pGraphics->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
	//DirectX::XMFLOAT3 colorBlock = { 0.2f, 0.0f, 0.6f };	
	//mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &colorBlock);

	//entity->SetDrawable(mesh);
	//m_pWorld->AddEntity(entity);

	//auto entity = m_pWorld->CreateEntity();
	//entity->m_Transform.SetPosition(0,0,0);

	//sunEffect = twRenderer->CreateMeshDrawable();
	//sunEffect->m_pMesh = twEngine.m_pResourceManager->GetMesh("sphere");
	//sunEffect->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Sun"));
	//sunEffect->m_Material.m_pVertexShader.SetTexture(0, twEngine.m_pResourceManager->GetTexture2D("WhiteNoise"));
	//sunEffect->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	//sunEffect->m_D3DStates.m_pRasterizerState = twGraphic->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);

	//entity->SetDrawable(sunEffect);
	//m_pWorld->AddEntity(entity);

   /* const int range = 10;
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
                mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
                mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
				mesh->SetRenderTarget(0);
				mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
                DirectX::XMFLOAT3 colorBlock = { twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f) };
                mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &colorBlock);

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
