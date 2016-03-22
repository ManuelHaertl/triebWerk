#include <iostream>
#include <CEngine.h>

int main()
{
    if (twEngine.Initialize() == false)
    {
        twEngine.Shutdown();
        return 0;
    }

    bool run = true;
    while (run == true)
    {
        run = twEngine.Run();
        std::cout << twTime->GetDeltaTime() << std::endl;
    }

    twEngine.Shutdown();
    return 0;
}