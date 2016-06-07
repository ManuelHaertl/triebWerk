#include <CValueUpdater.h>

#include <CEnvironmentCreator.h>
#include <CGameInfo.h>
#include <CPatternManager.h>
#include <CPlayer.h>


float CPlayer::FlySpeed = 75.0f;
float CPlayer::Acceleration = 250.0f;
float CPlayer::Drag = 150.0f;
float CPlayer::MaxSpeed = 30.0f;
float CPlayer::DodgeDistance = 15.0f;
float CPlayer::DodgeTime = 0.5f;
float CPlayer::DodgeCooldown = 0.5f;
float CPlayer::MaxRotation = 25.0f;
float CPlayer::RotationCameraFactor = 0.03f;

float CPlayer::RotationX = 347.0f;

float CPlayer::CameraRotationX = 4.7f;
float CPlayer::CameraPosY = 5.0f;
float CPlayer::CameraMinusPosZ = 10.0f;

int CEnvironmentCreator::FeatherSpawnProbability = 40;

float CPatternManager::SpawnDistance = 300.0f;
float CPatternManager::DeleteDistance = 10.0f;
float CPatternManager::StartFreeDistance = 100.0f;

CValueUpdater::CValueUpdater() :
    m_pValues(nullptr)
{
}

CValueUpdater::~CValueUpdater()
{
}

void CValueUpdater::Start()
{
    auto startValues = twResourceManager->GetTWFData("start_values");
    if (startValues != nullptr)
        UpdateStartValues(startValues);

    m_pValues = twResourceManager->GetTWFData("values");
    m_pMainCamera = twRenderer->GetCurrentActiveCamera();

    if (m_pValues != nullptr)
        UpdateValues();
}

void CValueUpdater::Update()
{
    if (m_pValues != nullptr && m_pValues->m_IsModified == true)
    {
        m_pValues->m_IsModified = false;
        UpdateValues();
    }
}

void CValueUpdater::End()
{
}

void CValueUpdater::UpdateStartValues(triebWerk::CTWFData* a_pValues)
{
    CGameInfo& gameInfo = CGameInfo::Instance();

    for (auto value : a_pValues->m_ConfigurationTable)
    {
        if (value.first == "g_Difficulty")
        {
            gameInfo.m_Difficulty = std::stoi(value.second);
        }
        else if (value.first == "g_PointsPerMeter")
        {
            gameInfo.m_PointsPerMeter = std::stof(value.second);
        }
        else if (value.first == "g_AddedMultiplicator")
        {
            gameInfo.m_AddedMultiplier = std::stof(value.second);
        }
        else if (value.first == "g_HighestMultiplicator")
        {
            gameInfo.m_HighestMultiplier = std::stof(value.second);
        }
        else if (value.first == "pm_SpawnDistance")
        {
            CPatternManager::SpawnDistance = std::stof(value.second);
        }
        else if (value.first == "pm_DeleteDistance")
        {
            CPatternManager::DeleteDistance = std::stof(value.second);
        }
        else if (value.first == "pm_StartFreeDistance")
        {
            CPatternManager::StartFreeDistance = std::stof(value.second);
        }
    }
}

void CValueUpdater::UpdateValues()
{
    for (auto value : m_pValues->m_ConfigurationTable)
    {
        if (value.first == "pl_FlySpeed")
        {
            CPlayer::FlySpeed = std::stof(value.second);
        }
        else if (value.first == "pl_Acceleration")
        {
            CPlayer::Acceleration = std::stof(value.second);
        }
        else if (value.first == "pl_Drag")
        {
            CPlayer::Drag = std::stof(value.second);
        }
        else if (value.first == "pl_MaxSpeed")
        {
            CPlayer::MaxSpeed = std::stof(value.second);
        }
        else if (value.first == "pl_DodgeDistance")
        {
            CPlayer::DodgeDistance = std::stof(value.second);
        }
        else if (value.first == "pl_DodgeTime")
        {
            CPlayer::DodgeTime = std::stof(value.second);
        }
        else if (value.first == "pl_DodgeCooldown")
        {
            CPlayer::DodgeCooldown = std::stof(value.second);
        }
        else if (value.first == "pl_MaxRotation")
        {
            CPlayer::MaxRotation = std::stof(value.second);
        }
        else if (value.first == "pl_RotationCameraFactor")
        {
            CPlayer::RotationCameraFactor = std::stof(value.second);
        }
        else if (value.first == "pl_RotationX")
        {
            CPlayer::RotationX = std::stof(value.second);
        }
        else if (value.first == "c_FOV")
        {
            m_pMainCamera->SetFOV(DirectX::XMConvertToRadians(std::stof(value.second)));
        }
        else if (value.first == "c_NearPlane")
        {
            m_pMainCamera->SetNear(std::stof(value.second));
        }
        else if (value.first == "c_FarPlane")
        {
            m_pMainCamera->SetFar(std::stof(value.second));
        }
        else if (value.first == "c_RotationX")
        {
            CPlayer::CameraRotationX = std::stof(value.second);
        }
        else if (value.first == "c_PositionY")
        {
            CPlayer::CameraPosY = std::stof(value.second);
        }
        else if (value.first == "c_PositionMinusZ")
        {
            CPlayer::CameraMinusPosZ = std::stof(value.second);
        }
        else if (value.first == "en_FeatherProbability")
        {
            CEnvironmentCreator::FeatherSpawnProbability = std::stoi(value.second);
        }
    }
}