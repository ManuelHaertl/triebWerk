#include <CGameScene.h>

#include <CGameInfo.h>
#include <CPostEffects.h>
#include <CFileWriter.h>

float g_TestValue = 0.0f; 

CGameScene::CGameScene()
    : m_pPlayerScript(nullptr)
    , m_LastPlayerPos(0.0f)
	, m_LastAudioIndex(-1)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Start()
{
    twDebug->Disable();

	//triebWerk::CFileWriter t;
	//t.CreateSaveFile("C:\\Users\\alexander.klinger\\Desktop\\save\\data.twf");
	//t.SetParams("1High", "12312321311");
	//t.SaveFile();

    CreatePlayer();
    CreatePostEffects();
    LoadHighscore();

	twResourceManager->GetAll("data\\Audio\\BGM\\game", &m_Music);

    m_DifficultyChanger.Start();
    m_EnvironmentCreator.Start();
    m_PatternManager.Start();
    m_IngameUI.Start();

    m_pPlayerScript->SetBackground(m_EnvironmentCreator.GetBackground());

}

void CGameScene::Update()
{
    m_DifficultyChanger.Update();

    if (CGameInfo::Instance().m_RestartGame)
    {
        m_pPlayerScript->Reset();
        m_PatternManager.Reset();
        m_EnvironmentCreator.Reset();
        CGameInfo::Instance().Reset();
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

	if (twAudio->IsBGMFinished() == true)
		PlayRandomSong(false);
}

void CGameScene::End()
{
    m_EnvironmentCreator.End();
    m_PatternManager.End();
    m_IngameUI.End();
    SaveHighscore();
}

void CGameScene::Resume()
{
    m_pPlayerScript->Reset();
    m_PatternManager.Reset();
    m_EnvironmentCreator.Reset();
    CGameInfo::Instance().Reset();

	PlayRandomSong(true);
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
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Player"));
    mesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_player_diff"));
	mesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_player_emissive_18"));
	mesh->m_Material.m_pGeometryShader.SetTexture(0, twResourceManager->GetTexture2D("t_noisecolor"));
	mesh->m_Material.m_pGeometryShader.SetTexture(1, twResourceManager->GetTexture2D("t_noise"));
	m_pMaterial = &mesh->m_Material;
	float defaultValue = 0.0f;
	mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &defaultValue);
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

void CGameScene::PlayRandomSong(bool a_FadeIn)
{
	if (m_Music.size() == 0)
		return;

	std::vector<int>musicIndices;
	for (size_t i = 0; i < m_Music.size(); i++)
	{
		if(i != m_LastAudioIndex)
			musicIndices.push_back(i);
	}

	int index = twRandom::GetNumber(0, musicIndices.size() - 1);
	twAudio->PlayBGM(m_Music[musicIndices[index]], true, false);
	m_LastAudioIndex = musicIndices[index];

	if (a_FadeIn)
	{
		twAudio->FadeInBGM(0.05f, true);
	}

}

void CGameScene::LoadHighscore()
{
}

void CGameScene::SaveHighscore()
{
}
