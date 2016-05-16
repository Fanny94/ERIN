#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Camera.h"
#include "CustomImport.h"
#include "ObjectPool.h"
#include "Player.h"
#include "GameObject.h"

enum GameStateManager
{
	TitleScreen,
	MainMenu,
	GameRunning,
	Pause,
	GameOver,
	HighScore,
	HelpAndOptions,
	HowToPlay,
	Controls,
	Settings,
	Credits
};

enum FloorStateManager
{
	Arctic,
	Desert,
	Jungle,
	Tropical,
	Volcanic
};

class Engine
{
public:
	Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow);
	~Engine();

	void processInput();
	void update(double deltaTimeMs);
	void render();
	void RendHUD();

	bool sphereToSphere(const TSphere& tSph1, const TSphere& tSph2);
	bool sphereToPlane(const TSphere& tSph, const Vector3& vecPoint, const Vector3& vecNormal);
	bool pointInSphere(const TSphere& tSph, const Vector3& vecPoint);

	HWND InitWindow(HINSTANCE hInstance);
	HWND wndHandle;

	bool getRunning() { return running; };

	bool aButtonActive = false;
	bool bButtonActive = false;

	bool mainMenu = true;
	bool resMenu = false;
	bool floorClear = false;

	bool printTitle = true;

	GameStateManager gameState;
	FloorStateManager floorState;

	float savedRx, savedRy;
	bool block = false;
	void Elevatorfunc();

	void rendElevator();

	// Pause
	int pMenuOption = 0;
	// Main Menu
	int mainMenuOption = 0;
	// Help & Options Menu
	int haoMenuOption = 0;
	// Result Screen
	int resMenuOption = 0;

	TSphere* Esphere;

	//Enemy counters
	int specialEnemyCount = 5;
	int enemyCount = 12;

private:
	bool running;

	float childX, childY;

	// test cooldown function
	bool ready = true;
	const float cooldown = 30.0f;
	double currentTime;
	void updateCooldown(double dt);
	void resetCooldown();

	Graphics* graphics;
	Mesh* mesh;
	Camera* camera;
	CustomImport* customImport;
	ObjectPool* Objectpool;
	GameObject* gameObject;

	Bullet* bulletptr;
	Bullet** bullets;

	Wall* upper_wall;
	Wall* left_wall;
	Wall* lower_wall;
	Wall* right_wall;

	Player* player;

	float upperWall, leftWall, lowerWall, rightWall;
	float safeZoneX, safeZoneY;
	void randomFloat();
	float Rx, Ry;

};

#endif // !ENGINE_H
