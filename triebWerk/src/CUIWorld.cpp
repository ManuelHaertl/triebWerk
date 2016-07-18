#include <CUIWorld.h>

triebWerk::CUIWorld::CUIWorld()
    : m_CurrentSize(0)
    , m_Entities()
    , m_UpdateEntities()
    , m_DrawEntities()
    , m_RemoveEntities()
    , m_pRenderingHandle(nullptr)
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
}

void triebWerk::CUIWorld::Shutdown()
{
}

triebWerk::CUIEntity* triebWerk::CUIWorld::CreateUIEntity() const
{
    return nullptr;
}

void triebWerk::CUIWorld::AddUIEntity(CUIEntity * a_pUIEntity)
{
}

void triebWerk::CUIWorld::RemoveUIEntity(CUIEntity * a_pUIEntity)
{
}

void triebWerk::CUIWorld::ClearUIEntities()
{
}

triebWerk::CUIEntity* triebWerk::CUIWorld::GetEntity(const size_t a_ID) const
{
    return nullptr;
}

size_t triebWerk::CUIWorld::GetEntityCount() const
{
    return size_t();
}

void triebWerk::CUIWorld::DeleteEntity(CEntity * a_pEntity)
{
}
