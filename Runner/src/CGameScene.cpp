#include <CGameScene.h>

#include <CGameInfo.h>
#include <CPostEffects.h>
#include <CFileWriter.h>
#include <ShlObj.h>

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
	std::string t = twTime->GetDateString();

    twDebug->Disable();

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

    twActiveUIWorld->SetReferenceResolution(1920, 1080.0f, triebWerk::CUIWorld::EScreenMatchState::Height);
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
    collbox->SetSize(1.77f, 0.68f, 2.48f);
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
    CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
    std::string path = my_documents;
    path += "\\My Games\\AZ-Tec Racer\\highscore.twf";

    twResourceManager->LoadSpecificFile(path.c_str(), true);
    auto file = twResourceManager->GetTWFData("highscore");
    
    if (file == nullptr)
        return;
    
    CHighscore& highscore = CGameInfo::Instance().m_Highscore;
    
    for (auto value : file->m_ConfigurationTable)
    {

		//Score
		if (value.first == "score0") highscore.m_Scores[0] = std::stoi(value.second);
		else if (value.first == "score1") highscore.m_Scores[1] = std::stoi(value.second);
		else if (value.first == "score2") highscore.m_Scores[2] = std::stoi(value.second);
		else if (value.first == "score3") highscore.m_Scores[3] = std::stoi(value.second);
		else if (value.first == "score4") highscore.m_Scores[4] = std::stoi(value.second);
		//Color
		else if (value.first == "colorR0") highscore.m_Colors[0].x = std::stof(value.second);
		else if (value.first == "colorG0") highscore.m_Colors[0].y = std::stof(value.second);
		else if (value.first == "colorB0") highscore.m_Colors[0].z = std::stof(value.second);
		else if (value.first == "colorR1") highscore.m_Colors[1].x = std::stof(value.second);
		else if (value.first == "colorG1") highscore.m_Colors[1].y = std::stof(value.second);
		else if (value.first == "colorB1") highscore.m_Colors[1].z = std::stof(value.second);
		else if (value.first == "colorR2") highscore.m_Colors[2].x = std::stof(value.second);
		else if (value.first == "colorG2") highscore.m_Colors[2].y = std::stof(value.second);
		else if (value.first == "colorB2") highscore.m_Colors[2].z = std::stof(value.second);
		else if (value.first == "colorR3") highscore.m_Colors[3].x = std::stof(value.second);
		else if (value.first == "colorG3") highscore.m_Colors[3].y = std::stof(value.second);
		else if (value.first == "colorB3") highscore.m_Colors[3].z = std::stof(value.second);
		else if (value.first == "colorR4") highscore.m_Colors[4].x = std::stof(value.second);
		else if (value.first == "colorG4") highscore.m_Colors[4].y = std::stof(value.second);
		else if (value.first == "colorB4") highscore.m_Colors[4].z = std::stof(value.second);
		//Date
		else if (value.first == "date0") highscore.m_Dates[0] = value.second;
		else if (value.first == "date1") highscore.m_Dates[1] = value.second;
		else if (value.first == "date2") highscore.m_Dates[2] = value.second;
		else if (value.first == "date3") highscore.m_Dates[3] = value.second;
		else if (value.first == "date4") highscore.m_Dates[4] = value.second;
    }
}

void CGameScene::SaveHighscore()
{
    CHighscore& highscore = CGameInfo::Instance().m_Highscore;

    CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
    std::string path = my_documents;
    path += "\\My Games\\AZ-Tec Racer\\highscore.twf";

    triebWerk::CFileWriter fileWriter;
    if (!fileWriter.CreateSaveFile(path.c_str()))
        return;

	//Score
    fileWriter.SetParams("score0", std::to_string(highscore.m_Scores[0]));
    fileWriter.SetParams("score1", std::to_string(highscore.m_Scores[1]));
    fileWriter.SetParams("score2", std::to_string(highscore.m_Scores[2]));
    fileWriter.SetParams("score3", std::to_string(highscore.m_Scores[3]));
    fileWriter.SetParams("score4", std::to_string(highscore.m_Scores[4]));
	//Color
	fileWriter.SetParams("colorR0", std::to_string(highscore.m_Colors[0].x));
	fileWriter.SetParams("colorG0", std::to_string(highscore.m_Colors[0].y));
	fileWriter.SetParams("colorB0", std::to_string(highscore.m_Colors[0].z));

	fileWriter.SetParams("colorR1", std::to_string(highscore.m_Colors[1].x));
	fileWriter.SetParams("colorG1", std::to_string(highscore.m_Colors[1].y));
	fileWriter.SetParams("colorB1", std::to_string(highscore.m_Colors[1].z));

	fileWriter.SetParams("colorR2", std::to_string(highscore.m_Colors[2].x));
	fileWriter.SetParams("colorG2", std::to_string(highscore.m_Colors[2].y));
	fileWriter.SetParams("colorB2", std::to_string(highscore.m_Colors[2].z));

	fileWriter.SetParams("colorR3", std::to_string(highscore.m_Colors[3].x));
	fileWriter.SetParams("colorG3", std::to_string(highscore.m_Colors[3].y));
	fileWriter.SetParams("colorB3", std::to_string(highscore.m_Colors[3].z));

	fileWriter.SetParams("colorR4", std::to_string(highscore.m_Colors[4].x));
	fileWriter.SetParams("colorG4", std::to_string(highscore.m_Colors[4].y));
	fileWriter.SetParams("colorB4", std::to_string(highscore.m_Colors[4].z));
	//Dates

	highscore.m_Dates[0].resize(highscore.m_Dates[0].size() - 1);
	highscore.m_Dates[1].resize(highscore.m_Dates[1].size() - 1);
	highscore.m_Dates[2].resize(highscore.m_Dates[2].size() - 1);
	highscore.m_Dates[3].resize(highscore.m_Dates[3].size() - 1);
	highscore.m_Dates[4].resize(highscore.m_Dates[4].size() - 1);


	fileWriter.SetParams("date0", highscore.m_Dates[0]);
	fileWriter.SetParams("date1", highscore.m_Dates[1]);
	fileWriter.SetParams("date2", highscore.m_Dates[2]);
	fileWriter.SetParams("date3", highscore.m_Dates[3]);
	fileWriter.SetParams("date4", highscore.m_Dates[4]);

    fileWriter.SaveFile();
}
