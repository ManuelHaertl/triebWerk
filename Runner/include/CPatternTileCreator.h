#pragma once
#include <CEngine.h>
#include <SPatternTile.h>

class CPatternTileCreator
{
public:
    std::vector<triebWerk::CEntity*> m_Entities;

private:
    static const size_t MaxObstacleHeights = 2;
    static const size_t MaxObstacleDekos = 3;
    static const size_t MaxObstacleTextures = 3;
    static const size_t MaxObstacleTextureBlendings = 3;

	const float BuildRandomMax = 5.0f;
	const float BuildRandomMin = -5.0f;

	DirectX::XMFLOAT3 LineColor = DirectX::XMFLOAT3(1, 1, 1);
	DirectX::XMFLOAT3 FaceColor = DirectX::XMFLOAT3(0, 0, 0);

    SPatternTile m_Tile;
    float m_PatternSpawnBegin;

    // Models -------------------------------------------------

    triebWerk::CMesh* m_pCheckPoint;
    triebWerk::CMesh* m_pPoints;
    triebWerk::CMesh* m_pBlock1x1;
    triebWerk::CMesh* m_pBlock2x2;

    triebWerk::CMesh* m_pObstacle05[MaxObstacleHeights];
    triebWerk::CMesh* m_pObstacle05Dekos[MaxObstacleHeights][MaxObstacleDekos];

    triebWerk::CMesh* m_pObstacle10[MaxObstacleHeights];
    triebWerk::CMesh* m_pObstacle10Dekos[MaxObstacleHeights][MaxObstacleDekos];

    triebWerk::CMesh* m_pObstacle20[MaxObstacleHeights];
    triebWerk::CMesh* m_pObstacle20Dekos[MaxObstacleHeights][MaxObstacleDekos];

    triebWerk::CMesh* m_pObstacle30[MaxObstacleHeights];
    triebWerk::CMesh* m_pObstacle30Dekos[MaxObstacleHeights][MaxObstacleDekos];

    triebWerk::CMesh* m_pShadow05;
    triebWerk::CMesh* m_pShadow10;
    triebWerk::CMesh* m_pShadow20;
    triebWerk::CMesh* m_pShadow30;

    triebWerk::CMesh* m_pMoving05Up;
    triebWerk::CMesh* m_pMoving05Down;
    triebWerk::CMesh* m_pMoving05Left;
    triebWerk::CMesh* m_pMoving05Right;
    triebWerk::CMesh* m_pMoving10Up;
    triebWerk::CMesh* m_pMoving10Down;
    triebWerk::CMesh* m_pMoving10Left;
    triebWerk::CMesh* m_pMoving10Right;

    // Textures ----------------------------------------------

    triebWerk::CTexture2D* m_pTextureObstacle[MaxObstacleTextures][MaxObstacleTextureBlendings];
	triebWerk::CTexture2D* m_pTextureEmissive[MaxObstacleTextureBlendings];
    triebWerk::CTexture2D* m_pTexturePoints;
    triebWerk::CTexture2D* m_pTextureShadow05;
    triebWerk::CTexture2D* m_pTextureShadow10;
    triebWerk::CTexture2D* m_pTextureShadow20;
    triebWerk::CTexture2D* m_pTextureShadow30;
	triebWerk::CTexture2D* m_pTextureEmissiveMoveable;
	triebWerk::CTexture2D* m_pTextureNoise;
	triebWerk::CTexture2D* m_pTextureColorNoise;

    // Shader ------------------------------------------------

    triebWerk::CMaterial* m_pMaterialStandardColor;
    triebWerk::CMaterial* m_pMaterialStandardTexture;
    triebWerk::CMaterial* m_pMaterialStandardTransparentTexture;
    triebWerk::CMaterial* m_pMaterialObstacle;
    triebWerk::CMaterial* m_pMaterialWireframe;

public:
    CPatternTileCreator();
    ~CPatternTileCreator();

    void Start();
    void CreateEntity(const SPatternTile& a_rTile, const float a_PatternSpawnBegin);

private:
    void CreateCheckpoint();
    void CreatePoints(const size_t a_Amount);
    void CreateShield();
    void CreateBlock1x1();
    void CreateBlock2x2();
    void CreateModel05x05(const bool a_Rotated);//
    void CreateModel05x10(const bool a_Rotated);//
    void CreateModel05x20(const bool a_Rotated);//
    void CreateModel05x30(const bool a_Rotated);//
    void CreateShadow05(const bool a_Rotated);
    void CreateShadow10(const bool a_Rotated);
    void CreateShadow20(const bool a_Rotated);
    void CreateShadow30(const bool a_Rotated);
    void CreateMoving05x05(); //
    void CreateMoving05x10(const bool a_Rotated);//

	float GetRandomSign();
};
