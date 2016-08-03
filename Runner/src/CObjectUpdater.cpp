#include <CObjectUpdater.h>

#include <CEnvironmentCreator.h>

CObjectUpdater::CObjectUpdater()
    : m_pValues(nullptr)
{
}

CObjectUpdater::~CObjectUpdater()
{
}

void CObjectUpdater::Start(triebWerk::CEntity * a_pSnake1, triebWerk::CEntity * a_pSnake2, triebWerk::CEntity * a_pSnake3)
{
    m_pSnake1 = a_pSnake1;
    m_pSnake2 = a_pSnake2;
    m_pSnake3 = a_pSnake3;

    m_pValues = twResourceManager->GetTWFData("objects");

    if (m_pValues != nullptr)
        UpdateValues();
}

void CObjectUpdater::Update()
{
    if (m_pValues != nullptr && m_pValues->m_IsModified == true)
    {
        m_pValues->m_IsModified = false;
        UpdateValues();
    }

    RotateSnakes();
}

void CObjectUpdater::UpdateValues()
{
    DirectX::XMVECTOR snake1Position = DirectX::XMVectorZero();
    DirectX::XMVECTOR snake1Scale = DirectX::XMVectorZero();

    DirectX::XMVECTOR snake2Position = DirectX::XMVectorZero();
    DirectX::XMVECTOR snake2Scale = DirectX::XMVectorZero();

    DirectX::XMVECTOR snake3Position = DirectX::XMVectorZero();
    DirectX::XMVECTOR snake3Scale = DirectX::XMVectorZero();

    DirectX::XMVECTOR fogPosition[FogCount];
    DirectX::XMVECTOR fogScale[FogCount];
    DirectX::XMVECTOR fogRotation[FogCount];

    for (size_t i = 0; i < FogCount; ++i)
    {
        fogPosition[i] = DirectX::XMVectorZero();
        fogScale[i] = DirectX::XMVectorZero();
        fogRotation[i] = DirectX::XMVectorZero();
        fogRotation[i].m128_f32[3] = 1.0f;
    }

    for (auto value : m_pValues->m_ConfigurationTable)
    {
        // Snake 1
        if      (value.first == "s1_PositionX") snake1Position.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s1_PositionY") snake1Position.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s1_PositionZ") snake1Position.m128_f32[2] = std::stof(value.second);

        else if (value.first == "s1_ScaleX") snake1Scale.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s1_ScaleY") snake1Scale.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s1_ScaleZ") snake1Scale.m128_f32[2] = std::stof(value.second);

        else if (value.first == "s1_RotationX") snake1Rotation.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s1_RotationY") snake1Rotation.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s1_RotationZ") snake1Rotation.m128_f32[2] = std::stof(value.second);

        // Snake 2
        else if (value.first == "s2_PositionX") snake2Position.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s2_PositionY") snake2Position.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s2_PositionZ") snake2Position.m128_f32[2] = std::stof(value.second);

        else if (value.first == "s2_ScaleX") snake2Scale.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s2_ScaleY") snake2Scale.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s2_ScaleZ") snake2Scale.m128_f32[2] = std::stof(value.second);

        else if (value.first == "s2_RotationX") snake2Rotation.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s2_RotationY") snake2Rotation.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s2_RotationZ") snake2Rotation.m128_f32[2] = std::stof(value.second);

        // Snake 3
        else if (value.first == "s3_PositionX") snake3Position.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s3_PositionY") snake3Position.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s3_PositionZ") snake3Position.m128_f32[2] = std::stof(value.second);

        else if (value.first == "s3_ScaleX") snake3Scale.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s3_ScaleY") snake3Scale.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s3_ScaleZ") snake3Scale.m128_f32[2] = std::stof(value.second);

        else if (value.first == "s3_RotationX") snake3Rotation.m128_f32[0] = std::stof(value.second);
        else if (value.first == "s3_RotationY") snake3Rotation.m128_f32[1] = std::stof(value.second);
        else if (value.first == "s3_RotationZ") snake3Rotation.m128_f32[2] = std::stof(value.second);

        else
        {
            size_t pos = value.first.find('_', 0);
            int number = std::stoi(value.first.substr(0, pos));
            std::string text = value.first.substr(pos, value.first.size() - (pos));

            if      (text == "_PositionX") fogPosition[number].m128_f32[0] = std::stof(value.second);
            else if (text == "_PositionY") fogPosition[number].m128_f32[1] = std::stof(value.second);
            else if (text == "_PositionZ") fogPosition[number].m128_f32[2] = std::stof(value.second);

            else if (text == "_ScaleX") fogScale[number].m128_f32[0] = std::stof(value.second);
            else if (text == "_ScaleY") fogScale[number].m128_f32[1] = std::stof(value.second);
            else if (text == "_ScaleZ") fogScale[number].m128_f32[2] = std::stof(value.second);

            else if (text == "_RotationX") fogRotation[number].m128_f32[0] = std::stof(value.second);
            else if (text == "_RotationY") fogRotation[number].m128_f32[1] = std::stof(value.second);
            else if (text == "_RotationZ") fogRotation[number].m128_f32[2] = std::stof(value.second);
        }
    }

    m_pSnake1->m_Transform.SetPosition(snake1Position);
    m_pSnake1->m_Transform.SetScale(snake1Scale);
    m_pSnake1->m_Transform.SetRotationDegrees(snake1Rotation);

    m_pSnake2->m_Transform.SetPosition(snake2Position);
    m_pSnake2->m_Transform.SetScale(snake2Scale);
    m_pSnake2->m_Transform.SetRotationDegrees(snake2Rotation);

    m_pSnake3->m_Transform.SetPosition(snake3Position);
    m_pSnake3->m_Transform.SetScale(snake3Scale);
    m_pSnake3->m_Transform.SetRotationDegrees(snake3Rotation);

    for (size_t i = 0; i < FogCount; ++i)
    {
        m_Fog[i]->m_Transform.SetPosition(fogPosition[i]);
        m_Fog[i]->m_Transform.SetScale(fogScale[i]);
        m_Fog[i]->m_Transform.SetRotationDegrees(fogRotation[i].m128_f32[0], fogRotation[i].m128_f32[1], fogRotation[i].m128_f32[2]);
    }
}

void CObjectUpdater::RotateSnakes()
{
    float dt = twTime->GetDeltaTime();
    snake1Rotation.m128_f32[0] += dt * CEnvironmentCreator::SnakeRotateSpeed1;
    snake2Rotation.m128_f32[0] += dt * CEnvironmentCreator::SnakeRotateSpeed2;
    snake3Rotation.m128_f32[0] += dt * CEnvironmentCreator::SnakeRotateSpeed3;
    m_pSnake1->m_Transform.SetRotationDegrees(snake1Rotation);
    m_pSnake2->m_Transform.SetRotationDegrees(snake2Rotation);
    m_pSnake3->m_Transform.SetRotationDegrees(snake3Rotation);
}
