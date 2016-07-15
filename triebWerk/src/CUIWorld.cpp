#include <CUIWorld.h>

triebWerk::CUIWorld::CUIWorld()
    : m_CurrentSize(0)
    , m_Entities()
    , m_UpdateEntities()
    , m_DrawEntities()
    , m_pRenderingHandle(nullptr)
{
}

triebWerk::CUIWorld::~CUIWorld()
{
}

void triebWerk::CUIWorld::Initialize(CRenderer* a_pRenderer)
{
}

void triebWerk::CUIWorld::Update()
{
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
