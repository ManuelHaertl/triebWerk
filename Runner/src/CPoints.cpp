#include <CPoints.h>

CPoints::CPoints()
{
}

CPoints::~CPoints()
{
}

void CPoints::Start()
{
}

void CPoints::Update()
{
    m_pEntity->m_Transform.RotateDegrees(0.0f, RotateSpeed * twTime->GetDeltaTime(), 0.0f);
}

void CPoints::End()
{
}
