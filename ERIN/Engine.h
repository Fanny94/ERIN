#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "Mesh.h"
#include "Camera.h"
#include "CustomImport.h"
#include "ObjectPool.h"
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
	bool sphereToPlane(const TSphere& tSph, const Vector3& vecPoint, const Vector3& vecNormal);

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
	ObjectPool* BulletObjectpool;

	Bullet* inu;
	Bullet** bullets;

	Wall* upper_wall;
	Wall* left_wall;
	Wall* lower_wall;
	Wall* right_wall;

	// test input
	Player* player;
	Player pplay;
	GameObject* gameObject;
	GameObject** enemies;
};

#endif // !ENGINE_H