#include <CUIWorld.h>

float triebWerk::CUIWorld::m_ScreenResolutionX = 800.0f;
float triebWerk::CUIWorld::m_ScreenResolutionY = 600.0f;

triebWerk::CUIWorld::CUIWorld()
    : m_CurrentSize(Start_Reserve_Size)
    , m_Entities()
    , m_UpdateEntities()
    , m_DrawEntities()
    , m_RemoveEntities()
    , m_pRenderingHandle(nullptr)
    , m_ReferenceResolutionX(800.0f)
    , m_ReferenceResolutionY(600.0f)
    , m_ScreenMatchState(EScreenMatchState::Width)
{
}

triebWerk::CUIWorld::~CUIWorld()
{
}

void triebWerk::CUIWorld::Initialize(CRenderer* a_pRenderer)
{
    Shutdown();

    m_pRenderingHandle = a_pRenderer;

    // reserve some spots so the vector doesn't need
    // to get resized too often during runtime
    m_Entities.Resize(Start_Reserve_Size);
    m_UpdateEntities.Resize(Start_Reserve_Size);
    m_DrawEntities.Resize(Start_Reserve_Size);
    m_RemoveEntities.Resize(Start_Reserve_Size);
}

void triebWerk::CUIWorld::Update()
{
    // Get Entity Behaviour and Drawable
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        CUIEntity* pEntity = m_Entities[i];

        if (pEntity->GetBehaviour() != nullptr)
        {
            m_UpdateEntities.Add(pEntity->GetBehaviour());
        }

        if (pEntity->GetDrawable() != nullptr)
        {
            m_DrawEntities.Add(pEntity);
        }
    }

    // Update Entity Behaviour
    size = m_UpdateEntities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        m_UpdateEntities[i]->Update();
    }

    // Render entities
    size = m_DrawEntities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        m_DrawEntities[i]->GetDrawable()->SetTransform(m_DrawEntities[i]->m_Transform.GetTransformation());
        m_pRenderingHandle->AddRenderCommand(m_DrawEntities[i]->GetDrawable());
    }

    m_UpdateEntities.Reset();
    m_DrawEntities.Reset();
}

void triebWerk::CUIWorld::Shutdown()
{
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        DeleteEntity(m_Entities[i]);
    }
    m_Entities.Clear();
}

void triebWerk::CUIWorld::RemoveDeleteEntities()
{
    size_t removeSize = m_RemoveEntities.GetSize();
    for (size_t i = 0; i < removeSize; ++i)
    {
        CUIEntity* removeEntity = m_RemoveEntities[i];

        m_Entities.Remove(removeEntity);
        DeleteEntity(removeEntity);
    }

    m_RemoveEntities.Reset();
}

void triebWerk::CUIWorld::SetScreenResolution(const int m_Width, const int m_Height)
{
    m_ScreenResolutionX = static_cast<float>(m_Width);
    m_ScreenResolutionY = static_cast<float>(m_Height);

    UpdateScreenInformation();
}

void triebWerk::CUIWorld::SetReferenceResolution(const float m_Width, const float m_Height, const EScreenMatchState m_MatchState)
{
    m_ReferenceResolutionX = m_Width;
    m_ReferenceResolutionY = m_Height;
    m_ScreenMatchState = m_MatchState;

    UpdateScreenInformation();
}

triebWerk::CUIEntity* triebWerk::CUIWorld::CreateUIEntity() const
{
    CUIEntity* entity = new CUIEntity();
    return entity;
}

void triebWerk::CUIWorld::AddUIEntity(CUIEntity * a_pUIEntity)
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
    m_Entities.Add(a_pUIEntity);

    // now set the world state true because every needed subsystem has been added
    a_pUIEntity->SetInWorldState(true);

    if (a_pUIEntity->GetBehaviour() != nullptr)
    {
        // call the behaviour start function at the end because behaviour
        // functions only may be called while the entity is in the world
        a_pUIEntity->GetBehaviour()->Start();
    }
}

void triebWerk::CUIWorld::RemoveUIEntity(CUIEntity * a_pUIEntity)
{
    if (a_pUIEntity != nullptr && m_RemoveEntities.Contains(a_pUIEntity) == false)
    {
        IBehaviour* behaviour = a_pUIEntity->GetBehaviour();
        if (behaviour != nullptr)
            behaviour->End();

        m_RemoveEntities.Add(a_pUIEntity);
    }
}

void triebWerk::CUIWorld::ClearUIEntities()
{
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        IBehaviour* behaviour = m_Entities[i]->GetBehaviour();
        if (behaviour != nullptr)
            behaviour->End();

        m_RemoveEntities.Add(m_Entities[i]);
    }
}

triebWerk::CUIEntity* triebWerk::CUIWorld::GetEntity(const size_t a_ID) const
{
    CUIEntity* entity = m_Entities[a_ID];
    return entity;
}

size_t triebWerk::CUIWorld::GetEntityCount() const
{
    return m_Entities.GetSize();
}

void triebWerk::CUIWorld::DeleteEntity(CUIEntity* a_pUIEntity)
{
    a_pUIEntity->RemoveBehaviour();
    a_pUIEntity->RemoveDrawable();

    delete a_pUIEntity;
}

void triebWerk::CUIWorld::UpdateScreenInformation()
{
    // calculate scale value
    if (m_ScreenMatchState == EScreenMatchState::Width)
        CUITransform::ReferenceScale = m_ScreenResolutionX / m_ReferenceResolutionX;
    else
        CUITransform::ReferenceScale = m_ScreenResolutionY / m_ReferenceResolutionY;

    CUITransform::ResolutionWidth = m_ScreenResolutionX;
    CUITransform::ResolutionHeight = m_ScreenResolutionY;
    CUITransform::ReferenceWidth = m_ReferenceResolutionX;
    CUITransform::ReferenceHeight = m_ReferenceResolutionY;

    // tell all entities to update their transformation
    size_t size = m_Entities.GetSize();
    for (size_t i = 0; i < size; ++i)
        m_Entities[i]->m_Transform.UpdateScreenInformation();
}
