#pragma once
#include <CEngine.h>
#include <SPatternTile.h>

class CPatternTileCreator
{
private:
    SPatternTile m_Tile;
    float m_PatternSpawnBegin;

public:
    CPatternTileCreator();
    ~CPatternTileCreator();

    triebWerk::CEntity* CreateEntity(const SPatternTile& a_rTile, const float a_PatternSpawnBegin);

private:
    triebWerk::CEntity* CreateCheckpoint();
    triebWerk::CEntity* CreatePoints();
    triebWerk::CEntity* CreateShield();
    triebWerk::CEntity* CreateBlock1x1();
    triebWerk::CEntity* CreateBlock2x2();
    triebWerk::CEntity* CreateModel05x05();
    triebWerk::CEntity* CreateModel05x05Flipped();
    triebWerk::CEntity* CreateModel05x10();
    triebWerk::CEntity* CreateModel05x10Flipped();
    triebWerk::CEntity* CreateModel05x20();
    triebWerk::CEntity* CreateModel05x20Flipped();
    triebWerk::CEntity* CreateModel05x30();
    triebWerk::CEntity* CreateModel05x30Flipped();
};
