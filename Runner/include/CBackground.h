#pragma once
#include <CEngine.h>

class CBackground : public triebWerk::IBehaviour
{
private:
	triebWerk::CEntity* m_pBGSnake;
	triebWerk::CEntity* m_pSnakeFeather;
	triebWerk::CEntity* m_pBGBassLeft;
	triebWerk::CEntity* m_pBGBassRight;

	triebWerk::CMaterial* m_pLeftMaterial;
	triebWerk::CMaterial* m_pRightMaterial;
	triebWerk::CMaterial* m_pSnakeFeatherMaterial;
	triebWerk::CMaterial* m_pSnakeHeadMaterial;

	int m_Difficulty;
	float m_Multiplier;

	//Circle Lerp Stuff
	bool m_IsLerping;
	float m_LerpValue;
	int m_ToLerpIndex;

	//Multiplier Lerp Stuff
	bool m_IsMultiLerping;
	float m_MultiLerpValue;
	int m_ToMultiLerpIndex;


	//Color Stuff
	DirectX::XMFLOAT4 m_StartColor = DirectX::XMFLOAT4(0.0, 0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT4 m_LerpToColor;
	static const int ToLerpColorsCount = 2;
	static DirectX::XMFLOAT4 ToLerpColors[ToLerpColorsCount];
	bool m_LerpColors;
	float m_LerpColorToValue;
	float m_LerpColorValue;

public:
	CBackground();
	~CBackground();

	void Start();
	void Update();
	void End();

private:
	void UpdateMultiplier();
	void UpdateDifficultyCircles();
	void UpdateColor();
	void LerpColor();

};