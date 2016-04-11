#include <CPhysicWorld.h>

triebWerk::CPhysicWorld::CPhysicWorld() :
    m_GravityScale(9.81f),
    m_CurrentEntityID(0)
{
}

triebWerk::CPhysicWorld::~CPhysicWorld()
{
}

triebWerk::CPhysicEntity* triebWerk::CPhysicWorld::CreatePhysicEntity()
{
    CPhysicEntity* entity = new CPhysicEntity(m_CurrentEntityID);
    m_CurrentEntityID++;

    return entity;
}

triebWerk::CBody* triebWerk::CPhysicWorld::CreateBody()
{
    CBody* body = new CBody();
    return body;
}

triebWerk::CAABB* triebWerk::CPhysicWorld::CreateAABB()
{
    CAABB* aabb = new CAABB();
    return aabb;
}

void triebWerk::CPhysicWorld::AddPhysicEntity(CPhysicEntity* a_pPhysicEntity)
{
    // add the entity and all sub categories in it's specific vector

    m_Entities.push_back(a_pPhysicEntity);

    if (a_pPhysicEntity->m_pBody != nullptr)
        m_Bodies.push_back(a_pPhysicEntity->m_pBody);

    for (CCollider* pCollider : a_pPhysicEntity->m_Collider)
    {
        if (pCollider->m_CheckCollision == false)
            m_StaticCollider.push_back(pCollider);
        else
            m_DynamicCollider.push_back(pCollider);
    }
}

void triebWerk::CPhysicWorld::RemovePhysicEntity(CPhysicEntity* a_pPhysicEntity)
{
    // remove and delete collider
    for (size_t i = 0; i < a_pPhysicEntity->m_Collider.size(); ++i)
    {
        if (a_pPhysicEntity->m_Collider[i]->m_CheckCollision == false)
        {
            CCollider* coll = a_pPhysicEntity->m_Collider[i];
            for (size_t j = 0; j < m_StaticCollider.size(); ++j)
            {
                if (coll == m_StaticCollider[j])
                {
                    m_StaticCollider.erase(m_StaticCollider.begin() + j);
                    delete coll;
                }
            }
        }
        else
        {
            CCollider* coll = a_pPhysicEntity->m_Collider[i];
            for (size_t j = 0; j < m_DynamicCollider.size(); ++j)
            {
                if (coll == m_DynamicCollider[j])
                {
                    m_DynamicCollider.erase(m_DynamicCollider.begin() + j);
                    delete coll;
                }
            }
        }
    }

    // remove and delete body
    if (a_pPhysicEntity->m_pBody != nullptr)
    {
        for (size_t i = 0; i < m_Bodies.size(); ++i)
        {
            if (m_Bodies[i] == a_pPhysicEntity->m_pBody)
            {
                m_Bodies.erase(m_Bodies.begin() + i);
                delete a_pPhysicEntity->m_pBody;
            }
        }
    }

    // remove and delete entities
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        if (m_Entities[i] == a_pPhysicEntity)
        {
            m_Entities.erase(m_Entities.begin() + i);
            delete a_pPhysicEntity;
        }
    }
}

void triebWerk::CPhysicWorld::Update(const float a_DeltaTime)
{
    // TO DO:
    
    // (only applies to entities which have a body)
    // 1. Bodies: add gravity force
    // 2. Bodies: apply all forces to the velocity (gravity + forces from the game)
    // 3. Bodies: apply velocity to the position

    // 4. Update Quadtree

    // (only applies to entities which have a collider)
    // 5. check collision from all dynamic collider and gather collision info
    //      (if collision happened)
    //      6. (if trigger event) send a collision event
    //      7. (if body exists) solve the collision with the collision info
}
