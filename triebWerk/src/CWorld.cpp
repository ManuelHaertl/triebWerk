#include <CWorld.h>
#include <thread>

triebWerk::CWorld::CWorld() :
    m_pPhysicWorld(nullptr),
    m_CurrentSize(Start_Reserve_Size),
    m_pRenderingHandle(nullptr),
    m_PhysicTimeStamp(0.0f)
{
}

triebWerk::CWorld::~CWorld()
{
}

void triebWerk::CWorld::Initialize(CRenderer* a_pRenderer, const float a_PhysicTimeStamp)
{
    Shutdown();

    m_pPhysicWorld = new CPhysicWorld();

    // reserve some spots so the vector doesn't need
    // to get resized too often during runtime
    m_Entities.Resize(Start_Reserve_Size);
    m_UpdateEntities.Resize(Start_Reserve_Size);
    m_DrawEntities.Resize(Start_Reserve_Size);
    m_RemoveEntities.Resize(Start_Reserve_Size);

    m_pRenderingHandle = a_pRenderer;
    m_PhysicTimeStamp = a_PhysicTimeStamp;
}

void triebWerk::CWorld::Update(const bool a_Render, const bool a_UpdatePhysic)
{
    if (a_Render && a_UpdatePhysic)
    {
        GetEntityBehaviourAndDrawable();
        UpdateEntityBehaviour();
        UpdatePhysic();
        LateUpdateEntityBehaviour();
        RenderEntities();
        DeleteRemoveEntities();

        m_UpdateEntities.Reset();
        m_DrawEntities.Reset();
    }
    else if (a_Render)
    {
        GetEntityBehaviourAndDrawable();
        UpdateEntityBehaviour();
        LateUpdateEntityBehaviour();
        RenderEntities();
        DeleteRemoveEntities();

        m_UpdateEntities.Reset();
        m_DrawEntities.Reset();
    }
    else if (a_UpdatePhysic)
    {
        UpdatePhysic();
    }
}

void triebWerk::CWorld::Shutdown()
{
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        DeleteEntity(m_Entities[i]);
    }
    m_Entities.Clear();

    if (m_pPhysicWorld != nullptr)
    {
        delete m_pPhysicWorld;
        m_pPhysicWorld = nullptr;
    }
}

triebWerk::CEntity* triebWerk::CWorld::CreateEntity() const
{
    CEntity* entity = new CEntity();
    return entity;
}

void triebWerk::CWorld::AddEntity(CEntity* a_pEntity)
{
    // resize if the vector doesn't have any more reserved spots
    if (m_Entities.GetSize() >= m_CurrentSize)
    {
        m_CurrentSize *= 2;
        m_Entities.Resize(m_CurrentSize);
        m_UpdateEntities.Resize(m_CurrentSize);
        m_DrawEntities.Resize(m_CurrentSize);
        m_RemoveEntities.Resize(m_CurrentSize);
    }

    // and add it to the vector
    m_Entities.Add(a_pEntity);

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
    if (m_RemoveEntities.Contains(a_pEntity) == false)
        m_RemoveEntities.Add(a_pEntity);
}

void triebWerk::CWorld::ClearEntities()
{
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        m_RemoveEntities.Add(m_Entities[i]);
    }
}

triebWerk::CEntity* triebWerk::CWorld::GetEntity(size_t a_ID) const
{
    CEntity* entity = m_Entities[a_ID];
    return entity;
}

size_t triebWerk::CWorld::GetEntityCount() const
{
    return m_Entities.GetSize();
}

void triebWerk::CWorld::GetEntityBehaviour()
{
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        CEntity* pEntity = m_Entities[i];

        if (pEntity->GetBehaviour() != nullptr)
        {
            m_UpdateEntities.Add(pEntity->GetBehaviour());
        }
    }
}

void triebWerk::CWorld::GetEntityBehaviourAndDrawable()
{
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        CEntity* pEntity = m_Entities[i];

        if (pEntity->GetBehaviour() != nullptr)
        {
            m_UpdateEntities.Add(pEntity->GetBehaviour());
        }

        if (pEntity->GetDrawable() != nullptr)
        {
            m_DrawEntities.Add(pEntity);
        }
    }
}

void triebWerk::CWorld::UpdateEntityBehaviour()
{
    size_t size = m_UpdateEntities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        m_UpdateEntities[i]->Update();
    }
}

void triebWerk::CWorld::UpdatePhysic()
{
    m_pPhysicWorld->Update(m_PhysicTimeStamp);
}

void triebWerk::CWorld::LateUpdateEntityBehaviour()
{
    size_t size = m_UpdateEntities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        m_UpdateEntities[i]->LateUpdate();
    }
}

void triebWerk::CWorld::RenderEntities()
{
    size_t size = m_DrawEntities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        m_DrawEntities[i]->GetDrawable()->SetTransform(m_DrawEntities[i]->m_Transform.GetTransformation());
        m_pRenderingHandle->AddRenderCommand(m_DrawEntities[i]->GetDrawable());
    }

    m_pRenderingHandle->DrawScene();
}

void triebWerk::CWorld::DeleteRemoveEntities()
{
    // TO DO: maybe improve this a bit in case ClearEntities() gets called..
    size_t removeSize = m_RemoveEntities.GetSize();
    for (size_t i = 0; i < removeSize; ++i)
    {
        CEntity* removeEntity = m_RemoveEntities[i];

        m_Entities.Remove(removeEntity);
        DeleteEntity(removeEntity);
    }

    m_RemoveEntities.Reset();
}

void triebWerk::CWorld::DeleteEntity(CEntity* a_pEntity)
{
	a_pEntity->RemoveBehaviour();
	a_pEntity->RemovePhysicEntity();
	a_pEntity->RemoveDrawable();

    delete a_pEntity;
}
