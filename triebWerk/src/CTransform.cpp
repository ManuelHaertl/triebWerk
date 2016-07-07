#include <CTransform.h>




triebWerk::CTransform::CTransform() :
    m_pParent(nullptr),
	m_Modified(true),
    m_PhysicModified(true)
{
    m_Position = DirectX::XMVectorZero();
    m_LocalPosition = DirectX::XMVectorZero();
	m_Rotation = DirectX::XMQuaternionIdentity();
    m_LocalRotation = DirectX::XMQuaternionIdentity();
    m_Forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    m_Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_Side = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_Pivot = DirectX::XMVectorZero();
    m_Scale = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
    m_LocalScale = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
}

triebWerk::CTransform::~CTransform()
{
    for (auto child : this->m_Children)
    {
        child->m_pParent = nullptr;
    }

    if (this->m_pParent != nullptr)
    {
        this->m_pParent->RemoveChild(this);
    }
}

void triebWerk::CTransform::SetParent(CTransform* const a_pParent)
{
    m_pParent = a_pParent;
}

triebWerk::CTransform * triebWerk::CTransform::GetParent() const
{
    return m_pParent;
}

void triebWerk::CTransform::AddChild(CTransform* const a_pChild)
{
    a_pChild->SetParent(this);
    m_Children.push_back(a_pChild);
}

void triebWerk::CTransform::RemoveChild(CTransform* const a_pChild)
{
    for (size_t i = 0; i < this->m_Children.size(); i++)
    {
        if (m_Children[i] == a_pChild)
        {
            a_pChild->SetParent(nullptr);
            m_Children.erase(m_Children.begin() + i);
            break;
        }
    }
}

std::vector<triebWerk::CTransform*>* triebWerk::CTransform::GetAllChildren()
{
    return &m_Children;
}

triebWerk::CTransform* triebWerk::CTransform::GetChildren(const size_t a_Index)
{
    return m_Children[a_Index];
}

void triebWerk::CTransform::DetachChildren()
{
    for (auto child : m_Children)
    {
        child->SetParent(nullptr);
    }

    m_Children.clear();
}

void triebWerk::CTransform::DetachFromParent()
{
    m_pParent->RemoveChild(this);
}

DirectX::XMVECTOR triebWerk::CTransform::GetPosition() const
{
    return m_Position;
}

DirectX::XMVECTOR triebWerk::CTransform::GetLocalPosition() const
{
    return m_LocalPosition;
}

DirectX::XMVECTOR triebWerk::CTransform::GetScale() const
{
    return m_Scale;
}

DirectX::XMVECTOR triebWerk::CTransform::GetLocalScale() const
{
    return m_LocalScale;
}

DirectX::XMVECTOR triebWerk::CTransform::GetRotation() const
{
    return m_Rotation;
}

DirectX::XMVECTOR triebWerk::CTransform::GetLocalRotation() const
{
    return m_LocalRotation;
}

DirectX::XMVECTOR triebWerk::CTransform::GetForward() const
{
    return m_Forward;
}

DirectX::XMVECTOR triebWerk::CTransform::GetUp() const
{
    return m_Up;
}

DirectX::XMVECTOR triebWerk::CTransform::GetSide() const
{
    return m_Side;
}

DirectX::XMVECTOR triebWerk::CTransform::GetPivot() const
{
    return m_Pivot;
}

DirectX::XMMATRIX& triebWerk::CTransform::GetTransformation()
{
    if (m_Modified)
    {
        m_Transformation = DirectX::XMMatrixTransformation(m_Pivot, DirectX::XMQuaternionIdentity(), m_Scale, m_Pivot, m_Rotation, m_Position);
        m_Modified = false;
    }
    
    return m_Transformation;
}

void triebWerk::CTransform::SetPosition(const float a_X, const float a_Y, const float a_Z)
{
    m_Position = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);

    if (m_pParent != nullptr)
        m_LocalPosition = DirectX::XMVectorSubtract(m_Position, m_pParent->GetPosition());

    else
        m_LocalPosition = m_Position;

	UpdateChildPosition();
    Modified();
}

void triebWerk::CTransform::SetPosition(const DirectX::XMVECTOR a_Position)
{
    m_Position = a_Position;

    if (m_pParent != nullptr)
        m_LocalPosition = DirectX::XMVectorSubtract(m_Position, m_pParent->GetPosition());

    else
        m_LocalPosition = m_Position;

    UpdateChildPosition();
    Modified();
}

void triebWerk::CTransform::SetLocalPosition(const float a_X, const float a_Y, const float a_Z)
{
    m_LocalPosition = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);

    if (m_pParent != nullptr)
        m_Position = DirectX::XMVectorAdd(m_pParent->GetPosition(), m_LocalPosition);

    else
        m_Position = m_LocalPosition;

    UpdateChildPosition();
    Modified();
}

