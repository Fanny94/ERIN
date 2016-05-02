#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "Mesh.h"
#include "Camera.h"
#include "CustomImport.h"

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

	bool sphereToSphere(const TSphere& tSph1, const TSphere& tSph2);

	HWND InitWindow(HINSTANCE hInstance);
	HWND wndHandle;

	bool getRunning() { return running; };

private:
	bool running;

	Graphics* graphics;
	GameLogic* gameLogic;
	Mesh* mesh;
	Camera* camera;
	CustomImport* customImport;
	ObjectPool* objectpool;

	// test input
	Player* player;
	GameObject* gameObject;
	GameObject** enemies;
};

#endif // !ENGINE_H