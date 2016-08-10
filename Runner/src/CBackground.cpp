#include <CBackground.h>
#include <CGameInfo.h>

DirectX::XMFLOAT4 CBackground::ToLerpColors[ToLerpColorsCount] = { DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) };

CBackground::CBackground() 
	: m_pBGSnake(nullptr)
	, m_pBGBassLeft(nullptr)
	, m_pBGBassRight(nullptr)
	, m_Difficulty(1)
	, m_IsLerping(false)
	, m_LerpValue(0)
	, m_IsMultiLerping(false)
	, m_MultiLerpValue(0)
	, m_LerpColors(false)
	, m_LerpColorToValue(0.0f)
	, m_LerpColorValue(0.0)
{
}

CBackground::~CBackground()
{
}

void CBackground::Start()
{
	
	CreateSnakeHead();
	CreateWings();
	CreateEyes();
}

void CBackground::Update()
{
	UpdateMultiplier();

	UpdateDifficultyCircles();

	LerpColor();

	DirectX::XMVECTOR backgroundPos = m_pBGSnake->m_Transform.GetPosition();
	backgroundPos.m128_f32[1] = (std::sin(twTime->GetTimeSinceStartup() ) * 0.5f + 0.5f) * 40;
	backgroundPos.m128_f32[1] += 120.0f;
	m_pBGSnake->m_Transform.SetPosition(backgroundPos);
	backgroundPos.m128_f32[2] += 1.0f;
	m_pSnakeFeather->m_Transform.SetPosition(backgroundPos);
	DirectX::XMVECTOR eyePosLeft = backgroundPos;
	eyePosLeft.m128_f32[0] -= 88;
	eyePosLeft.m128_f32[1] += 24;
	DirectX::XMVECTOR eyePosRight = backgroundPos;
	eyePosRight.m128_f32[0] += 88;
	eyePosRight.m128_f32[1] += 24;
	m_pEyeLeft->m_Transform.SetPosition(eyePosLeft);
	m_pEyeRight->m_Transform.SetPosition(eyePosRight);
	
	float time = twTime->GetTimeSinceStartup();
	m_pSnakeFeatherMaterial->m_ConstantBuffer.SetValueInBuffer(5, &time);
	m_pEyeLeftMaterial->m_ConstantBuffer.SetValueInBuffer(4, &time);
	m_pEyeRightMaterial->m_ConstantBuffer.SetValueInBuffer(4, &time);

	DirectX::XMVECTOR leftPos = m_pBGBassLeft->m_Transform.GetPosition();
	leftPos.m128_f32[1] = (std::sin(twTime->GetTimeSinceStartup() * 0.7f)) * 20;
	leftPos.m128_f32[1] += 250.0f;
	m_pBGBassLeft->m_Transform.SetPosition(leftPos);

	DirectX::XMVECTOR rightPos = m_pBGBassRight->m_Transform.GetPosition();
	rightPos.m128_f32[1] = (std::sin(twTime->GetTimeSinceStartup() * 0.7f )) * 20;
	rightPos.m128_f32[1] += 250.0f;
	m_pBGBassRight->m_Transform.SetPosition(rightPos);
}

void CBackground::End()
{
}

void CBackground::ResetBackground()
{
	//Multiplier
	float circlePower1 = 1;
	float circlePower2 = 0;
	float circlePower3 = 0;
	float circlePower4 = 0;
	float circlePower5 = 0;

	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(10, &circlePower1);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(11, &circlePower2);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(12, &circlePower3);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(13, &circlePower4);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(14, &circlePower5);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(10, &circlePower1);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(11, &circlePower2);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(12, &circlePower3);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(13, &circlePower4);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(14, &circlePower5);

	//Circles
	circlePower1 = 1.0f;
	circlePower2 = 0.0f;
	circlePower3 = 0.0f;
	circlePower4 = 0.0f;
	circlePower5 = 0.0f;

	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(5, &circlePower1);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(6, &circlePower2);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(7, &circlePower3);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(8, &circlePower4);
	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(9, &circlePower5);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(5, &circlePower1);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(6, &circlePower2);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(7, &circlePower3);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(8, &circlePower4);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(9, &circlePower5);

	//Colors
	m_LerpColors = false;
	m_LerpColorValue = 0.0f;
	m_LerpColorToValue = 0.0f;
	m_LerpToColor = DirectX::XMFLOAT4(0.0f, 0.0f, 0.f, 0.0f);

	m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);
	m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);
	m_pSnakeFeatherMaterial->m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);
	m_pSnakeHeadMaterial->m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);

}

