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
//#include "GameObject.h"

enum GameStateManager
{
	TitleScreen,
	MainMenu,
	GameRunning,
	Pause,
	GameOver,
	HighScore,
	HelpAndOptions
};

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
	bool pointInSphere(const TSphere& tSph, const Vector3& vecPoint);

	HWND InitWindow(HINSTANCE hInstance);
	HWND wndHandle;

	bool getRunning() { return running; };

	bool aButtonActive = false;
	bool bButtonActive = false;

	GameStateManager gameState;

	// Pause
	int pMenuOption = 0;
	// Main Menu
	int mainMenuOption = 0;

private:
	bool running;

	// test cooldown function
	bool ready;
	const float cooldown = 1.0f;
	double currentTime;
	void updateCooldown(double dt);
	// test cooldown function #end

	Graphics* graphics;
	GameLogic* gameLogic;
	Mesh* mesh;
	Camera* camera;
	CustomImport* customImport;
	ObjectPool* Objectpool;

	Bullet* bulletptr;
	Bullet** bullets;

	Wall* upper_wall;
	Wall* left_wall;
	Wall* lower_wall;
	Wall* right_wall;

	Player* player;

	TriangleVertex* triangle;
};

#endif // !ENGINE_H