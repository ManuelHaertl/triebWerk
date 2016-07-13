#pragma once
#include <CEngine.h>

class CDebugScene : public triebWerk::IScene
{
private:
    DirectX::XMVECTOR m_Position;

public:
    CDebugScene();
    ~CDebugScene();

    void Start();
    void Update();
    void End();
    void Resume();
    void Pause();

private:
    void CreatePlayground();
	void CreateDebugFont();
	void CreateMultipleObjects();
    void ResetCamera();
};