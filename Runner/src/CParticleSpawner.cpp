#include <CParticleSpawner.h>
#include <CGameInfo.h>

CParticleSpawner::CParticleSpawner()
{
}

CParticleSpawner::~CParticleSpawner()
{
}

void CParticleSpawner::Start()
{
	m_TimeTillNextParticle = twRandom::GetNumber(m_MinNextSpawnTime, m_MaxNextSpawnTime);
}

void CParticleSpawner::Update()
{
	if (m_TimeTillNextParticle < 0)
	{
		m_TimeTillNextParticle = twRandom::GetNumber(m_MinNextSpawnTime, m_MaxNextSpawnTime);
		for (size_t i = 0; i < 5; i++)
		{
			CreateParticle();
		}
	}
	else
	{
		m_TimeTillNextParticle -= twTime->GetDeltaTime();
	}

	DirectX::XMVECTOR tempPos;

	for (auto entity : m_Particles)
	{
		tempPos = entity->m_Transform.GetPosition();
		tempPos.m128_f32[2] -= 50 * twTime->GetDeltaTime();
		entity->m_Transform.SetPosition(tempPos);
		entity->m_Transform.RotateDegrees(0.0f, 0.0f, 90.f * twTime->GetDeltaTime());

		float z = entity->m_Transform.GetPosition().m128_f32[2];
		float playerZ = CGameInfo::Instance().m_PlayerPositionZ;

		if (z < playerZ)
		{
			m_KillParticles.push_front(entity);
		}
	}

	for (auto entity : m_KillParticles)
	{
		m_Particles.remove(entity);
		twActiveWorld->RemoveEntity(entity);
	}

	m_KillParticles.clear();
}

void CParticleSpawner::End()
{
}

void CParticleSpawner::CreateParticle()
{
	auto pParticle = twActiveWorld->CreateEntity();
	pParticle->m_Transform.SetPosition(m_pEntity->m_Transform.GetPosition());
	
	SetRandomTransformation(&pParticle->m_Transform);

	auto particleMesh = twRenderer->CreateMeshDrawable();
	particleMesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::Draw;
	particleMesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_triangle");
	particleMesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("StandardColor"));
	particleMesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &DirectX::XMFLOAT3(1, 1, 1));
	particleMesh->m_D3DStates.m_pRasterizerState = twGraphic->GetDefaultCullNoneRasterizerState();

	pParticle->SetDrawable(particleMesh);

	twActiveWorld->AddEntity(pParticle);

	m_Particles.push_front(pParticle);
}

void CParticleSpawner::SetRandomTransformation(triebWerk::CTransform * a_pTransform)
{
	DirectX::XMVECTOR pos = a_pTransform->GetPosition();
	pos.m128_f32[0] = twRandom::GetNumber(-150.0f, 150.0f);
	pos.m128_f32[1] = pos.m128_f32[1] + twRandom::GetNumber(0.0f, 90.0f);
	a_pTransform->SetPosition(pos);
	a_pTransform->SetRotationDegrees(-90.0f, 00.0f, 00.0f);
	a_pTransform->SetScale(twRandom::GetNumber(0.5f, 2.0f), twRandom::GetNumber(0.5f, 2.0f), twRandom::GetNumber(0.5f, 2.0f));
}
