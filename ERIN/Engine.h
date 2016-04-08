#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"

class Engine: public Graphics
{
public:
	Engine();
	~Engine();

	int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow);

	HWND InitWindow(HINSTANCE hInstance);
};

#endif // !ENGINE_H