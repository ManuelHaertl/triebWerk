#include <CValueUpdater.h>

#include <CEnvironmentCreator.h>
#include <CCheckpoint.h>
#include <CDifficultyChanger.h>
#include <CGameInfo.h>
#include <CPatternManager.h>
#include <CPlayer.h>

float CPlayer::Acceleration = 250.0f;
float CPlayer::Drag = 150.0f;
float CPlayer::MaxSpeed = 30.0f;
float CPlayer::DodgeDistance = 15.0f;
float CPlayer::DodgeTime = 0.5f;
float CPlayer::DodgeCooldown = 0.5f;

float CPlayer::ShieldTime = 2.0f;
float CPlayer::ShieldCooldown = 10.0f;

float CPlayer::MaxRotation = 25.0f;
float CPlayer::RotationCameraFactor = 0.03f;

float CPlayer::RotationX = 347.0f;

float CPlayer::CameraRotationX = 4.7f;
float CPlayer::CameraPosY = 5.0f;
float CPlayer::CameraMinusPosZ = 10.0f;

int CPlayer::GodMode = 0;

int CEnvironmentCreator::FeatherSpawnProbability = 40;

float CPatternManager::SpawnDistance = 300.0f;
float CPatternManager::DeleteDistance = 10.0f;
float CPatternManager::StartFreeDistance = 100.0f;
float CPatternManager::StartTextureBlendDistance = 150.0f;
float CPatternManager::EndTextureBlendDistance = 15.0f;

float CCheckpoint::AddedMultiplier = 0.5f;
float CCheckpoint::HighestMultiplier = 5.0f;

float CDifficultyChanger::ScoreDifficulty2 = 1000.0f;
float CDifficultyChanger::ScoreDifficulty3 = 2000.0f;
float CDifficultyChanger::ScoreDifficulty4 = 3000.0f;
float CDifficultyChanger::ScoreDifficulty5 = 4000.0f;
float CDifficultyChanger::SpeedRaiseTime = 60.0f;
float CDifficultyChanger::AddedSpeed = 5.0f;
float CDifficultyChanger::MaxSpeed = 85.0f;

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

void CValueUpdater::UpdateValues()
{
    CGameInfo& gameInfo = CGameInfo::Instance();

    for (auto value : m_pValues->m_ConfigurationTable)
    {
        // Game
        if (value.first == "g_PointsPerMeter")
        {
            gameInfo.m_PointsPerMeter = std::stof(value.second);
        }

        // Player
        else if (value.first == "pl_FlySpeed")
        {
            gameInfo.m_FlySpeed = std::stof(value.second);
            gameInfo.m_StartFlySpeed = std::stof(value.second);
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
        else if (value.first == "pl_ShieldTime")
        {
            CPlayer::ShieldTime = std::stof(value.second);
        }
        else if (value.first == "pl_ShieldCooldown")
        {
            CPlayer::ShieldCooldown = std::stof(value.second);
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
        else if (value.first == "pl_GodMode")
        {
            CPlayer::GodMode = std::stoi(value.second);
        }

        // Checkpoints
        else if (value.first == "cp_AddedMultiplicator")
        {
            CCheckpoint::AddedMultiplier = std::stof(value.second);
        }
        else if (value.first == "cp_HighestMultiplicator")
        {
            CCheckpoint::HighestMultiplier = std::stof(value.second);
        }

        // Difficulty Changer
        else if (value.first == "dc_ScoreDifficulty2")
        {
            CDifficultyChanger::ScoreDifficulty2 = std::stof(value.second);
        }
        else if (value.first == "dc_ScoreDifficulty3")
        {
            CDifficultyChanger::ScoreDifficulty3 = std::stof(value.second);
        }
        else if (value.first == "dc_ScoreDifficulty4")
        {
            CDifficultyChanger::ScoreDifficulty4 = std::stof(value.second);
        }
        else if (value.first == "dc_ScoreDifficulty5")
        {
            CDifficultyChanger::ScoreDifficulty5 = std::stof(value.second);
        }
        else if (value.first == "dc_SpeedRaiseTime")
        {
            CDifficultyChanger::SpeedRaiseTime = std::stof(value.second);
        }
        else if (value.first == "dc_AddedSpeed")
        {
            CDifficultyChanger::AddedSpeed = std::stof(value.second);
        }
        else if (value.first == "dc_MaxSpeed")
        {
            CDifficultyChanger::MaxSpeed = std::stof(value.second);
        }

        // Camera
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

        // Environment
        else if (value.first == "en_FeatherProbability")
        {
            CEnvironmentCreator::FeatherSpawnProbability = std::stoi(value.second);
        }

        // Pattern Manager
        else if (value.first == "pm_StartTextureBlendDistance")
        {
            CPatternManager::StartTextureBlendDistance = std::stof(value.second);
        }
        else if (value.first == "pm_EndTextureBlendDistance")
        {
            CPatternManager::EndTextureBlendDistance = std::stof(value.second);
        }
    }
}