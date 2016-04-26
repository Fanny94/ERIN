#include "Engine.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

using namespace std;

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->running = true;
	this->camera = new Camera();
	this->graphics = new Graphics();

	// test input
	this->gameObject = new GameObject("triangle", 0.0f, 0.0f, 0.5f);
	this->player = new Player("player", 1.0f, 0.0f, 0.0f);

	//create window
	wndHandle = InitWindow(hInstance);

	if (!camera->InitDirectInput(hInstance))
	{
		MessageBox(0, "Direct Input Initialization - Failed", "Error", MB_OK);

		return;
	}

	graphics->camera = camera;

	// window is valid
	if (wndHandle)
	{
		// Create SwapChain, Device and Device Context 
		graphics->CreateDirect3DContext(wndHandle);

		graphics->SetViewport(); // Set Viewport

		graphics->CreateShaders();

		graphics->CreateTriangle(gameObject->triangle);

		if (!graphics->LoadObjModel(L"C:/Users/vilu14/Documents/GitHub/ERIN/Cube.obj", &graphics->meshVertBuff, &graphics->meshIndexBuff, graphics->meshSubsetIndexStart, graphics->meshSubsetTexture, graphics->material, graphics->meshSubsets, true, false))
		{
			return;
		}
		
		/*if (!graphics->LoadObjModel(L"C:/Users/Marc/Documents/Visual Studio 2015/Projects/ERIN/Cube.obj", &graphics->meshVertBuff, &graphics->meshIndexBuff, graphics->meshSubsetIndexStart, graphics->meshSubsetTexture, graphics->material, graphics->meshSubsets, true, false))

		{
			return;
		}
		*/
		graphics->CreateConstantBuffer();

		ShowWindow(wndHandle, nCommandShow);

	}
}

Engine::~Engine()
{
	delete this->graphics;
	delete this->player;
	delete this->gameObject;
	delete this->camera;
}

void Engine::processInput()
{

	player->input->update(); // test object, should be done for all objects

	if (player->input->isConnected())
	{
		player->playerInput();

		if (this->player->input->State._buttons[GamePad_Button_Y] == true)
		{
			switch (gameState)
				case Pause:
					this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_X] == true)
		{
			switch (gameState)
				case Pause:
					this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_B] == true)
		{
			switch (gameState)
			{
			case Pause:
				this->running = false;
				break;
			}
		}
		if (this->player->input->State._buttons[GamePad_Button_A] == true)
		{
			switch (gameState)
			{
			case MainMenu:
				gameState = GameRunning;
				break;
			case Pause:
				gameState = GameRunning;
				break;
			}
		}

		if (this->player->input->State._buttons[GamePad_Button_START] == true)
		{
			switch (gameState)
			{
			case TitleScreen:
				gameState = MainMenu;
				break;
			case GameRunning:
				gameState = Pause;
				break;
			}
		}
		if (this->player->input->State._buttons[GamePad_Button_BACK] == true)
		{
			this->running = false;
		}

		if (this->player->input->State._buttons[GamePad_Button_LEFT_THUMB] == true)
		{
			switch (gameState)
			{
			case Pause:
				this->running = false;
			}
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_THUMB] == true)
		{
			switch (gameState)
			{
			case Pause:
				switch (gameState)
				{
				case Pause:
					this->running = false;
				}
			}
		}

		if (this->player->input->State._buttons[GamePad_Button_LEFT_SHOULDER] == true)
		{
			switch (gameState)
			{
			case Pause:
				this->running = false;
			}
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_SHOULDER] == true)
		{
			switch (gameState)
			{
			case GameRunning:
				switch (currLevel)
				{
				case Level1:
					currLevel = Level2;
					break;
				}
				break;
			}
		}

		// Dpad camera movement
		if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
		{
			if(gameState == GameRunning)
				this->camera->cameraMoveLeft();
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
		{
			if (gameState == GameRunning)
				this->camera->cameraMoveRight();
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
		{
			if (gameState == GameRunning)
				this->camera->cameraMoveUp();
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
		{
			if (gameState == GameRunning)
				this->camera->cameraMoveDown();
		}
	}
}

void Engine::update(double deltaTimeMs)
{
	double deltaTimeS;
	deltaTimeS = deltaTimeMs / 1000;
	// update code
	// example physics calculation using delta time:
	// object.x = object.x + (object.speed * deltaTimeS);

	//printf("Elapsed time: %fS.\n", deltaTimeS);

	switch (gameState)
	{
	case TitleScreen:
		cout << "Title Screen" << endl;
		// Title Screen
		//TitleScreen->render();	// Example of how to render the title screen
		//gameState = GameRunning;
		break;
	case MainMenu:
		cout << "Main Menu" << endl;
		// Main Menu
		//MainMenu->render();		// Example of how to render the main menu
		break;
	case GameRunning:
		cout << "Game running | ";
		switch (currLevel)
		{
		case Level1:
			cout << "Level 1" << endl;
			break;
		case Level2:
			cout << "Level 2" << endl;
			break;
		}
		// Gameplay loop
		//GameLogic->startGame;		// Example of how to start a level
		render();
		break;
	case Pause:
		cout << "Game Paused" << endl;
		// Pause Menu
		//GameLogic->Sleep();		// Example of how to pause the game
		break;
	}

	player->update(deltaTimeMs);
	gameObject->update(deltaTimeMs);
}

void Engine::render()
{
	graphics->UpdateConstantBuffer();

	/*

	player shader;
	player rend;
	player shader delete;

	for (int i = 0; i < assetmanager->numberOfMeshes; i++)
	{
		graphics->CreateShaders("filename");
		graphics->RendFBX(x);
		graphics->DeleteShader();
	}

	*/

	graphics->Render();
	graphics->RendPlayer(*player->objectMatrix);
	graphics->RendPlayer(*gameObject->objectMatrix);
	

	camera->InitCamera();

	// Switch front- and back-buffer
	graphics->get_gSwapChain()->Present(0, 0);
}

HWND Engine::InitWindow(HINSTANCE hInstance)
{
	// Every window created must belkong to a class

	WNDCLASSEX winClassInfo = { 0 };
	winClassInfo.cbSize = sizeof(WNDCLASSEX);
	winClassInfo.style = CS_HREDRAW | CS_VREDRAW;
	winClassInfo.lpfnWndProc = WndProc; // This function is called for events
	winClassInfo.hInstance = hInstance;
	winClassInfo.lpszClassName = "WindowClass";

	if (!RegisterClassEx(&winClassInfo))
		return false;

	// the window size
	RECT rc = { 0, 0, (LONG) graphics->get_gWidth() , (LONG) graphics->get_gHeight() };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND handle = CreateWindow(
		"WindowClass",	// Class name
		"ERIN",			// Window name
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return handle;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//call the default handler function if w do not handle the message here 
	return DefWindowProc(hWnd, message, wParam, lParam);
}