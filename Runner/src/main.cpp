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

        if (twKeyboard.IsState(triebWerk::EKey::A, triebWerk::EButtonState::Down))
            std::cout << "Keyboard A" << std::endl;

        if (twMouse.IsState(triebWerk::EMouseButton::Left, triebWerk::EButtonState::Down))
            std::cout << "Mouse Left" << std::endl;

        if (twGamepad.IsState(triebWerk::EGamepadButton::A, triebWerk::EButtonState::Down, 0))
            std::cout << "A down" << std::endl;
    }

    twEngine.Shutdown();
    return 0;
}