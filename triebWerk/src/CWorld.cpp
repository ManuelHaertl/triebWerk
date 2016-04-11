#include <CWorld.h>

triebWerk::CWorld::CWorld() :
    m_pPhysicWorld(nullptr),
    m_CurrentSize(Start_Reserve_Size)
{
}

triebWerk::CWorld::~CWorld()
{
}

bool triebWerk::CWorld::Initialize()
{
    m_pPhysicWorld = new CPhysicWorld();

    // reserve some spots so the vector doesn't need
    // to get resized too often during runtime
    m_Entities.reserve(Start_Reserve_Size);
    return true;
}

bool triebWerk::CWorld::Update(const float a_DeltaTime)
{
    // check what behaviour the entity has
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        if (m_Entities[i]->m_pBehaviour != nullptr)
        {
            m_Entities[i]->m_pBehaviour->Update();
        }
    }

    m_pPhysicWorld->Update(a_DeltaTime);
    return true;
}

void triebWerk::CWorld::Shutdown()
{
    ClearEntities();

    if (m_pPhysicWorld != nullptr)
        delete m_pPhysicWorld;
}

triebWerk::CEntity* triebWerk::CWorld::CreateEntity() const
{
    CEntity* entity = new CEntity();
    return entity;
}

void triebWerk::CWorld::AddEntity(CEntity * a_pEntity)
{
    // resize if the vector doesn't have any more reserved spots
    if (m_Entities.size() >= m_CurrentSize)
    {
        m_CurrentSize *= 2;
        m_Entities.reserve(m_CurrentSize);
    }

    if (a_pEntity->m_pBehaviour != nullptr)
    {
        a_pEntity->m_pBehaviour->Start();
    }

    // check for Physic Entity
    if (a_pEntity->m_pPhysicEntity != nullptr)
    {
        m_pPhysicWorld->AddPhysicEntity(a_pEntity->m_pPhysicEntity);
    }
    m_Entities.push_back(a_pEntity);
}

void triebWerk::CWorld::RemoveEntity(CEntity* a_pEntity)
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        if (m_Entities[i] == a_pEntity)
        {
            DeleteEntity(a_pEntity);
            m_Entities.erase(m_Entities.begin() + i);
            break;
        }
    }
}

void triebWerk::CWorld::ClearEntities()
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        DeleteEntity(m_Entities[i]);
    }

    m_Entities.clear();
}

void triebWerk::CWorld::DeleteEntity(CEntity * a_pEntity)
{
    if (a_pEntity->m_pBehaviour != nullptr)
    {
        a_pEntity->m_pBehaviour->End();
        delete a_pEntity->m_pBehaviour;
    }

    if (a_pEntity->m_pPhysicEntity != nullptr)
    {
        m_pPhysicWorld->RemovePhysicEntity(a_pEntity->m_pPhysicEntity);
    }

    delete a_pEntity;
}
