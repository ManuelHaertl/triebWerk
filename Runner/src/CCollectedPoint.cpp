#include <CCollectedPoint.h>

CCollectedPoint::CCollectedPoint() :
    m_CurrentState(0.0f),
    m_CurrentScale(1.0f),
    m_AddedSpeed(0.0f),
    m_CurrentTime(0.0f),
    m_pMeshDrawable(nullptr)
{
}

CCollectedPoint::~CCollectedPoint()
{
}

void CCollectedPoint::Start()
{
    m_pMeshDrawable = static_cast<triebWerk::CMeshDrawable*>(m_pEntity->GetDrawable());;
}

void CCollectedPoint::Update()
{
    m_CurrentState += Speed * twTime->GetDeltaTime();
    m_CurrentScale -= ScaleValue * twTime->GetDeltaTime();

    m_pEntity->m_Transform.SetScale(m_CurrentScale, m_CurrentScale, m_CurrentScale);

    m_pMeshDrawable->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &m_CurrentState);

    m_CurrentTime += twTime->GetDeltaTime();
    if (m_CurrentTime >= TimeAlive)
        twActiveWorld->RemoveEntity(m_pEntity);
}

void CCollectedPoint::End()
{
}