void CBackground::CreateSnakeHead()
{
	// Snake Head
	const float snakeWidth = 650.0f;
	const float snakeApectRatio = 1.0f;

	//Rotation Feathers

	m_pSnakeFeather = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pSnakeFeather->m_Transform);
	m_pSnakeFeather->m_Transform.SetPosition(0.0f, 170.0f, 480.0f);
	m_pSnakeFeather->m_Transform.SetScale(snakeWidth, 0.0f, snakeWidth * snakeApectRatio);
	m_pSnakeFeather->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

	auto snakeFeatherMesh = twRenderer->CreateMeshDrawable();
	snakeFeatherMesh->m_RenderMode= triebWerk::CMeshDrawable::ERenderMode::Transparent;
	snakeFeatherMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	snakeFeatherMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	snakeFeatherMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Background1TextureCutOut"));
	snakeFeatherMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);
	snakeFeatherMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_snake_emissive_wreath"));
	snakeFeatherMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_snake_emissive_alpha"));
	m_pSnakeFeatherMaterial = &snakeFeatherMesh->m_Material;
	m_pSnakeFeather->SetDrawable(snakeFeatherMesh);

	twActiveWorld->AddEntity(m_pSnakeFeather);

	//Head

	m_pBGSnake = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pBGSnake->m_Transform);
	m_pBGSnake->m_Transform.SetPosition(0.0f, 170.0f, 479.0f);
	m_pBGSnake->m_Transform.SetScale(snakeWidth, 0.0f, snakeWidth * snakeApectRatio);
	m_pBGSnake->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

	auto snakeMesh = twRenderer->CreateMeshDrawable();
	snakeMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	snakeMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	snakeMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	snakeMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Background1Texture"));
	snakeMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);
	snakeMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_snake_emissive"));
	m_pSnakeHeadMaterial = &snakeMesh->m_Material;
	m_pBGSnake->SetDrawable(snakeMesh);

	twActiveWorld->AddEntity(m_pBGSnake);
}

