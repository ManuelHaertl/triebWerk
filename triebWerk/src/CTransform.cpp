#include <CTransform.h>

triebWerk::CTransform::CTransform() :
    m_pParent(nullptr),
	m_Modified(true)
{
    m_Position = DirectX::XMVectorZero();
    m_LocalPosition = DirectX::XMVectorZero();
	m_Rotation = DirectX::XMQuaternionIdentity();
    m_LocalRotation = DirectX::XMQuaternionIdentity();
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

void triebWerk::CTransform::SetParent(CTransform * a_pParent)
{
    m_pParent = a_pParent;
}

triebWerk::CTransform * triebWerk::CTransform::GetParent()
{
    return m_pParent;
}

void triebWerk::CTransform::AddChild(CTransform * a_pChild)
{
    a_pChild->SetParent(this);
    m_Children.push_back(a_pChild);
}

void triebWerk::CTransform::RemoveChild(CTransform * a_pChild)
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

std::vector<triebWerk::CTransform*>* triebWerk::CTransform::GetChildren()
{
    return &m_Children;
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

DirectX::XMVECTOR triebWerk::CTransform::GetPosition()
{
    return m_Position;
}

DirectX::XMVECTOR triebWerk::CTransform::GetLocalPosition()
{
    return m_LocalPosition;
}

DirectX::XMVECTOR triebWerk::CTransform::GetScale()
{
    return m_Scale;
}

DirectX::XMVECTOR triebWerk::CTransform::GetLocalScale()
{
    return m_LocalScale;
}

DirectX::XMVECTOR triebWerk::CTransform::GetRotation()
{
    return m_Rotation;
}

DirectX::XMVECTOR triebWerk::CTransform::GetLocalRotation()
{
    return m_LocalRotation;
}

void triebWerk::CTransform::SetPosition(float a_X, float a_Y, float a_Z)
{
    m_Position = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);

    if (m_pParent != nullptr)
        m_LocalPosition = DirectX::XMVectorSubtract(m_Position, m_pParent->GetPosition());

    else
        m_LocalPosition = m_Position;

	UpdateChildPosition();

	m_Modified = true;
}

void triebWerk::CTransform::SetPosition(DirectX::XMVECTOR a_Position)
{
    m_Position = a_Position;

    if (m_pParent != nullptr)
        m_LocalPosition = DirectX::XMVectorSubtract(m_Position, m_pParent->GetPosition());

    else
        m_LocalPosition = m_Position;

    UpdateChildPosition();

	m_Modified = true;
}

void triebWerk::CTransform::SetLocalPosition(float a_X, float a_Y, float a_Z)
{
    m_LocalPosition = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);

    if (m_pParent != nullptr)
        m_Position = DirectX::XMVectorAdd(m_pParent->GetPosition(), m_LocalPosition);

    else
        m_Position = m_LocalPosition;

    UpdateChildPosition();

	m_Modified = true;
}

void triebWerk::CTransform::SetLocalPosition(DirectX::XMVECTOR a_Position)
{
    m_LocalPosition = a_Position;

    if (m_pParent != nullptr)
        m_Position = DirectX::XMVectorAdd(m_pParent->GetPosition(), m_LocalPosition);

    else
        m_Position = m_LocalPosition;

    UpdateChildPosition();

	m_Modified = true;
}

void triebWerk::CTransform::SetScale(float a_X, float a_Y, float a_Z)
{
    m_Scale = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);

	m_Modified = true;
}

void triebWerk::CTransform::SetScale(DirectX::XMVECTOR a_Scale)
{
    m_Scale = a_Scale;

	m_Modified = true;
}

void triebWerk::CTransform::SetRotation(float a_X, float a_Y, float a_Z)
{
    m_Rotation = DirectX::XMVectorSet(a_X, a_Y, a_Z, 0.0f);

	m_Modified = true;
}

void triebWerk::CTransform::SetRotation(DirectX::XMVECTOR a_Rotation)
{
    m_Rotation = a_Rotation;

	m_Modified = true;
}

DirectX::XMMATRIX & triebWerk::CTransform::GetTransformation()
{
	if (!m_Modified)
		return m_Transformation;
	else
	{
		m_Transformation = DirectX::XMMatrixTransformation(m_Pivot, DirectX::XMQuaternionIdentity(), m_Scale, m_Pivot, m_Rotation, m_Position);
		m_Modified = false;
		return m_Transformation;
	}

}

void triebWerk::CTransform::UpdateChildPosition()
{
    for (auto child : m_Children)
    {
        DirectX::XMVECTOR newPosition = DirectX::XMVectorAdd(m_Position, child->GetLocalPosition());
        child->SetPosition(newPosition);
    }
}