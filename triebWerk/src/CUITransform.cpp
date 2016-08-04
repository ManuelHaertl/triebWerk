#include <CUITransform.h>

float triebWerk::CUITransform::ResolutionWidth = 800.0f;
float triebWerk::CUITransform::ResolutionHeight = 600.0f;
float triebWerk::CUITransform::ReferenceWidth = 800.0f;
float triebWerk::CUITransform::ReferenceHeight = 600.0f;
float triebWerk::CUITransform::ReferenceScale = 1.0f;

triebWerk::CUITransform::CUITransform()
    : m_Modified(true)
    , m_AnchorPoint(DirectX::XMFLOAT2(0.f, 0.0f))
    , m_PositionOffset(DirectX::XMVectorZero())
    , m_Scale(DirectX::XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f))
    , m_Rotation(DirectX::XMVectorZero())
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
    return m_Rotation.m128_f32[2];
}

DirectX::XMVECTOR triebWerk::CUITransform::GetPivot() const
{
    return m_Pivot;
}

DirectX::XMMATRIX& triebWerk::CUITransform::GetTransformation()
{
    if (m_Modified)
    {
        float x = ((ReferenceWidth / 2.0f * m_AnchorPoint.x) + m_PositionOffset.m128_f32[0]) * ReferenceScale;
        float y = ((ReferenceHeight / 2.0f * m_AnchorPoint.y) + m_PositionOffset.m128_f32[1]) * ReferenceScale;

        DirectX::XMVECTOR realPosition = DirectX::XMVectorSet(x, y, m_PositionOffset.m128_f32[2], 0.0f);
        DirectX::XMVECTOR realScale = DirectX::XMVectorScale(m_Scale, ReferenceScale);

        m_Transformation = DirectX::XMMatrixTransformation(m_Pivot, DirectX::XMQuaternionIdentity(), realScale, m_Pivot, m_Rotation, realPosition);
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
    m_Rotation = DirectX::XMQuaternionRotationRollPitchYaw(
        DirectX::XMConvertToRadians(0.0f),
        DirectX::XMConvertToRadians(0.0f),
        DirectX::XMConvertToRadians(a_Rotation));
    Modified();
}

void triebWerk::CUITransform::SetRotationRadians(const float a_Rotation)
{
    m_Rotation = DirectX::XMQuaternionRotationRollPitchYaw(0.0f, 0.0f, a_Rotation);
    Modified();
}

void triebWerk::CUITransform::RotateDegrees(const float a_Degrees)
{
    DirectX::XMVECTOR rotation = DirectX::XMQuaternionRotationRollPitchYaw(
        DirectX::XMConvertToRadians(0.0f),
        DirectX::XMConvertToRadians(0.0f),
        DirectX::XMConvertToRadians(a_Degrees));

    m_Rotation = DirectX::XMQuaternionMultiply(m_Rotation, rotation);
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

void triebWerk::CUITransform::UpdateScreenInformation()
{
    m_Modified = true;
}

inline void triebWerk::CUITransform::Modified()
{
    m_Modified = true;
}
