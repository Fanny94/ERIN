#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "AssetManager.h"
#include "Camera.h"

class Engine
{
public:
	Engine();
	~Engine();

	void processInput();
	void update(int deltaTimeMs);
	int render(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow);

	HWND InitWindow(HINSTANCE hInstance);
	HWND wndHandle;

private:
	bool running;
	Graphics* graphics;
	GameLogic* gameLogic;
	AssetManager* assetManager;
	Camera* camera;
};

#endif // !ENGINE_H