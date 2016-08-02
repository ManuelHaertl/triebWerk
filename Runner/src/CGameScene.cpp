#include <CGameScene.h>

#include <CGameInfo.h>
#include <CPostEffects.h>

bool loud = false;

CGameScene::CGameScene()
    : m_pPlayerScript(nullptr)
    , m_LastPlayerPos(0.0f)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Start()
{
    twDebug->Disable();

	twAudio->PlayBGM(twResourceManager->GetSound("Vermair - Rendez Vous"), true, true);
	twAudio->m_pDevice->setSoundVolume(static_cast<float>(loud));
    CreatePlayer();
    CreatePostEffects();

    m_DifficultyChanger.Start();
    m_EnvironmentCreator.Start();
    m_PatternManager.Start();
    m_IngameUI.Start();
}

void CGameScene::Update()
{
    m_DifficultyChanger.Update();

    if (m_pPlayerScript->HasDied())
    {
        m_pPlayerScript->Reset();
        m_PatternManager.Reset();
        m_EnvironmentCreator.Reset();
        CGameInfo::Instance().Reset();
    }

	if (twGamepad.IsState(triebWerk::EGamepadButton::Back, triebWerk::EButtonState::Down, 0))
	{
        twSceneManager->SetActiveScene("Menu");
	}

    if (twKeyboard.IsState(triebWerk::EKey::F3, triebWerk::EButtonState::Down))
    {
        if (!twDebug->IsInDebug())
            twDebug->Enable();
        else
            twDebug->Disable();
    }

    const float metersFlewn = m_pPlayerScript->GetMetersFlewn();
    CGameInfo::Instance().m_CurrentPoints += metersFlewn * PointsPerMeter;

    m_EnvironmentCreator.Update(metersFlewn);
    m_PatternManager.Update(metersFlewn);
    m_IngameUI.Update();
}

void CGameScene::End()
{
    m_EnvironmentCreator.End();
    m_PatternManager.End();
    m_IngameUI.End();
}

void CGameScene::Resume()
{
    m_pPlayerScript->Reset();
    m_PatternManager.Reset();
    m_EnvironmentCreator.Reset();
    CGameInfo::Instance().Reset();
}

void CGameScene::CreatePlayer()
{
    DirectX::XMFLOAT3 colorPlayer = { 0.0f, 0.0f, 1.0f };

    auto entity = m_pWorld->CreateEntity();

    m_LastPlayerPos = 0.0f;

    // Transform
    entity->m_Transform.SetPosition(0.0f, 1.0f, 0.0f);

    // Behaviour
    m_pPlayerScript = new CPlayer();
    entity->SetBehaviour(m_pPlayerScript);

    // Drawable
    triebWerk::CMeshDrawable* mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_player");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardTextureEmissiv"));
    mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_player_diff"));
	mesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_player_emissive_18"));
    entity->SetDrawable(mesh);

    // Physic
    auto physicEntity = m_pWorld->m_pPhysicWorld->CreatePhysicEntity();

    auto collbox = m_pWorld->m_pPhysicWorld->CreateAABBCollider();
    collbox->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collbox->m_CheckCollision = true;
    physicEntity->AddCollider(collbox);

    auto body = m_pWorld->m_pPhysicWorld->CreateBody();
    body->m_GravityFactor = 0.0f;
    physicEntity->SetBody(body);

    entity->SetPhysicEntity(physicEntity);

    m_pWorld->AddEntity(entity);
}

void CGameScene::CreatePostEffects()
{
    auto entity = twActiveWorld->CreateEntity();
    entity->SetBehaviour(new CPostEffects());
    twActiveWorld->AddEntity(entity);
}
