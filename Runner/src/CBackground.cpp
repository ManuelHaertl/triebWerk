#include <CBackground.h>
#include <CGameInfo.h>

DirectX::XMFLOAT3 CBackground::DifficultyColors[5] = 
{
DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f),
DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f),
DirectX::XMFLOAT3(0.0f, 1.0f, 1.0f),
DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f) 
};

CBackground::CBackground() 
	: m_pBGSnake(nullptr)
	, m_pBGBassLeft(nullptr)
	, m_pBGBassRight(nullptr)
	, m_Difficulty(0)
{
}

CBackground::~CBackground()
{
}

void CBackground::Start()
{
	// Snake Head
	const float snakeWidth = 650.0f;
	const float snakeApectRatio = 1.0f;

	m_pBGSnake = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pBGSnake->m_Transform);
	m_pBGSnake->m_Transform.SetPosition(0.0f, 170.0f, 480.0f);
	m_pBGSnake->m_Transform.SetScale(snakeWidth, 0.0f, snakeWidth * snakeApectRatio);
	m_pBGSnake->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

	auto snakeMesh = twRenderer->CreateMeshDrawable();
	snakeMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	snakeMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	snakeMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Background1Texture"));
	snakeMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	snakeMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_snake_emissive"));
	m_pBGSnake->SetDrawable(snakeMesh);

	twActiveWorld->AddEntity(m_pBGSnake);

	// Bass Left
	const float bassWidth = 350.0f;
	const float bassApectRatio = 1.0f;

	m_pBGBassLeft = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pBGBassLeft->m_Transform);
	m_pBGBassLeft->m_Transform.SetPosition(-420.0f, 230.0f, 475.0f);
	m_pBGBassLeft->m_Transform.SetScale(bassWidth, 0.0f, bassWidth * bassApectRatio);
	m_pBGBassLeft->m_Transform.SetRotationDegrees(270.0f, 0.0f, 0.0f);

	auto bassLeftMesh = twRenderer->CreateMeshDrawable();
	bassLeftMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	bassLeftMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	bassLeftMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Background5Textures"));
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	bassLeftMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_bass_emissive_01"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_bass_emissive_02"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(2, twResourceManager->GetTexture2D("t_bass_emissive_03"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(3, twResourceManager->GetTexture2D("t_bass_emissive_04"));
	bassLeftMesh->m_Material.m_pPixelShader.SetTexture(4, twResourceManager->GetTexture2D("t_bass_emissive_05"));
	m_pBGBassLeft->SetDrawable(bassLeftMesh);

	m_pLeftMaterial = &bassLeftMesh->m_Material;

	twActiveWorld->AddEntity(m_pBGBassLeft);

	// Bass Right

	m_pBGBassRight = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pBGBassRight->m_Transform);
	m_pBGBassRight->m_Transform.SetPosition(420.0f, 230.0f, 475.0f);
	m_pBGBassRight->m_Transform.SetScale(bassWidth, 0.0f, bassWidth * bassApectRatio);
	m_pBGBassRight->m_Transform.SetRotationDegrees(270.0f, 180.0f, 0.0f);

	auto bassRightMesh = twRenderer->CreateMeshDrawable();
	bassRightMesh->m_D3DStates.m_pRasterizerState = twGraphic->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
	bassRightMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
	bassRightMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	bassRightMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("Background5Textures"));
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	bassRightMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("t_bass_emissive_01"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("t_bass_emissive_02"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(2, twResourceManager->GetTexture2D("t_bass_emissive_03"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(3, twResourceManager->GetTexture2D("t_bass_emissive_04"));
	bassRightMesh->m_Material.m_pPixelShader.SetTexture(4, twResourceManager->GetTexture2D("t_bass_emissive_05"));
	m_pBGBassRight->SetDrawable(bassRightMesh);

	m_pRightMaterial = &bassRightMesh->m_Material;

	twActiveWorld->AddEntity(m_pBGBassRight);
}

void CBackground::Update()
{
	if (m_Difficulty != CGameInfo::Instance().m_Difficulty)
	{
		m_Difficulty = CGameInfo::Instance().m_Difficulty;
		
		m_pLeftMaterial->m_ConstantBuffer.SetValueInBuffer(5, &DifficultyColors[m_Difficulty-1]);
		m_pRightMaterial->m_ConstantBuffer.SetValueInBuffer(5, &DifficultyColors[m_Difficulty-1]);
	}

}

void CBackground::End()
{
}
