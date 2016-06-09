#include <CDebugScene.h>

triebWerk::CMeshDrawable* mesh;
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
		speed += (1.0f * twTime->GetDeltaTime()) * speed;
		mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);
	}

	if (twKeyboard.IsState(triebWerk::EKey::G, triebWerk::EButtonState::Pressed))
	{
		speed -= 1.0f * twTime->GetDeltaTime();
		mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);
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

	auto entity = m_pWorld->CreateEntity();
	entity->m_Transform.SetPosition(0, 0, 0);

	mesh = twRenderer->CreateMeshDrawable();
	mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("checkpoint2");
	mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("PointExpolsion"));
	mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	mesh->m_Material.m_pGeometryShader.SetTexture(0, twResourceManager->GetTexture2D("noise"));
	DirectX::XMFLOAT3 colorBlock = { twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f) };
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &colorBlock);
	speed = 0;
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);
	speed = 0.4f;
	entity->SetDrawable(mesh);
	m_pWorld->AddEntity(entity);

  /*  const int range = 10;
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

                DirectX::XMFLOAT3 colorBlock = { twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f), twRandom::GetNumber(0.0f, 1.0f) };
                mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &colorBlock);

                entity->SetDrawable(mesh);
                m_pWorld->AddEntity(entity);
            }
        }
    }*/
}

void CDebugScene::ResetCamera()
{
    twDebug->Enable();
    twRenderer->GetCurrentActiveCamera()->m_Transform.SetPosition(m_Position);
}
