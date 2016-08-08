#pragma once
#include <CEngine.h>

class CIntroScene : public triebWerk::IScene
{
public:
    static float GALogoTime;
    static float TWLogoTime;

private:
    triebWerk::CUIEntity* m_pGALogo;
    triebWerk::CUIEntity* m_pTWLogo;

    bool m_HasShown;
    bool m_HasLoaded;
    bool m_HasShownGALogo;
    float m_CurrentTime;

public:
    CIntroScene();
    ~CIntroScene();

    void Start() final;
    void Update() final;
    void End() final;
};
