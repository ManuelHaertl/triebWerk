#include <CUITransform.h>

triebWerk::CUITransform::CUITransform()
    : m_Modified(false)
    , m_AnchorPoint(DirectX::XMFLOAT2(0.f, 0.0f))
    , m_PositionOffset(DirectX::XMVectorZero())
    , m_Scale(DirectX::XMVectorZero())
    , m_Rotation(0.0f)
    , m_RealPosition(DirectX::XMVectorZero())
    , m_RealScale(DirectX::XMVectorZero())
    , m_Pivot(DirectX::XMVectorZero())
    , m_Transformation(DirectX::XMMatrixIdentity())
{
}

triebWerk::CUITransform::~CUITransform()
{
}

DirectX::XMFLOAT2 triebWerk::CUITransform::GetAnchorPoint() const
{
    return m_AnchorPoint;
}

DirectX::XMVECTOR triebWerk::CUITransform::GetPositionOffset() const
{
    return m_PositionOffset;
}

DirectX::XMVECTOR triebWerk::CUITransform::GetScale() const
{
    return m_Scale;
}

float triebWerk::CUITransform::GetRotation() const
{
    return m_Rotation;
}

DirectX::XMVECTOR triebWerk::CUITransform::GetPivot() const
{
    return m_Pivot;
}

DirectX::XMMATRIX& triebWerk::CUITransform::GetTransformation()
{
    if (m_Modified)
    {
        m_Transformation = DirectX::XMMatrixTransformation2D(m_Pivot, 0.0f, m_RealScale, m_Pivot, m_Rotation, m_RealPosition);
        m_Modified = false;
    }

    return m_Transformation;
}

void triebWerk::CUITransform::SetAnchorPoint(const float a_X, const float a_Y)
{
    m_AnchorPoint.x = a_X;
    m_AnchorPoint.y = a_Y;
    Modified();
}

void triebWerk::CUITransform::SetAnchorPoint(const DirectX::XMFLOAT2 a_AnchorPoint)
{
    m_AnchorPoint = a_AnchorPoint;
    Modified();
}

void triebWerk::CUITransform::SetPositionOffset(const float a_X, const float a_Y, const float a_Z)
{
    m_PositionOffset = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);
    Modified();
}

void triebWerk::CUITransform::SetPositionOffset(const DirectX::XMVECTOR a_PositionOffset)
{
    m_PositionOffset = a_PositionOffset;
    Modified();
}

void triebWerk::CUITransform::SetScale(const float a_X, const float a_Y, const float a_Z)
{
    m_Scale = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);
    Modified();
}

void triebWerk::CUITransform::SetScale(const DirectX::XMVECTOR a_Scale)
{
    m_Scale = a_Scale;
    Modified();
}

void triebWerk::CUITransform::SetRotationDegrees(const float a_Rotation)
{
    m_Rotation = DirectX::XMConvertToRadians(a_Rotation);
    Modified();
}

void triebWerk::CUITransform::SetRotationRadians(const float a_Rotation)
{
    m_Rotation = a_Rotation;
    Modified();
}

void triebWerk::CUITransform::RotateDegrees(const float a_Degrees)
{
    m_Rotation *= DirectX::XMConvertToRadians(a_Degrees);
    Modified();
}

void triebWerk::CUITransform::SetPivot(const float a_X, const float a_Y, const float a_Z)
{
    m_Pivot = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);
    Modified();
}

void triebWerk::CUITransform::SetPivot(const DirectX::XMVECTOR a_Pivot)
{
    m_Pivot = a_Pivot;
    Modified();
}

void triebWerk::CUITransform::SetScreenInformation(const SUIScreenInformation& a_rScreenInformation)
{
    float x = ((a_rScreenInformation.m_Width / 2.0f * m_AnchorPoint.x) + m_PositionOffset.m128_f32[0]) * a_rScreenInformation.m_Scale;
    float y = ((a_rScreenInformation.m_Height / 2.0f * m_AnchorPoint.y) + m_PositionOffset.m128_f32[1]) * a_rScreenInformation.m_Scale;

    m_RealPosition = DirectX::XMVectorSet(x, y, m_PositionOffset.m128_f32[2], 0.0f);    
    m_RealScale = DirectX::XMVectorScale(m_Scale, a_rScreenInformation.m_Scale);
}

inline void triebWerk::CUITransform::Modified()
{
    m_Modified = true;
}
