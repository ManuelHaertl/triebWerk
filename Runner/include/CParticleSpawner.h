#pragma once
#include <CEngine.h>

class CParticleSpawner : public triebWerk::IBehaviour
{
private:
	const float m_MaxNextSpawnTime = 0.6f;
	const float m_MinNextSpawnTime = 0.1f;

private:
	float m_TimeTillNextParticle;
	std::list<triebWerk::CEntity*> m_Particles;
	std::list<triebWerk::CEntity*> m_KillParticles;

public:
	CParticleSpawner();
	~CParticleSpawner();

public:
	void Start() final;
	void Update() final;
	void End() final;

private:
	void CreateParticle();
	void SetRandomTransformation(triebWerk::CTransform* a_pTransform);

};