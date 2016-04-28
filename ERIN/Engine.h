#ifndef ENGINE_H
#define ENGINE_H

#include "Linker.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "Mesh.h"
#include "Camera.h"
#include "CustomImport.h"
#include "Player.h"
#include "GameObject.h"

#include <iostream>

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

using namespace std;

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
	bool bButtonActive = false;

	GameStateManager gameState;
	//CurrLevelManager currLevel = Level1;

	// Pause
	int pMenuOption = 0;
	// Main Menu
	int mainMenuOption = 0;

private:
	bool running;
	
	Graphics* graphics;
	GameLogic* gameLogic;
	Mesh* mesh;
	Camera* camera;
	CustomImport* customImport;

	// test input
	Player* player;
	GameObject* gameObject;
	GameObject** enemies;
};

#endif // !ENGINE_H