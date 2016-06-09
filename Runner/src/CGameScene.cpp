#include <CGameScene.h>

#include <CGameInfo.h>

CGameScene::CGameScene() :
    m_pPlayer(nullptr),
    m_LastPlayerPos(0.0f),
    m_pPoints(nullptr)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Start()
{
    twDebug->Disable();

    m_ValueUpdater.Start();
    m_EnvironmentCreator.Start();
    m_PatternManager.Start();
    CreateText();
    CreatePlayer();
}

void CGameScene::Update()
{
    m_ValueUpdater.Update();

    if (m_pPlayer->HasDied())
    {
        CGameInfo::Instance().Reset();
        m_pPlayer->Reset();
        m_PatternManager.Reset();
        m_EnvironmentCreator.Reset();
    }

    std::string points =
        "Total: " +
        std::to_string(CGameInfo::Instance().m_TotalPoints) +
        "\nCurrent: " +
        std::to_string(CGameInfo::Instance().m_CurrentPoints) +
        "\nx" +
        std::to_string(CGameInfo::Instance().m_Multiplier);
    m_pPoints->Update(points, nullptr, 0);

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

void CGameScene::CreateText()
{
    auto entity = m_pWorld->CreateEntity();
    entity->m_Transform.SetPosition(1.0f, 50.0f, 1.0f);
    entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

    auto pFont = twRenderer->CreateFontDrawable();
    pFont->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardFont"));
    m_pPoints = twFontManager->CreateText("Hallo", twResourceManager->GetFont("Rubik-Regular"), 18);
    pFont->SetText(m_pPoints);
    entity->SetDrawable(pFont);

    m_pWorld->AddEntity(entity);
}

void CGameScene::CreatePlayer()
{
    DirectX::XMFLOAT3 colorPlayer = { 0.0f, 0.0f, 1.0f };

    auto player = m_pWorld->CreateEntity();

    m_LastPlayerPos = 0.0f;

    // Transform
    player->m_Transform.SetPosition(0.0f, 1.0f, 0.0f);
    player->m_Transform.SetRotationDegrees(0.0f, 0.0f, 0.0f);
    player->m_Transform.SetScale(1.0f, 1.0f, 1.0f);

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
