#include <CMovingObstacle.h>
#include <CGameInfo.h>

CMovingObstacle::CMovingObstacle(const DirectX::XMVECTOR a_PositionStart, const DirectX::XMVECTOR a_PositionEnd, const float a_Time, const float a_Distance, triebWerk::CEntity* a_pShadow)
    : PositionStart(a_PositionStart)
    , PositionEnd(a_PositionEnd)
    , Time(a_Time)
    , Distance(a_Distance)
    , m_pShadow(a_pShadow)
    , m_IsMoving(false)
    , m_CurrentTime(0.0f)
{

}

CMovingObstacle::~CMovingObstacle()
{

}

void CMovingObstacle::Start()
{
}

void CMovingObstacle::Update()
{
    if (m_IsMoving)
    {
        m_CurrentTime += twTime->GetDeltaTime();
        if (m_CurrentTime > Time)
            m_CurrentTime = Time;

        float lerpValue = m_CurrentTime / Time;
        DirectX::XMVECTOR newPos = DirectX::XMVectorLerp(PositionStart, PositionEnd, lerpValue);
        m_pEntity->m_Transform.SetPosition(newPos);

        newPos.m128_f32[1] = 0.001f;
        m_pShadow->m_Transform.SetPosition(newPos);
    }
    else
    {
        // check when the player is in range to move the object
        float dist = m_pEntity->m_Transform.GetPosition().m128_f32[2] - CGameInfo::Instance().m_PlayerPosition;
        if (dist < Distance)
            m_IsMoving = true;
    }
}

void CMovingObstacle::End()
{
}
