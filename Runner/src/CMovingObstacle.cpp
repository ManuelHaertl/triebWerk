#include <CMovingObstacle.h>
#include <CGameInfo.h>

CMovingObstacle::CMovingObstacle(const float a_PositionStart, const float a_PositionEnd, const float a_Time, const float a_Distance)
    : PositionStart(a_PositionStart)
    , PositionEnd(a_PositionEnd)
    , Time(a_Time)
    , Distance(a_Distance)
    , m_Up(false)
    , m_IsMoving(false)
    , m_UpDownValue(0.0f)
    , m_Speed(0.0f)
    , m_CurrentTime(0.0f)
{
    m_Speed = (PositionEnd - PositionStart) / Time;
    m_Up = PositionStart < PositionEnd;
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
        auto pos = m_pEntity->m_Transform.GetPosition();
        pos.m128_f32[1] += m_Speed * twTime->GetDeltaTime();

        if (m_Up && pos.m128_f32[1] > PositionEnd)
            pos.m128_f32[1] = PositionEnd;
        else if (!m_Up && pos.m128_f32[1] < PositionEnd)
            pos.m128_f32[1] = PositionEnd;

        m_pEntity->m_Transform.SetPosition(pos);
    }
    else
    {
        float playerPos = CGameInfo::Instance().m_PlayerPosition;
        float obstaclePos = m_pEntity->m_Transform.GetPosition().m128_f32[2];

        float dist = obstaclePos - playerPos;

        if (dist < Distance)
        {
            m_IsMoving = true;
        }
    }    
}

void CMovingObstacle::End()
{
}
