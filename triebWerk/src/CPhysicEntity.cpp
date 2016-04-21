#include <CPhysicEntity.h>

#include <CPhysicWorld.h>
#include <CEntity.h>

triebWerk::CPhysicEntity::CPhysicEntity(size_t a_EntityID, CPhysicWorld* a_pPhysicWorld) :
    //m_pTransform(nullptr),
    m_pPhysicWorld(a_pPhysicWorld),
    m_pBody(nullptr),
    m_IsInPhysicWorld(false),
    m_ID(a_EntityID)
{
    
}

triebWerk::CPhysicEntity::~CPhysicEntity()
{
}

size_t triebWerk::CPhysicEntity::GetID() const
{
    return m_ID;
}

triebWerk::CPhysicWorld* triebWerk::CPhysicEntity::GetPhysicWorld() const
{
    return m_pPhysicWorld;
}

triebWerk::CBody* triebWerk::CPhysicEntity::GetBody() const
{
    return m_pBody;
}

std::vector<triebWerk::ICollider*>* triebWerk::CPhysicEntity::GetCollider() const
{
    return nullptr;
}

void triebWerk::CPhysicEntity::SetBody(CBody* a_pBody)
{
    RemoveBody();
    m_pBody = a_pBody;
   // m_pBody->m_pTransform = m_pTransform;
    m_pBody->m_pTransform = &m_pEntity->m_Transform;

    if (m_IsInPhysicWorld)
        m_pPhysicWorld->AddBody(a_pBody);

    // give all collider the new body
    for (ICollider* pCollider : m_Collider)
        pCollider->m_pEntity = m_pEntity;
        //pCollider->m_pBody = m_pBody;
}

void triebWerk::CPhysicEntity::AddCollider(ICollider* a_pCollider)
{
    m_Collider.push_back(a_pCollider);

    if (m_IsInPhysicWorld)
        m_pPhysicWorld->AddCollider(a_pCollider);

    a_pCollider->m_pEntity = m_pEntity;
}

void triebWerk::CPhysicEntity::RemoveBody()
{
    if (m_pBody != nullptr)
    {
        if (m_IsInPhysicWorld) // let the physic world delete the body
            m_pPhysicWorld->RemoveBody(m_pBody);

        else // delete manually
            delete m_pBody;

        m_pBody = nullptr;
    }
}

void triebWerk::CPhysicEntity::RemoveCollider(ICollider* a_pCollider)
{
    for (size_t i = 0; i < m_Collider.size(); ++i)
    {
        if (m_Collider[i] == a_pCollider)
        {
            if (m_IsInPhysicWorld) // let the physic world delete the collider
                m_pPhysicWorld->RemoveCollider(a_pCollider);

            else // delete it manually
                delete a_pCollider;

            m_Collider.erase(m_Collider.begin() + i);
            return;
        }
    }
}

void triebWerk::CPhysicEntity::RemoveAllCollider()
{
    for (size_t i = 0; i < m_Collider.size(); ++i)
    {
        if (m_IsInPhysicWorld) // let the physic world delete the collider
            m_pPhysicWorld->RemoveCollider(m_Collider[i]);

        else // delete it manually
        {
            delete m_Collider[i];
        }
    }

    m_Collider.clear();
}

bool triebWerk::CPhysicEntity::IsInPhysicWorld() const
{
    return m_IsInPhysicWorld;
}

void triebWerk::CPhysicEntity::SetInPhysicWorldState(const bool a_State)
{
    m_IsInPhysicWorld = a_State;
}
