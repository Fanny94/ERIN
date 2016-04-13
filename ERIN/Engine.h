#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "AssetManager.h"
#include "Camera.h"

// test input
#include "GameObject.h"

class Engine
{
public:
	Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow);
	~Engine();

	void processInput();
	void update(int deltaTimeMs);
	void render();

	HWND InitWindow(HINSTANCE hInstance);
	HWND wndHandle;

	bool getRunning() { return running; };
private:
	bool running;

	Graphics* graphics;
	GameLogic* gameLogic;
	AssetManager* assetManager;
	Camera* camera;

	// test input
	GameObject* gameObject;
};

#endif // !ENGINE_H