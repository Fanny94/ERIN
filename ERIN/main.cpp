#include "Linker.h"
#include "Engine.h"

//link for details about the windows datatypes
//https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx

//Entry point for te program
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	Engine* engine = new Engine;

	engine->render(hInstance, hPrevInstance, lpCommandLine, nCommandShow);

	delete engine;

	return 0;
}