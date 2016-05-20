#include <CWorld.h>

triebWerk::CWorld::CWorld() :
    m_pPhysicWorld(nullptr),
    m_CurrentSize(Start_Reserve_Size),
    m_EntitiesToUpdate(0),
    m_EntitiesToDraw(0),
    m_EntitiesToRemove(0),
    m_pRenderingHandle(nullptr),
    m_TimePerFrame(0.0f),
    m_CurrentRenderTime(0.0f),
    m_PhysicTimeStamp(0.0f),
    m_CurrentPhysicTime(0.0f)
{
}

triebWerk::CWorld::~CWorld()
{
}

bool triebWerk::CWorld::Initialize(CRenderer * a_pRenderer, const float a_TargetFPS, const float a_PhysicTimeStamp)
{
    m_pPhysicWorld = new CPhysicWorld();

    // reserve some spots so the vector doesn't need
    // to get resized too often during runtime
    m_Entities.reserve(Start_Reserve_Size);
    m_UpdateEntities.resize(Start_Reserve_Size);
    m_DrawEntities.resize(Start_Reserve_Size);
    m_RemoveEntities.resize(Start_Reserve_Size);

    m_pRenderingHandle = a_pRenderer;
    m_PhysicTimeStamp = a_PhysicTimeStamp;

    m_TimePerFrame = 1.0f / a_TargetFPS;

    return true;
}

bool triebWerk::CWorld::Update(const float a_DeltaTime)
{
    m_CurrentRenderTime += a_DeltaTime;
    m_CurrentPhysicTime += a_DeltaTime;

    bool renderUpdate = false;
    bool physicUpdate = false;

    if (m_CurrentRenderTime >= m_TimePerFrame)
    {
        m_CurrentRenderTime -= m_TimePerFrame;
        renderUpdate = true;
    }

    if (m_CurrentPhysicTime >= m_PhysicTimeStamp)
    {
        m_CurrentPhysicTime -= m_PhysicTimeStamp;
        physicUpdate = true;
    }

    if (renderUpdate && physicUpdate)
    {
        GetEntityBehaviourAndDrawable();
        UpdateEntityBehaviour();
        UpdatePhysic();
        LateUpdateEntityBehaviour();
        RenderEntities();
        DeleteRemoveEntities();

        m_EntitiesToUpdate = 0;
        m_EntitiesToDraw = 0;
    }
    else if (renderUpdate)
    {
        GetEntityBehaviourAndDrawable();
        UpdateEntityBehaviour();
        LateUpdateEntityBehaviour();
        RenderEntities();
        DeleteRemoveEntities();

        m_EntitiesToUpdate = 0;
        m_EntitiesToDraw = 0;
    }
    else if (physicUpdate)
    {
        GetEntityBehaviour();
        UpdateEntityBehaviour();
        UpdatePhysic();
        LateUpdateEntityBehaviour();
        DeleteRemoveEntities();

        m_EntitiesToUpdate = 0;
    }
    else
    {
        GetEntityBehaviour();
        UpdateEntityBehaviour();
        LateUpdateEntityBehaviour();
        DeleteRemoveEntities();

        m_EntitiesToUpdate = 0;
    }

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
        m_UpdateEntities.resize(m_CurrentSize);
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

void triebWerk::CWorld::GetEntityBehaviour()
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        CEntity* pEntity = m_Entities[i];

        if (pEntity->GetBehaviour() != nullptr)
        {
            m_UpdateEntities[m_EntitiesToUpdate] = pEntity->GetBehaviour();
            m_EntitiesToUpdate++;
        }
    }
}

void triebWerk::CWorld::GetEntityBehaviourAndDrawable()
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        CEntity* pEntity = m_Entities[i];

        if (pEntity->GetBehaviour() != nullptr)
        {
            m_UpdateEntities[m_EntitiesToUpdate] = pEntity->GetBehaviour();
            m_EntitiesToUpdate++;
        }

        if (pEntity->GetDrawable() != nullptr)
        {
            m_DrawEntities[m_EntitiesToDraw] = pEntity;
            m_EntitiesToDraw++;
        }
    }
}

void triebWerk::CWorld::UpdateEntityBehaviour()
{
    for (size_t i = 0; i < m_EntitiesToUpdate; ++i)
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
    for (size_t i = 0; i < m_EntitiesToUpdate; ++i)
    {
        m_UpdateEntities[i]->LateUpdate();
    }
}

void triebWerk::CWorld::RenderEntities()
{
    for (size_t i = 0; i < m_EntitiesToDraw; ++i)
    {
        m_DrawEntities[i]->GetDrawable()->SetTransform(m_DrawEntities[i]->m_Transform.GetTransformation());
        m_pRenderingHandle->AddRenderCommand(m_DrawEntities[i]->GetDrawable());
    }

    m_pRenderingHandle->DrawScene();
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
