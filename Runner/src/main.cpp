#include <iostream>
#include <CEngine.h>

int main()
{
    triebWerk::CEngine::Instance().Initialize();

    while (42)
    {
        triebWerk::CEngine::Instance().Run();
    }

    triebWerk::CEngine::Instance().Shutdown();
}