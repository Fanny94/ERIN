#include "Linker.h"
#include "Engine.h"
#include "Camera.h"

#include <ctime>
#include <time.h>

// link for details about the windows datatypes
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx

// Entry point for te program
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	Engine* engine = new Engine(hInstance, hPrevInstance, lpCommandLine, nCommandShow);

	const double MS_PER_UPDATE = 8;
	double previous = clock();
	double lag = 0.0;

	while (engine->getRunning()) // get engine state, e.g running / shutting down
	{
		double current = clock();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		engine->processInput();

		// TODO not working correctly, and I think I know why (mainloop and an engineloop)
		while (lag >= MS_PER_UPDATE)
		{
			engine->update(elapsed);
			lag -= MS_PER_UPDATE;
		}

		engine->render();
	}

	delete engine;

	return 0;
}