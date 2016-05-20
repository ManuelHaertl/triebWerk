#include <CGameScene.h>

CGameScene::CGameScene() :
    m_pPlayer(nullptr)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Start()
{
    m_EnvironmentCreator.Start();
    m_PatternManager.LoadPattern();
    CreatePlayer();
}

void CGameScene::Update()
{
    if (twKeyboard.IsState(triebWerk::EKey::F3, triebWerk::EButtonState::Down))
    {
        if (!twDebug->IsInDebug())
            twDebug->Enable();
        else
            twDebug->Disable();
    }

    if (twKeyboard.IsState(triebWerk::EKey::Up, triebWerk::EButtonState::Down))
    {
        if (CGameInfo::Instance().m_Difficulty < 5)
            CGameInfo::Instance().m_Difficulty++;

        std::cout << "Difficulty: " << CGameInfo::Instance().m_Difficulty << std::endl;
    }
    if (twKeyboard.IsState(triebWerk::EKey::Down, triebWerk::EButtonState::Down))
    {
        if (CGameInfo::Instance().m_Difficulty > 1)
            CGameInfo::Instance().m_Difficulty--;

        std::cout << "Difficulty: " << CGameInfo::Instance().m_Difficulty << std::endl;
    }

    const float metersFlewn = m_pPlayer->GetMetersFlewn();
    m_EnvironmentCreator.Update(metersFlewn);
    m_PatternManager.Update(metersFlewn);
}

void CGameScene::End()
{
    m_EnvironmentCreator.End();
}

void CGameScene::CreatePlayer()
{
    DirectX::XMFLOAT3 colorPlayer = { 0.0f, 0.0f, 1.0f };

    auto player = twWorld->CreateEntity();

    // Transform
    player->m_Transform.SetPosition(0.0f, 1.0f, 0.0f);
    player->m_Transform.SetRotationDegrees(0.0f, 0.0f, 0.0f);
    player->m_Transform.SetScale(1.5f, 0.7f, 2.0f);

    // Behaviour
    m_pPlayer = new CPlayer();
    player->SetBehaviour(m_pPlayer);

    // Drawable
    triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(3, &colorPlayer);
    player->SetDrawable(mesh);

    // Physic
    auto physicEntity = twPhysic->CreatePhysicEntity();

    auto collbox = twPhysic->CreateAABBCollider();
    collbox->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collbox->m_CheckCollision = true;
    physicEntity->AddCollider(collbox);

    auto body = twPhysic->CreateBody();
    body->m_GravityFactor = 0.0f;
    physicEntity->SetBody(body);

    player->SetPhysicEntity(physicEntity);

    twWorld->AddEntity(player);
}
