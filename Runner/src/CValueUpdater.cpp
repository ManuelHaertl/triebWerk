#include <CValueUpdater.h>
#include <CPlayer.h>

CValueUpdater::CValueUpdater()
{
}

CValueUpdater::~CValueUpdater()
{
}

void CValueUpdater::Start()
{
    m_pValues = twResourceManager->GetTWFData("values");
    int bla = 5;
}

void CValueUpdater::Update()
{
    for (auto value : m_pValues->m_ConfigurationTable)
    {

    }
}

void CValueUpdater::End()
{
}