void CBackground::CreateWings()
{
	// Bass Left
	const float bassWidth = 350.0f;
	const float bassApectRatio = 1.0f;

	m_pBGBassLeft = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pBGBassLeft->m_Transform);
	m_pBGBassLeft->m_Transform.SetPosition(-520.0f, 350.0f, 475.0f);
	m_pBGBassLeft->m_Transform.SetScale(bassWidth, 0.0f, bassWidth * bassApectRatio);
	m_pBGBassLeft->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

	auto bassLeftMesh = twRenderer->CreateMeshDrawable();
	bassLeftMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	bassLeftMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	bassLeftMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	bassLeftMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Background5Textures"));
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);

	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_bass_emissive_01"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_bass_emissive_02"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(2, twResourceManager->GetTexture2D("t_bass_emissive_03"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(3, twResourceManager->GetTexture2D("t_bass_emissive_04"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(4, twResourceManager->GetTexture2D("t_bass_emissive_05"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(5, twResourceManager->GetTexture2D("t_bass_emissive_m_01"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(6, twResourceManager->GetTexture2D("t_bass_emissive_m_02"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(7, twResourceManager->GetTexture2D("t_bass_emissive_m_03"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(8, twResourceManager->GetTexture2D("t_bass_emissive_m_04"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(9, twResourceManager->GetTexture2D("t_bass_emissive_m_05"));

	float circlePower1 = 1.0f;
	float circlePower2 = 0.0f;
	float circlePower3 = 0.0f;
	float circlePower4 = 0.0f;
	float circlePower5 = 0.0f;

	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &circlePower1);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &circlePower2);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &circlePower3);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &circlePower4);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &circlePower5);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &circlePower5);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(11, &circlePower5);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(12, &circlePower5);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(13, &circlePower5);
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(14, &circlePower5);

	m_pBGBassLeft->SetDrawable(bassLeftMesh);

	m_pLeftMaterial = &bassLeftMesh->m_Material;

	twActiveWorld->AddEntity(m_pBGBassLeft);

	// Bass Right

	m_pBGBassRight = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pBGBassRight->m_Transform);
	m_pBGBassRight->m_Transform.SetPosition(520.0f, 350.0f, 475.0f);
	m_pBGBassRight->m_Transform.SetScale(bassWidth, 0.0f, bassWidth * bassApectRatio);
	m_pBGBassRight->m_Transform.SetRotationDegrees(270.0f, 180.0f, 0.0f);

	auto bassRightMesh = twRenderer->CreateMeshDrawable();
	bassRightMesh->m_D3DStates.m_pRasterizerState = twGraphic->GetDefaultCullNoneRasterizerState();
	bassRightMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	bassRightMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	bassRightMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	bassRightMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Background5Textures"));
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_StartColor);
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_bass_emissive_01"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_bass_emissive_02"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(2, twResourceManager->GetTexture2D("t_bass_emissive_03"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(3, twResourceManager->GetTexture2D("t_bass_emissive_04"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(4, twResourceManager->GetTexture2D("t_bass_emissive_05"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(5, twResourceManager->GetTexture2D("t_bass_emissive_m_01"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(6, twResourceManager->GetTexture2D("t_bass_emissive_m_02"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(7, twResourceManager->GetTexture2D("t_bass_emissive_m_03"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(8, twResourceManager->GetTexture2D("t_bass_emissive_m_04"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(9, twResourceManager->GetTexture2D("t_bass_emissive_m_05"));

	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &circlePower1);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(6, &circlePower2);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(7, &circlePower3);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(8, &circlePower4);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(9, &circlePower5);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(10, &circlePower5);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(11, &circlePower5);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(12, &circlePower5);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(13, &circlePower5);
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(14, &circlePower5);

	m_pBGBassRight->SetDrawable(bassRightMesh);

	m_pRightMaterial = &bassRightMesh->m_Material;

	twActiveWorld->AddEntity(m_pBGBassRight);
}

void CBackground::CreateEyes()
{
	m_pEyeLeft = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pEyeLeft->m_Transform);
	// Transform
	m_pEyeLeft->m_Transform.SetPosition(-70.0f, 150.0f, 475.0f);
	m_pEyeLeft->m_Transform.SetScale(5.0f, 5.0f, 5.0f);

	// Rendering
	auto eyeLeftMesh = twRenderer->CreateMeshDrawable();
	eyeLeftMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	eyeLeftMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	eyeLeftMesh->m_pMesh = twResourceManager->GetMesh("ms_sphere");
	eyeLeftMesh->m_Material.SetMaterial(twResourceManager->GetMaterial("Eyes"));
	eyeLeftMesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("t_whitenoise"));
	eyeLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &m_StartColor);
	m_pEyeLeft->SetDrawable(eyeLeftMesh);

	m_pEyeLeftMaterial = &eyeLeftMesh->m_Material;

	twActiveWorld->AddEntity(m_pEyeLeft);

	m_pEyeRight = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pEyeRight->m_Transform);
	
	// Transform
	m_pEyeRight->m_Transform.SetPosition(70.0f, 150.0f, 475.0f);
	m_pEyeRight->m_Transform.SetScale(5.0f, 5.0f, 5.0f);

	// Rendering
	auto eyeRightMesh = twRenderer->CreateMeshDrawable();
	eyeRightMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	eyeRightMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	eyeRightMesh->m_pMesh = twResourceManager->GetMesh("ms_sphere");
	eyeRightMesh->m_Material.SetMaterial(twResourceManager->GetMaterial("Eyes"));
	eyeRightMesh->m_Material.m_pVertexShader.SetTexture(0, twResourceManager->GetTexture2D("t_whitenoise"));
	eyeRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &m_StartColor);
	m_pEyeRight->SetDrawable(eyeRightMesh);

	m_pEyeRightMaterial = &eyeRightMesh->m_Material;

	twActiveWorld->AddEntity(m_pEyeRight);
}

void CBackground::UpdateMultiplier()
{
	if (m_Multiplier != CGameInfo::Instance().m_Multiplier)
	{
		m_Multiplier = CGameInfo::Instance().m_Multiplier;

		if (m_Multiplier == 1)
		{
			float circlePower1 = 1;
			float circlePower2 = 0;
			float circlePower3 = 0;
			float circlePower4 = 0;
			float circlePower5 = 0;

			m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(10, &circlePower1);
			m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(11, &circlePower2);
			m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(12, &circlePower3);
			m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(13, &circlePower4);
			m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(14, &circlePower5);
			m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(10, &circlePower1);
			m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(11, &circlePower2);
			m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(12, &circlePower3);
			m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(13, &circlePower4);
			m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(14, &circlePower5);
		}

		m_ToMultiLerpIndex = (int)m_Multiplier + 9;
		std::cout << m_ToMultiLerpIndex << std::endl;
		m_IsMultiLerping = true;
	}

	if (m_IsMultiLerping)
	{
		m_MultiLerpValue += twTime->GetDeltaTime();

		m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(m_ToMultiLerpIndex, &m_MultiLerpValue);
		m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(m_ToMultiLerpIndex, &m_MultiLerpValue);

		if (m_MultiLerpValue > 1.0f)
		{
			m_IsMultiLerping = false;
			m_MultiLerpValue = 0.0f;
		}
	}
}

void CBackground::UpdateDifficultyCircles()
{
	if (m_Difficulty != CGameInfo::Instance().m_Difficulty)
	{
		if (!m_IsLerping)
		{
			m_Difficulty = CGameInfo::Instance().m_Difficulty;

			UpdateColor();

			m_IsLerping = true;
			m_ToLerpIndex = 4 + m_Difficulty;
		}
	}

	if (m_IsLerping)
	{
		m_LerpValue += twTime->GetDeltaTime();
		m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(m_ToLerpIndex, &m_LerpValue);
		m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(m_ToLerpIndex, &m_LerpValue);

		if (m_LerpValue > 1.0f)
		{
			m_IsLerping = false;
			m_LerpValue = 0.0f;
		}
	}
}

void CBackground::UpdateColor()
{
	if (m_Difficulty < 4.0f)
		m_LerpToColor = ToLerpColors[0];
	else
		m_LerpToColor = ToLerpColors[1];

	m_LerpColorToValue = m_LerpColorToValue + 1.0f / 4.0f;

	m_LerpColors = true;
}

void CBackground::LerpColor()
{
	if (m_LerpColors)
	{
		if (m_LerpColorValue < m_LerpColorToValue)
		{
			m_LerpColorValue += twTime->GetDeltaTime() / 12;

			DirectX::XMFLOAT4 temp;
			temp.x = m_LerpToColor.x * m_LerpColorValue;
			temp.y = m_LerpToColor.y * m_LerpColorValue;
			temp.z = m_LerpToColor.z * m_LerpColorValue;
			temp.w = m_LerpToColor.w * m_LerpColorValue;

			m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(4, &temp);
			m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(4, &temp);
			m_pSnakeFeatherMaterial->m_ConstantBuffer.SetValueInBuffer(4, &temp);
			m_pSnakeHeadMaterial->m_ConstantBuffer.SetValueInBuffer(4, &temp);
			m_pEyeLeftMaterial->m_ConstantBuffer.SetValueInBuffer(5, &temp);
			m_pEyeRightMaterial->m_ConstantBuffer.SetValueInBuffer(5, &temp);
		}
		else
		{
			m_LerpColors = false;
		}
	}
}
