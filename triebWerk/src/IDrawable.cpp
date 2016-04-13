#include <IDrawable.h>

triebWerk::IDrawable::IDrawable() :
	m_ActiveState(false),
	m_Type(EDrawableType::Empty)
{
}

triebWerk::IDrawable::~IDrawable()
{
}

void triebWerk::IDrawable::SetActive(bool a_State)
{
	m_ActiveState = a_State;
}

bool triebWerk::IDrawable::IsActive()
{
	return m_ActiveState;
}

