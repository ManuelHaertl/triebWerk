#include <CValueUpdater.h>

#include <CEnvironmentCreator.h>
#include <CCheckpoint.h>
#include <CDifficultyChanger.h>
#include <CGameInfo.h>
#include <CGameScene.h>
#include <CPatternManager.h>
#include <CPlayer.h>
#include <CPoints.h>
#include <CPostEffects.h>

float CGameScene::PointsPerMeter = 0.5f;

float CPlayer::Acceleration = 250.0f;
float CPlayer::Drag = 150.0f;
float CPlayer::MaxSpeed = 30.0f;

float CPlayer::MaxResource = 10.0f;
float CPlayer::ResourcePerSecond = 1.0f;

float CPlayer::FullControlSpeed = 100.0f;
float CPlayer::FullControlCost = 2.0f;

float CPlayer::BoostSpeed = 15.0f;
float CPlayer::BoostCost = 2.0f;

float CPlayer::MaxRotation = 25.0f;
float CPlayer::RotationCameraFactor = 0.03f;

float CPlayer::RotationX = 347.0f;

float CPlayer::CameraRotationX = 4.7f;
float CPlayer::CameraPosY = 5.0f;
float CPlayer::CameraMinusPosZ = 10.0f;

int CPlayer::GodMode = 0;

int CEnvironmentCreator::FeatherSpawnProbability = 40;
float CEnvironmentCreator::SnakeRotateSpeed1 = -3.0f;
float CEnvironmentCreator::SnakeRotateSpeed2 = -2.0f;
float CEnvironmentCreator::SnakeRotateSpeed3 = -1.0f;

float CPatternManager::SpawnDistance = 300.0f;
float CPatternManager::StartFreeDistance = 150.0f;
float CPatternManager::StartTextureBlendDistance = 200.0f;
float CPatternManager::EndTextureBlendDistance = 15.0f;
float CPatternManager::StartBuildDistance = 200.0f;
float CPatternManager::EndBuildDistance = 100.0f;
float CPatternManager::BuildStrength = 10.0f;

float CCheckpoint::AddedMultiplier = 0.5f;
float CCheckpoint::HighestMultiplier = 5.0f;

float CDifficultyChanger::ScoreDifficulty2 = 1000.0f;
float CDifficultyChanger::ScoreDifficulty3 = 2000.0f;
float CDifficultyChanger::ScoreDifficulty4 = 3000.0f;
float CDifficultyChanger::ScoreDifficulty5 = 4000.0f;
float CDifficultyChanger::SpeedRaiseTime = 60.0f;
float CDifficultyChanger::AddedSpeed = 5.0f;
float CDifficultyChanger::MaxSpeed = 85.0f;

int CPoints::Points[3] = { 10, 20, 50 };

float CPostEffects::ChromaticAberrationStrength = 0.8f;
float CPostEffects::CheckpointEffectCollectedLength = 1.5f;
float CPostEffects::CheckpointEffectPassedLength = 1.5f;
float CPostEffects::FullControlEffectStrengthMin = 2.0f;
float CPostEffects::FullControlEffectStrengthMax = 5.0f;
float CPostEffects::BoostEffectStrength = 2.0f;
float CPostEffects::GameStartTime = 2.0f;
float CPostEffects::GameStartLDEffectStrength = 15.0f;
float CPostEffects::GameStartCAEffectStrength = 15.0f;
float CPostEffects::GameStartRIBeginEffectStrength = 500.0f;
float CPostEffects::GameStartRIEndEffectStrength = 3.0f;

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
            CGameScene::PointsPerMeter = std::stof(value.second);
        }

        // Player
        else if (value.first == "pl_FlySpeed")
        {
            gameInfo.m_FlyStandardSpeed = std::stof(value.second);
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
        else if (value.first == "pl_MaxResource")
        {
            CPlayer::MaxResource = std::stof(value.second);
        }
        else if (value.first == "pl_ResourcePerSecond")
        {
            CPlayer::ResourcePerSecond = std::stof(value.second);
        }
        else if (value.first == "pl_FullControlSpeed")
        {
            CPlayer::FullControlSpeed = std::stof(value.second);
        }
        else if (value.first == "pl_FullControlCost")
        {
            CPlayer::FullControlCost = std::stof(value.second);
        }
        else if (value.first == "pl_FullControlEffectStrengthMin")
        {
            CPostEffects::FullControlEffectStrengthMin = std::stof(value.second);
        }
        else if (value.first == "pl_FullControlEffectStrengthMax")
        {
            CPostEffects::FullControlEffectStrengthMax = std::stof(value.second);
        }
        else if (value.first == "pl_BoostSpeed")
        {
            CPlayer::BoostSpeed = std::stof(value.second);
        }
        else if (value.first == "pl_BoostCost")
        {
            CPlayer::BoostCost = std::stof(value.second);
        }
        else if (value.first == "pl_BoostEffectStrength")
        {
            CPostEffects::BoostEffectStrength = std::stof(value.second);
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

        // Menu
        else if (value.first == "me_GameStartTime")
        {
            CPostEffects::GameStartTime = std::stof(value.second);
        }
        else if (value.first == "me_GameStartLDEffectStrength")
        {
            CPostEffects::GameStartLDEffectStrength = std::stof(value.second);
        }
        else if (value.first == "me_GameStartCAEffectStrength")
        {
            CPostEffects::GameStartCAEffectStrength = std::stof(value.second);
        }
        else if (value.first == "me_GameStartRIBeginEffectStrength")
        {
            CPostEffects::GameStartRIBeginEffectStrength = std::stof(value.second);
        }
        else if (value.first == "me_GameStartRIEEndffectStrength")
        {
            CPostEffects::GameStartRIEndEffectStrength = std::stof(value.second);
        }

        // PostEffects
        else if (value.first == "pe_ChromaticAberrationStrength")
        {
            CPostEffects::ChromaticAberrationStrength = std::stof(value.second);
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
        else if (value.first == "cp_EffectCollectedLength")
        {
            CPostEffects::CheckpointEffectCollectedLength = std::stof(value.second);
        }
        else if (value.first == "cp_EffectPassedLength")
        {
            CPostEffects::CheckpointEffectPassedLength = std::stof(value.second);
        }

        // Points
        else if (value.first == "po_Amount1")
        {
            CPoints::Points[0] = std::stoi(value.second);
        }
        else if (value.first == "po_Amount2")
        {
            CPoints::Points[1] = std::stof(value.second);
        }
        else if (value.first == "po_Amount3")
        {
            CPoints::Points[2] = std::stof(value.second);
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
        else if (value.first == "en_SnakeRotateSpeed1")
        {
            CEnvironmentCreator::SnakeRotateSpeed1 = std::stoi(value.second);
        }
        else if (value.first == "en_SnakeRotateSpeed2")
        {
            CEnvironmentCreator::SnakeRotateSpeed2 = std::stoi(value.second);
        }
        else if (value.first == "en_SnakeRotateSpeed3")
        {
            CEnvironmentCreator::SnakeRotateSpeed3 = std::stoi(value.second);
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
		else if (value.first == "pm_StartBuildDistance")
		{
			CPatternManager::StartBuildDistance = std::stof(value.second);
		}
		else if (value.first == "pm_EndBuildDistance")
		{
			CPatternManager::EndBuildDistance = std::stof(value.second);
		}
		else if (value.first == "pm_BuildStrength")
		{
			CPatternManager::BuildStrength = std::stof(value.second);
		}
    }
}