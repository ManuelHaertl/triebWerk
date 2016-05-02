#include <CGameScene.h>

CGameScene::CGameScene() :
    m_pPattern(nullptr),
    m_PatternCount(0)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Start()
{
    LoadAllPattern();

    auto test1 = twWorld->CreateEntity();
    test1->SetBehaviour(new CPlayer());
    twWorld->AddEntity(test1);
}

void CGameScene::Update()
{
}

void CGameScene::End()
{
    if (m_pPattern != nullptr)
    {
        delete[] m_pPattern;
    }
}

void CGameScene::LoadAllPattern()
{
    CPatternLoader patternLoader;
    patternLoader.LoadPattern();

    m_pPattern = patternLoader.GetPattern();
    m_PatternCount = patternLoader.GetPatternCount();
}
