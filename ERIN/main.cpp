#include "Linker.h"
#include "Engine.h"
#include "Camera.h"

// memory leaks
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// time
#include <ctime>
#include <time.h>

// link for details about the windows datatypes
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx

// Entry point for the program
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg = { 0 };

	// create console window
	AllocConsole();

	CoInitializeEx(NULL, 0);
	CoInitialize(NULL);

	// if you get an error because of freopen
	// Go to proporties and write _CRT_SECURE_NO_WARNINGS in preprocessor definitions 
	freopen("CONOUT$", "w", stdout);

	Engine* engine = new Engine(hInstance, hPrevInstance, lpCommandLine, nCommandShow);

	const double MS_PER_UPDATE = 8;
	double previous = clock();
	double lag = 0.0;

	while (WM_QUIT != msg.message && engine->getRunning())
	{
		// read messages
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}

		else
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

			engine->render();
		}
	}

	fclose(stdout);
	delete engine;

	return 0;
}