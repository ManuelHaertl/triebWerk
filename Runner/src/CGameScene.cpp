#include <CGameScene.h>

#include <CGameInfo.h>
#include <CPostEffects.h>

CGameScene::CGameScene() :
    m_pPlayer(nullptr),
    m_LastPlayerPos(0.0f)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Start()
{
    twDebug->Disable();

    m_ValueUpdater.Start();
    m_DifficultyChanger.Start();
    m_EnvironmentCreator.Start();
    m_PatternManager.Start();
    CreatePlayer();
    CreateText();

    auto entity = twActiveWorld->CreateEntity();
    entity->SetBehaviour(new CPostEffects());
    twActiveWorld->AddEntity(entity);
}

void CGameScene::Update()
{
    m_ValueUpdater.Update();
    m_DifficultyChanger.Update();

    if (m_pPlayer->HasDied())
    {
        m_pPlayer->Reset();
        m_PatternManager.Reset();
        m_EnvironmentCreator.Reset();
        CGameInfo::Instance().Reset();
    }

    //std::string points =
    //    "Total: " +
    //    std::to_string(CGameInfo::Instance().m_TotalPoints) +
    //    "\nCurrent: " +
    //    std::to_string(CGameInfo::Instance().m_CurrentPoints) +
    //    "\nMultiplier: " +
    //    std::to_string(CGameInfo::Instance().m_Multiplier) +
    //    "\nDifficulty: " + 
    //    std::to_string(CGameInfo::Instance().m_Difficulty);
    //
    //m_pPoints->Update(points, nullptr, 0);

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
    m_PatternManager.End();
    m_ValueUpdater.End();
}

void CGameScene::Resume()
{
    twDebug->Disable();
}

void CGameScene::CreatePlayer()
{
    DirectX::XMFLOAT3 colorPlayer = { 0.0f, 0.0f, 1.0f };

    auto player = m_pWorld->CreateEntity();

    m_LastPlayerPos = 0.0f;

    // Transform
    player->m_Transform.SetPosition(0.0f, 1.0f, 0.0f);

    // Behaviour
    m_pPlayer = new CPlayer();
    player->SetBehaviour(m_pPlayer);

    // Drawable
    triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_player");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTexture"));
    mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_player_diff"));
    player->SetDrawable(mesh);

    // Physic
    auto physicEntity = m_pWorld->m_pPhysicWorld->CreatePhysicEntity();

    auto collbox = m_pWorld->m_pPhysicWorld->CreateAABBCollider();
    collbox->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collbox->m_CheckCollision = true;
    physicEntity->AddCollider(collbox);

    auto body = m_pWorld->m_pPhysicWorld->CreateBody();
    body->m_GravityFactor = 0.0f;
    physicEntity->SetBody(body);

    player->SetPhysicEntity(physicEntity);

    m_pWorld->AddEntity(player);
}

void CGameScene::CreateText()
{
}
