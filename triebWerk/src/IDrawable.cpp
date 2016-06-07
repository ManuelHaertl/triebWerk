#include <IDrawable.h>

triebWerk::IDrawable::IDrawable() :
	m_ActiveState(true),
	m_Type(EDrawableType::Empty),
	m_RenderTargetSlot(0)
{
}

triebWerk::IDrawable::~IDrawable()
{
}

void triebWerk::IDrawable::SetRenderTarget(unsigned int a_Slot)
{
	m_RenderTargetSlot = a_Slot;
}

unsigned int triebWerk::IDrawable::GetRenderTargetSlot() const
{
	return m_RenderTargetSlot;
}

void triebWerk::IDrawable::SetActive(bool a_State)
{
	m_ActiveState = a_State;
}

bool triebWerk::IDrawable::IsActive() const
{
	return m_ActiveState;
}


