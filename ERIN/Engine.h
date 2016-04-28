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

	HWND InitWindow(HINSTANCE hInstance);
	HWND wndHandle;

	bool getRunning() { return running; };
	bool aButtonActive = false;

	GameStateManager gameState = TitleScreen;
	//CurrLevelManager currLevel = Level1;

	// Pause
	int pMenuOption = 0;
	// Main Menu
	int mainMenuOption = 0;

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