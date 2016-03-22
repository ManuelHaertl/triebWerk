#include <iostream>
#include <CEngine.h>

int main()
{
	if (Engine.Initialize() == false)
	{
		Engine.Shutdown();
		return 0;
	}

	bool run = true;
	while (run == true)
	{
		run = Engine.Run();
	}

	Engine.Shutdown();
	return 0;
}