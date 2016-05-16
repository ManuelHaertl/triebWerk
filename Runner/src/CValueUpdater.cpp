#include <CValueUpdater.h>
#include <CPlayer.h>

CValueUpdater::CValueUpdater() :
    m_pValues(nullptr)
{
}

CValueUpdater::~CValueUpdater()
{
}

void CValueUpdater::Start()
{
    m_pValues = twResourceManager->GetTWFData("values");
}

void CValueUpdater::Update()
{
    if (m_pValues != nullptr && m_pValues->m_IsModified == true)
    {
        m_pValues->m_IsModified = false;

        for (auto value : m_pValues->m_ConfigurationTable)
        {
            if (value.first == "FlySpeed")
            {
                CPlayer::FlySpeed = std::stof(value.second);
            }
            else if (value.first == "Acceleration")
            {
                CPlayer::Acceleration = std::stof(value.second);
            }
            else if (value.first == "Drag")
            {
                CPlayer::Drag = std::stof(value.second);
            }
            else if (value.first == "MaxSpeed")
            {
                CPlayer::MaxSpeed = std::stof(value.second);
            }
            else if (value.first == "MaxRotation")
            {
                CPlayer::MaxRotation = std::stof(value.second);
            }
            else if (value.first == "RotationCameraFactor")
            {
                CPlayer::RotationCameraFactor = std::stof(value.second);
            }
        }
    }
}

void CValueUpdater::End()
{
}
