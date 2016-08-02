#pragma once
#include <CEngine.h>

class CRoadBorder : public triebWerk::IBehaviour
{
private:

	const float m_DistanceToShow = 6.0f;

	DirectX::XMFLOAT4 m_Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	triebWerk::CEntity* m_pRightBorder;

	triebWerk::CMaterial* m_pMaterialRight;
	triebWerk::CMaterial* m_pMaterialLeft;


public:
	CRoadBorder();
	~CRoadBorder();

	void Start();
	void Update();
	void End();


private:
};