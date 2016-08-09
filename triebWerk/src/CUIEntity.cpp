#include <CUIEntity.h>

triebWerk::CUIEntity::CUIEntity()
    : m_Transform()
    , m_ID()
    , m_pBehaviour(nullptr)
    , m_pDrawable(nullptr)
    , m_IsInWorld(false)
{
}

triebWerk::CUIEntity::~CUIEntity()
{
}

triebWerk::IBehaviour* triebWerk::CUIEntity::GetBehaviour() const
{
    return m_pBehaviour;
}

triebWerk::IDrawable* triebWerk::CUIEntity::GetDrawable() const
{
    return m_pDrawable;
}

void triebWerk::CUIEntity::SetBehaviour(IBehaviour * a_pBehaviour)
{
    // delete the old behaviour in case it gets overwritten
    RemoveBehaviour();

    m_pBehaviour = a_pBehaviour;
    m_pBehaviour->m_pUIEntity = this;

    if (m_IsInWorld)
        m_pBehaviour->Start();
}

void triebWerk::CUIEntity::SetDrawable(IDrawable * a_pDrawable)
{
    RemoveDrawable();
    m_pDrawable = a_pDrawable;
}

void triebWerk::CUIEntity::RemoveBehaviour()
{
    // check if there exists a behaviour
    if (m_pBehaviour != nullptr)
    {
        delete m_pBehaviour;
        m_pBehaviour = nullptr;
    }
}

void triebWerk::CUIEntity::RemoveDrawable()
{
    if (m_pDrawable != nullptr)
    {
        delete m_pDrawable;
        m_pDrawable = nullptr;
    }
}

bool triebWerk::CUIEntity::IsInWorld() const
{
    return m_IsInWorld;
}

void triebWerk::CUIEntity::SetInWorldState(const bool a_State)
{
    m_IsInWorld = a_State;
}
