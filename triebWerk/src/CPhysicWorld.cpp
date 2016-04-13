#include <CPhysicWorld.h>

triebWerk::CPhysicWorld::CPhysicWorld() :
    m_CurrentEntityID(0)
{
    m_GravityScale = DirectX::XMVectorSet(0.0f, -9.81f, 0.0f, 0.0f);
}

triebWerk::CPhysicWorld::~CPhysicWorld()
{
}

triebWerk::CPhysicEntity* triebWerk::CPhysicWorld::CreatePhysicEntity()
{
    CPhysicEntity* entity = new CPhysicEntity(m_CurrentEntityID, this);
    m_CurrentEntityID++;

    return entity;
}

triebWerk::CBody* triebWerk::CPhysicWorld::CreateBody()
{
    CBody* body = new CBody();
    return body;
}

triebWerk::CAABBCollider* triebWerk::CPhysicWorld::CreateAABBCollider()
{
    CAABBCollider* aabbCollider = new CAABBCollider();
    return aabbCollider;
}

void triebWerk::CPhysicWorld::AddPhysicEntity(CPhysicEntity* a_pPhysicEntity)
{
    // add the entity and all sub categories in it's specific vector

    m_Entities.push_back(a_pPhysicEntity);
    a_pPhysicEntity->SetInPhysicWorldState(true);

    AddBody(a_pPhysicEntity->GetBody());

    for (ICollider* pCollider : a_pPhysicEntity->m_Collider)
    {
        AddCollider(pCollider);
    }
}

void triebWerk::CPhysicWorld::AddBody(CBody* a_pBody)
{
    if (a_pBody != nullptr)
        m_Bodies.push_back(a_pBody);
}

void triebWerk::CPhysicWorld::AddCollider(ICollider* a_pCollider)
{
    if (a_pCollider->m_CheckCollision == false)
        m_StaticCollider.push_back(a_pCollider);
    else
        m_DynamicCollider.push_back(a_pCollider);
}

void triebWerk::CPhysicWorld::RemovePhysicEntity(CPhysicEntity* a_pPhysicEntity)
{
    // remove and delete collider
    for (size_t i = 0; i < a_pPhysicEntity->m_Collider.size(); ++i)
    {
        RemoveCollider(a_pPhysicEntity->m_Collider[i]);
    }

    // remove and delete body
    RemoveBody(a_pPhysicEntity->GetBody());

    // remove and delete entities
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        if (m_Entities[i] == a_pPhysicEntity)
        {
            m_Entities.erase(m_Entities.begin() + i);
            delete a_pPhysicEntity;
            break;
        }
    }
}

void triebWerk::CPhysicWorld::RemoveBody(CBody* a_pBody)
{
    // remove and delete body
    if (a_pBody != nullptr)
    {
        for (size_t i = 0; i < m_Bodies.size(); ++i)
        {
            if (m_Bodies[i] == a_pBody)
            {
                m_Bodies.erase(m_Bodies.begin() + i);
                delete a_pBody;
                return;
            }
        }
    }
}

void triebWerk::CPhysicWorld::RemoveCollider(ICollider* a_pCollider)
{
    if (a_pCollider->m_CheckCollision == false)
    {
        for (size_t j = 0; j < m_StaticCollider.size(); ++j)
        {
            if (a_pCollider == m_StaticCollider[j])
            {
                m_StaticCollider.erase(m_StaticCollider.begin() + j);
                delete a_pCollider;
                return;
            }
        }
    }
    else
    {
        for (size_t j = 0; j < m_DynamicCollider.size(); ++j)
        {
            if (a_pCollider == m_DynamicCollider[j])
            {
                m_DynamicCollider.erase(m_DynamicCollider.begin() + j);
                delete a_pCollider;
                return;
            }
        }
    }
}

void triebWerk::CPhysicWorld::Update(const float a_DeltaTime)
{
    DirectX::XMVECTOR deltaGravity = DirectX::XMVectorScale(m_GravityScale, a_DeltaTime);

    for (CBody* pBody : m_Bodies)
    {        
        // apply gravity
        DirectX::XMVECTOR gravity = DirectX::XMVectorScale(deltaGravity, pBody->m_GravityFactor);
        pBody->ApplyImpulse(gravity);

        // apply velocity
        DirectX::XMVECTOR deltaVelocity = DirectX::XMVectorScale(pBody->m_Velocity, a_DeltaTime);
        DirectX::XMVECTOR newPosition = DirectX::XMVectorAdd(pBody->m_pTransform->GetPosition(), deltaVelocity);
        pBody->m_pTransform->SetPosition(newPosition);
    }

    CCollision collision;

    for (size_t i = 0; i < m_DynamicCollider.size(); ++i)
    {
        // check for other dynamic collider
        for (size_t j = i + 1; j < m_DynamicCollider.size(); ++j)
            collision.CheckCollision(m_DynamicCollider[i], m_DynamicCollider[j]);

        // and for all static ones
        for (size_t j = 0; j < m_StaticCollider.size(); ++j)
            collision.CheckCollision(m_DynamicCollider[i], m_StaticCollider[j]);
    }

    collision.SolveAllCollisions();
}
