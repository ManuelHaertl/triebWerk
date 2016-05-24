#include <CDebugScene.h>

CDebugScene::CDebugScene()
{
}

CDebugScene::~CDebugScene()
{
}

void CDebugScene::Start()
{
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
}

void CDebugScene::End()
{
}

void CDebugScene::CreateTestCubes()
{
    auto entity = m_pWorld->CreateEntity();
    entity->m_Transform.SetPosition(0, 0, 0);
    triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_snakeloop_01");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
    mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_snakeloop_diff"));
    //mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
    entity->SetDrawable(mesh);
    m_pWorld->AddEntity(entity);


    //const int range = 30;
    //const int incrementer = 5;
    //const int freeArea = 1;
    //DirectX::XMFLOAT3 colorBlock = { 0.5f, 0.5f, 0.5f };

    //for (int x = -range; x < range; x += incrementer)
    //{
    //    for (int y = -range; y < range; y += incrementer)
    //    {
    //        for (int z = -range; z < range; z += incrementer)
    //        {
    //            auto entity = twWorld->CreateEntity();
    //            entity->m_Transform.SetPosition(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

    //            triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
    //            mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    //            mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
    //mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("images"));
    //            //mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorBlock);
    //            entity->SetDrawable(mesh);
    //            twWorld->AddEntity(entity);
    //        }
    //    }
    //}
}
