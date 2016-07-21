#pragma once
#include <CEngine.h>

class CBackground : public triebWerk::IBehaviour
{
private:
	static DirectX::XMFLOAT3 DifficultyColors[5];

	triebWerk::CEntity* m_pBGSnake;
	triebWerk::CEntity* m_pBGBassLeft;
	triebWerk::CEntity* m_pBGBassRight;

	triebWerk::CMaterial* m_pLeftMaterial;
	triebWerk::CMaterial* m_pRightMaterial;

	int m_Difficulty;

public:
	CBackground();
	~CBackground();

	void Start();
	void Update();
	void End();
};