void triebWerk::CTransform::SetLocalPosition(const DirectX::XMVECTOR a_Position)
{
    m_LocalPosition = a_Position;

    if (m_pParent != nullptr)
        m_Position = DirectX::XMVectorAdd(m_pParent->GetPosition(), m_LocalPosition);

    else
        m_Position = m_LocalPosition;

    UpdateChildPosition();
    Modified();
}

void triebWerk::CTransform::SetScale(const float a_X, const float a_Y, const float a_Z)
{
    m_Scale = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);
    Modified();
}

void triebWerk::CTransform::SetScale(const DirectX::XMVECTOR a_Scale)
{
    m_Scale = a_Scale;
    Modified();
}

void triebWerk::CTransform::SetRotation(const float a_X, const float a_Y, const float a_Z)
{
    m_Rotation = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);
    CalculateForwardUpAndSideVector();
    Modified();
}

void triebWerk::CTransform::SetRotation(const DirectX::XMVECTOR a_Rotation)
{
    m_Rotation = a_Rotation;
    CalculateForwardUpAndSideVector();
    Modified();
}

void triebWerk::CTransform::SetRotationDegrees(const float a_X, const float a_Y, const float a_Z)
{
    m_Rotation = DirectX::XMQuaternionRotationRollPitchYaw(
        DirectX::XMConvertToRadians(a_X),
        DirectX::XMConvertToRadians(a_Y),
        DirectX::XMConvertToRadians(a_Z));

    CalculateForwardUpAndSideVector();
    Modified();
}

void triebWerk::CTransform::SetRotationDegrees(DirectX::XMVECTOR a_Rotation)
{
    a_Rotation.m128_f32[0] = DirectX::XMConvertToRadians(a_Rotation.m128_f32[0]);
    a_Rotation.m128_f32[1] = DirectX::XMConvertToRadians(a_Rotation.m128_f32[1]);
    a_Rotation.m128_f32[2] = DirectX::XMConvertToRadians(a_Rotation.m128_f32[2]);

    m_Rotation = DirectX::XMQuaternionRotationRollPitchYawFromVector(a_Rotation);

    CalculateForwardUpAndSideVector();
    Modified();
}

void triebWerk::CTransform::RotateDegrees(const float a_X, const float a_Y, const float a_Z)
{
    DirectX::XMVECTOR rotation = DirectX::XMQuaternionRotationRollPitchYaw(
        DirectX::XMConvertToRadians(a_X),
        DirectX::XMConvertToRadians(a_Y),
        DirectX::XMConvertToRadians(a_Z));

    m_Rotation = DirectX::XMQuaternionMultiply(m_Rotation, rotation);

    CalculateForwardUpAndSideVector();
    Modified();
}

void triebWerk::CTransform::RotateDegrees(DirectX::XMVECTOR a_Rotation)
{
    a_Rotation.m128_f32[0] = DirectX::XMConvertToRadians(a_Rotation.m128_f32[0]);
    a_Rotation.m128_f32[1] = DirectX::XMConvertToRadians(a_Rotation.m128_f32[1]);
    a_Rotation.m128_f32[2] = DirectX::XMConvertToRadians(a_Rotation.m128_f32[2]);

    m_Rotation = DirectX::XMQuaternionMultiply(m_Rotation, a_Rotation);

    CalculateForwardUpAndSideVector();
    Modified();
}

void triebWerk::CTransform::SetPivot(const float a_X, const float a_Y, const float a_Z)
{
    m_Pivot = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);
    Modified();
}

void triebWerk::CTransform::SetPivot(const DirectX::XMVECTOR a_Pivot)
{
    m_Pivot = a_Pivot;
    Modified();
}

bool triebWerk::CTransform::IsPhysicModified() const
{
    return m_PhysicModified;
}

void triebWerk::CTransform::SetPhysicModifiedState(const bool a_State)
{
    m_PhysicModified = a_State;
}

void triebWerk::CTransform::Modified()
{
    m_Modified = true;
    m_PhysicModified = true;
}

void triebWerk::CTransform::CalculateForwardUpAndSideVector()
{
    DirectX::XMVECTOR forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR side = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

    m_Forward = DirectX::XMVector3Rotate(forward, m_Rotation);
    m_Up = DirectX::XMVector3Rotate(up, m_Rotation);
    m_Side = DirectX::XMVector3Rotate(side, m_Rotation);
}

void triebWerk::CTransform::UpdateChildPosition()
{
    for (size_t i = 0; i < m_Children.size(); ++i)
    {
        DirectX::XMVECTOR newPosition = DirectX::XMVectorAdd(m_Position, m_Children[i]->GetLocalPosition());
        m_Children[i]->SetPosition(newPosition);
    }
}