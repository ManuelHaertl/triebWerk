#pragma once
#include <CEngine.h>
#include <IMenu.h>

class COptionsMenu : public IMenu
{
private:
    enum EResolutions
    {
        x800x450 = 0,
        x1024x576 = 1,
        x1280x720 = 2,
        x1600x900 = 3,
        x1900x1024 = 4,
        x1920x1080 = 5,
    };

private:
    const size_t MaxResolutions = 6;
    const size_t MaxIndex = 6;
    const float SoundMoveSpeed = 0.3f;

    triebWerk::CUIEntity* m_pFieldBG;

    triebWerk::CUIEntity* m_pArrowLeft;
    triebWerk::CUIEntity* m_pArrowRight;
    triebWerk::CUIEntity* m_pResolutionBox;

    triebWerk::CUIEntity* m_pFullscreen;
    triebWerk::CUIEntity* m_pFullscreenCross;
    triebWerk::CUIEntity* m_pVSync;
    triebWerk::CUIEntity* m_pVSyncCross;

    triebWerk::CUIEntity* m_pMasterVolume;
    triebWerk::CUIEntity* m_pMasterVolumeBar;
    triebWerk::CUIEntity* m_pMasterVolumeSelected;
    triebWerk::CUIEntity* m_pBGMVolume;
    triebWerk::CUIEntity* m_pBGMVolumeBar;
    triebWerk::CUIEntity* m_pBGMVolumeSelected;
    triebWerk::CUIEntity* m_pSFXVolume;
    triebWerk::CUIEntity* m_pSFXVolumeBar;
    triebWerk::CUIEntity* m_pSFXVolumeSelected;

    triebWerk::CUIEntity* m_pFontResolution;
    triebWerk::CUIEntity* m_pFontCurrentResolution;
    triebWerk::CUIEntity* m_pFontFullscreen;
    triebWerk::CUIEntity* m_pFontVSync;
    triebWerk::CUIEntity* m_pFontMasterVolume;
    triebWerk::CUIEntity* m_pFontBGMVolume;
    triebWerk::CUIEntity* m_pFontSFXVolume;

    // Textures
    triebWerk::CTexture2D* m_pTexturesCheckbox[3];
    triebWerk::CTexture2D* m_pTexturesArrowsLeft[2];
    triebWerk::CTexture2D* m_pTexturesArrowsRight[2];

    // --------------------------------------------------------

    bool m_UpdateGraphics;
    int m_SelectedIndex;
    int m_PressedValue;

    // Current Settings
    int m_CurrentResolution;
    int m_CurrentFullscreen;
    int m_CurrentVSync;
    float m_CurrentMasterVolume;
    float m_CurrentBGMVolume;
    float m_CurrentSFXVolume;


public:
    COptionsMenu();
    ~COptionsMenu();

    void Start() final;
    void Update(const SUIInput& a_rInput) final;
    void End() final;

private:
    void GetOptions();
    void SaveOptions();
    void CheckInput(const SUIInput& a_rInput);
    void UpdateGraphics();
    size_t GetCurrentWidth();
    size_t GetCurrentHeight();
};