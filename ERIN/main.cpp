void onQuit();

#include "Linker.h"
#include "Engine.h"

#include <ctime>
#include <time.h>

// link for details about the windows datatypes
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx

bool running = true;

void onQuit()
{
	running = false;
}

// Entry point for te program
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	Engine* engine = new Engine;

	const double MS_PER_UPDATE = 8;
	double previous = clock();
	double lag = 0.0;

	while (running)
	{
		double current = clock();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		engine->processInput();

		while (lag >= MS_PER_UPDATE)
		{
			engine->update(elapsed);
			lag -= MS_PER_UPDATE;
		}

		engine->render(hInstance, hPrevInstance, lpCommandLine, nCommandShow);
	}

	delete engine;

	return 0;
}