#include <CEntity.h>

triebWerk::CEntity::CEntity() :
    m_pBehaviour(nullptr),
    m_pPhysicEntity(nullptr),
    m_IsInWorld(false)
{
}

triebWerk::CEntity::~CEntity()
{
}

triebWerk::CPhysicEntity* triebWerk::CEntity::GetPhysicEntity() const
{
    return m_pPhysicEntity;
}

triebWerk::IBehaviour* triebWerk::CEntity::GetBehaviour() const
{
    return m_pBehaviour;
}

triebWerk::IDrawable* triebWerk::CEntity::GetDrawable() const
{
	return m_pDrawable;
}

void triebWerk::CEntity::SetPhysicEntity(CPhysicEntity* a_pPhysicEntity)
{
    // delete the old physic entity in case it gets overwritten
    RemovePhysicEntity();

    m_pPhysicEntity = a_pPhysicEntity;
    m_pPhysicEntity->m_pTransform = &m_Transform;

    if (m_IsInWorld)
        m_pPhysicEntity->GetPhysicWorld()->AddPhysicEntity(m_pPhysicEntity);
}

void triebWerk::CEntity::SetBehaviour(IBehaviour* a_pBehaviour)
{
    // delete the old behaviour in case it gets overwritten
    RemoveBehaviour();

    m_pBehaviour = a_pBehaviour;

    if (m_IsInWorld)
        m_pBehaviour->Start();
}

void triebWerk::CEntity::SetDrawable(IDrawable * a_pDrawable)
{
	RemoveDrawable();
	m_pDrawable = a_pDrawable;
}

void triebWerk::CEntity::RemovePhysicEntity()
{
    // check if there exists a physic entity
    if (m_pPhysicEntity != nullptr)
    {
        if (m_IsInWorld) // let the physic world delete the physic entity
        {
            m_pPhysicEntity->GetPhysicWorld()->RemovePhysicEntity(m_pPhysicEntity);
        }
        else // delete manually because the entity isn't in the physic world list
        {
            m_pPhysicEntity->RemoveBody();
            m_pPhysicEntity->RemoveAllCollider();

            delete m_pPhysicEntity;
        }
        m_pPhysicEntity = nullptr;
    }
}

void triebWerk::CEntity::RemoveBehaviour()
{
    // check if there exists a behaviour
    if (m_pBehaviour != nullptr)
    {
        if (m_IsInWorld) // only call the behaviour end function if the entity is actually in the world
            m_pBehaviour->End();

        delete m_pBehaviour;
        m_pBehaviour = nullptr;
    }
}

void triebWerk::CEntity::RemoveDrawable()
{
	if (m_pDrawable != nullptr)
	{
		delete m_pDrawable;
		m_pDrawable = nullptr;
	}
}

bool triebWerk::CEntity::IsInWorld() const
{
    return m_IsInWorld;
}

void triebWerk::CEntity::SetInWorldState(const bool a_State)
{
    m_IsInWorld = a_State;
}
