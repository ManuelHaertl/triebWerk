#pragma once
#include <CEngine.h>
#include <SPatternTile.h>

class CPatternTileCreator
{
public:
    triebWerk::CEntity* m_pFirstEntity;
    triebWerk::CEntity* m_pSecondEntity;

private:
    SPatternTile m_Tile;
    float m_PatternSpawnBegin;

    // Models -------------------------------------------------

    triebWerk::CMesh* m_pCheckPoint;
    triebWerk::CMesh* m_pPoints;
    triebWerk::CMesh* m_pBlock1x1;
    triebWerk::CMesh* m_pBlock2x2;

    triebWerk::CMesh* m_pObstacle05x05x08;
    triebWerk::CMesh* m_pObstacle05x05x08Deko1;
    triebWerk::CMesh* m_pObstacle05x05x08Deko2;
    triebWerk::CMesh* m_pObstacle05x05x08Deko3;
    triebWerk::CMesh* m_pObstacle05x05x12;
    triebWerk::CMesh* m_pObstacle05x05x12Deko1;
    triebWerk::CMesh* m_pObstacle05x05x12Deko2;
    triebWerk::CMesh* m_pObstacle05x05x12Deko3;

    triebWerk::CMesh* m_pObstacle05x10x08;
    triebWerk::CMesh* m_pObstacle05x10x08Deko1;
    triebWerk::CMesh* m_pObstacle05x10x08Deko2;
    triebWerk::CMesh* m_pObstacle05x10x08Deko3;
    triebWerk::CMesh* m_pObstacle05x10x12;
    triebWerk::CMesh* m_pObstacle05x10x12Deko1;
    triebWerk::CMesh* m_pObstacle05x10x12Deko2;
    triebWerk::CMesh* m_pObstacle05x10x12Deko3;

    triebWerk::CMesh* m_pObstacle05x20x08;
    triebWerk::CMesh* m_pObstacle05x20x08Deko1;
    triebWerk::CMesh* m_pObstacle05x20x08Deko2;
    triebWerk::CMesh* m_pObstacle05x20x08Deko3;
    triebWerk::CMesh* m_pObstacle05x20x12;
    triebWerk::CMesh* m_pObstacle05x20x12Deko1;
    triebWerk::CMesh* m_pObstacle05x20x12Deko2;
    triebWerk::CMesh* m_pObstacle05x20x12Deko3;

    triebWerk::CMesh* m_pObstacle05x30x08;
    triebWerk::CMesh* m_pObstacle05x30x08Deko1;
    triebWerk::CMesh* m_pObstacle05x30x08Deko2;
    triebWerk::CMesh* m_pObstacle05x30x08Deko3;
    triebWerk::CMesh* m_pObstacle05x30x12;
    triebWerk::CMesh* m_pObstacle05x30x12Deko1;
    triebWerk::CMesh* m_pObstacle05x30x12Deko2;
    triebWerk::CMesh* m_pObstacle05x30x12Deko3;

    // Textures ----------------------------------------------

    triebWerk::CTexture2D* m_pTextureObstacle;

    // Shader ------------------------------------------------

    triebWerk::CMaterial* m_pMaterialStandardColor;
    triebWerk::CMaterial* m_pMaterialStandardTexture;

public:
    CPatternTileCreator();
    ~CPatternTileCreator();

    void CreateEntity(const SPatternTile& a_rTile, const float a_PatternSpawnBegin);

private:
    void CreateCheckpoint();
    void CreatePoints();
    void CreateShield();
    void CreateBlock1x1();
    void CreateBlock2x2();
    void CreateModel05x05();
    void CreateModel05x05Flipped();
    void CreateModel05x10();
    void CreateModel05x10Flipped();
    void CreateModel05x20();
    void CreateModel05x20Flipped();
    void CreateModel05x30();
    void CreateModel05x30Flipped();

};
