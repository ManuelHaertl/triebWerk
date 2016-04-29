#include <CWorld.h>

triebWerk::CWorld::CWorld() :
    m_pPhysicWorld(nullptr),
    m_CurrentSize(Start_Reserve_Size),
    m_EntitiesToDraw(0),
    m_EntitiesToRemove(0),
    m_pRenderingHandle(nullptr)
{
}

triebWerk::CWorld::~CWorld()
{
}

bool triebWerk::CWorld::Initialize(CRenderer* a_pRenderer)
{
    m_pPhysicWorld = new CPhysicWorld();

    // reserve some spots so the vector doesn't need
    // to get resized too often during runtime
    m_Entities.reserve(Start_Reserve_Size);
    m_DrawEntities.resize(Start_Reserve_Size);
    m_RemoveEntities.resize(Start_Reserve_Size);

	m_pRenderingHandle = a_pRenderer;

    return true;
}

bool triebWerk::CWorld::Update(const float a_DeltaTime)
{
    // check what behaviour the entity has
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        CEntity* pEntity = m_Entities[i];

        if (pEntity->GetBehaviour() != nullptr)
        {
            // Update Order #1: Update the Game Script
            pEntity->GetBehaviour()->Update();
        }

        if (pEntity->GetDrawable() != nullptr)
        {
            m_DrawEntities[m_EntitiesToDraw] = pEntity;
            m_EntitiesToDraw++;
        }
    }

    // Update Order #2: Update the Phyisc
    m_pPhysicWorld->Update(a_DeltaTime);

    // Update Order #3: Collect all Entities that shall be rendered
    for (size_t i = 0; i < m_EntitiesToDraw; ++i)
    {
        m_pRenderingHandle->AddRenderCommand(m_DrawEntities[i]->GetDrawable()->GetRenderCommand(m_DrawEntities[i]));
    }

    // Update Order #4: Draw all Entities
    m_pRenderingHandle->DrawScene();

    // Update Order #5: Delete all entities what have been removed this frame
    DeleteRemoveEntities();

    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        m_Entities[i]->m_Transform.SetModifiedStateFalse();
    }

    m_EntitiesToDraw = 0;
    return true;
}

void triebWerk::CWorld::Shutdown()
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        DeleteEntity(m_Entities[i]);
    }

    if (m_pPhysicWorld != nullptr)
        delete m_pPhysicWorld;
}

triebWerk::CEntity* triebWerk::CWorld::CreateEntity() const
{
    CEntity* entity = new CEntity();
    return entity;
}

void triebWerk::CWorld::AddEntity(CEntity* a_pEntity)
{
    // resize if the vector doesn't have any more reserved spots
    if (m_Entities.size() >= m_CurrentSize)
    {
        m_CurrentSize *= 2;
        m_Entities.reserve(m_CurrentSize);
        m_DrawEntities.resize(m_CurrentSize);
        m_RemoveEntities.resize(m_CurrentSize);
    }

    // and add it to the vector
    m_Entities.push_back(a_pEntity);

    // check for Physic Entity
    if (a_pEntity->GetPhysicEntity() != nullptr)
    {
        m_pPhysicWorld->AddPhysicEntity(a_pEntity->GetPhysicEntity());
    }

    // now set the world state true because every needed subsystem has been added
    a_pEntity->SetInWorldState(true);

    if (a_pEntity->GetBehaviour() != nullptr)
    {
        // call the behaviour start function at the end because behaviour
        // functions only may be called while the entity is in the world
        a_pEntity->GetBehaviour()->Start();
    }
}

void triebWerk::CWorld::RemoveEntity(CEntity* a_pEntity)
{
    m_RemoveEntities[m_EntitiesToRemove] = a_pEntity;
    m_EntitiesToRemove++;
}

void triebWerk::CWorld::ClearEntities()
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        m_RemoveEntities[m_EntitiesToRemove] = m_Entities[i];
        m_EntitiesToRemove++;
    }
}

triebWerk::CEntity* triebWerk::CWorld::GetEntity(size_t a_ID) const
{
    return m_Entities[a_ID];
}

size_t triebWerk::CWorld::GetEntityCount() const
{
    return m_Entities.size();
}

void triebWerk::CWorld::DeleteRemoveEntities()
{
    // TO DO: maybe improve this a bit in case ClearEntities() gets called..
    for (size_t i = 0; i < m_EntitiesToRemove; ++i)
    {
        for (size_t j = 0; j < m_Entities.size(); ++j)
        {
            if (m_RemoveEntities[i] == m_Entities[j])
            {
                m_Entities.erase(m_Entities.begin() + j);
                DeleteEntity(m_RemoveEntities[i]);
            }
        }
    }

    m_EntitiesToRemove = 0;
}

void triebWerk::CWorld::DeleteEntity(CEntity* a_pEntity)
{
	a_pEntity->RemoveBehaviour();
	a_pEntity->RemovePhysicEntity();
	a_pEntity->RemoveDrawable();

    delete a_pEntity;
}
