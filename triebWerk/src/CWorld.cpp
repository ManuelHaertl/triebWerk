#include <CWorld.h>

triebWerk::CWorld::CWorld() :
    m_CurrentSize(Start_Reserve_Size),
    m_UpdateEntityCount(0)
{
}

triebWerk::CWorld::~CWorld()
{
}

bool triebWerk::CWorld::Initialize()
{
    // reserve some spots so the vectore doesn't need
    // to get resized too often during runtime
    m_Entities.reserve(Start_Reserve_Size);

    //m_UpdateEntities.reserve(Start_Reserve_Size);
    m_UpdateEntities.resize(Start_Reserve_Size);
    return true;
}

bool triebWerk::CWorld::Update()
{
    m_UpdateEntityCount = 0;

    // check what behaviour the entity has
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        if (m_Entities[i]->m_pBehaviour != nullptr)
        {
            m_UpdateEntities[m_UpdateEntityCount] = m_Entities[i]->m_pBehaviour;
            m_UpdateEntityCount++;
        }
    }

    // Update Entities Behaviour
    for (size_t i = 0; i < m_UpdateEntityCount; ++i)
        m_UpdateEntities[i]->Update();

    return true;
}

void triebWerk::CWorld::Shutdown()
{
    ClearEntities();
}

void triebWerk::CWorld::AddEntity(CEntity * a_pEntity)
{
    // resize if the vector doesn't have any more reserved spots
    if (m_Entities.size() >= m_CurrentSize)
    {
        m_CurrentSize *= 2;
        m_Entities.reserve(m_CurrentSize);
        m_UpdateEntities.reserve(m_CurrentSize);
    }

    if (a_pEntity->m_pBehaviour != nullptr)
    {
        a_pEntity->m_pBehaviour->Start();
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

    delete a_pEntity;
}
