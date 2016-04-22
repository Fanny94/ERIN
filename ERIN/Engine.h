#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Camera.h"

// test input
#include "Player.h"
#include "GameObject.h"

class Engine
{
public:
	Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow);
	~Engine();

	void processInput();
	void update(double deltaTimeMs);
	void render();

	HWND InitWindow(HINSTANCE hInstance);
	HWND wndHandle;

	bool getRunning() { return running; };

private:
	bool running;
	
	Graphics* graphics;
	GameLogic* gameLogic;
	AssetManager* assetManager;
	Mesh* mesh;
	Camera* camera;

	// test input
	Player* player;
	GameObject* gameObject;
};

#endif // !ENGINE_H