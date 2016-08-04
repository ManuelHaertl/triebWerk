#include <CRoadBorder.h>
#include <CGameInfo.h>

CRoadBorder::CRoadBorder()
{
}

CRoadBorder::~CRoadBorder()
{
}

void CRoadBorder::Start()
{
	m_pRightBorder = twActiveWorld->CreateEntity();
	m_pEntity->m_Transform.AddChild(&m_pRightBorder->m_Transform);
	m_pRightBorder->m_Transform.SetPosition(24.9f, 5.0f, 0.0f);
	m_pRightBorder->m_Transform.SetRotationDegrees(90.0f, 00.0f, 90.0f);
	m_pRightBorder->m_Transform.SetScale(10.0f, 10.0f, 10.0f);


	auto borderMesh = twRenderer->CreateMeshDrawable();
	borderMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	borderMesh->m_RenderMode = triebWerk::CMeshDrawable::ERenderMode::Transparent;
	borderMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_plane");
	borderMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("TransparentScrolling"));
	borderMesh->m_Material.m_pPixelShader.SetTexture(0, twResourceManager->GetTexture2D("T_border_emissve_grid"));
	borderMesh->m_Material.m_pPixelShader.SetTexture(1, twResourceManager->GetTexture2D("T_grid_cutout_circle"));
	borderMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &m_Color);
	borderMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &DirectX::XMFLOAT2(1.0f, 0.0f));
	m_pMaterialRight = &borderMesh->m_Material;
	m_pRightBorder->SetDrawable(borderMesh);

	twActiveWorld->AddEntity(m_pRightBorder);


	m_pMaterialLeft = &reinterpret_cast<triebWerk::CMeshDrawable*>(m_pEntity->GetDrawable())->m_Material;

}

void CRoadBorder::Update()
{
	float distanceLeft = m_pEntity->m_Transform.GetPosition().m128_f32[0] - CGameInfo::Instance().m_PlayerPositionX;

	if (distanceLeft > m_DistanceToShow * -1)
	{
		m_Color.w = 1 + (distanceLeft / m_DistanceToShow);
		m_pMaterialLeft->m_ConstantBuffer.SetValueInBuffer(4, &m_Color);
	}
	else
	{
		m_Color.w = 0.0f;
		m_pMaterialLeft->m_ConstantBuffer.SetValueInBuffer(4, &m_Color);
	}

	float distanceRight = m_pRightBorder->m_Transform.GetPosition().m128_f32[0] - CGameInfo::Instance().m_PlayerPositionX;

	if (distanceRight < m_DistanceToShow)
	{
		m_Color.w = 1 - (distanceRight / m_DistanceToShow);
		m_pMaterialRight->m_ConstantBuffer.SetValueInBuffer(4, &m_Color);
	}
	else
	{
		m_Color.w = 0.0f;
		m_pMaterialRight->m_ConstantBuffer.SetValueInBuffer(4, &m_Color);
	}

	float time = twTime->GetTimeSinceStartup();
	m_pMaterialRight->m_ConstantBuffer.SetValueInBuffer(6, &time);
	m_pMaterialLeft->m_ConstantBuffer.SetValueInBuffer(6, &time);
}

void CRoadBorder::End()
{
}
