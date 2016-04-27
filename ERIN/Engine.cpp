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

		switch (gameState)
		{
		case TitleScreen:
			if (this->player->input->State._buttons[GamePad_Button_START] == true)
			{
				cout << "Main Menu" << endl << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				gameState = MainMenu;
			}
			break;

		case MainMenu:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (mainMenuOption == 1)
				{
					mainMenuOption = 0;
					cout << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				}
				else if (mainMenuOption == 3)
				{
					mainMenuOption = 2;
					cout << "Main Menu Option " << mainMenuOption << " (Help & Options)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (mainMenuOption == 0)
				{
					mainMenuOption = 1;
					cout << "Main Menu Option " << mainMenuOption << " (High Score)" << endl;
				}
				else if (mainMenuOption == 2)
				{
					mainMenuOption = 3;
					cout << "Main Menu Option " << mainMenuOption << " (Quit)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (mainMenuOption == 2)
				{
					mainMenuOption = 0;
					cout << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				}
				else if (mainMenuOption == 3)
				{
					mainMenuOption = 1;
					cout << "Main Menu Option " << mainMenuOption << " (High Score)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (mainMenuOption == 0)
				{
					mainMenuOption = 2;
					cout << "Main Menu Option " << mainMenuOption << " (Help & Options)" << endl;
				}
				else if (mainMenuOption == 1)
				{
					mainMenuOption = 3;
					cout << "Main Menu Option " << mainMenuOption << " (Quit)" << endl;
				}
			}

			// If accept
			if (this->player->input->State._buttons[GamePad_Button_A] == true)
			{
				if (mainMenuOption == 0)
				{
					cout << "Game Running" << endl;
					gameState = GameRunning;
				}
				else if (mainMenuOption == 1)
				{
					cout << "High Score" << endl;
					//gameState = HighScore;
				}
				else if (mainMenuOption == 2)
				{
					cout << "Help & Options" << endl;
					//gameState = HelpAndOptions;
				}
				else if (mainMenuOption == 3)
					this->running = false;
			}
			break;
		case GameRunning:
			if (this->player->input->State._buttons[GamePad_Button_START] == true)
			{
				cout << "Game Paused" << endl << "Pause Menu Option " << pMenuOption << " (Resume)" << endl;
				gameState = Pause;
			}

			// Dpad camera movement
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (gameState == GameRunning)
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
			break;

		case Pause:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (pMenuOption == 1)
				{
					pMenuOption = 0;
					cout << "Pause Menu Option " << pMenuOption << " (Resume)" << endl;
				}
				else if (pMenuOption == 3)
				{
					pMenuOption = 2;
					cout << "Pause Menu Option " << pMenuOption << " (Help & Options)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (pMenuOption == 0)
				{
					pMenuOption = 1;
					cout << "Pause Menu Option " << pMenuOption << " (High Score)" << endl;
				}
				else if (pMenuOption == 2)
				{
					pMenuOption = 3;
					cout << "Pause Menu Option " << pMenuOption << " (Main Menu)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (pMenuOption == 2)
				{
					pMenuOption = 0;
					cout << "Pause Menu Option " << pMenuOption << " (Resume)" << endl;
				}
				else if (pMenuOption == 3)
				{
					pMenuOption = 1;
					cout << "Pause Menu Option " << pMenuOption << " (High Score)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (pMenuOption == 0)
				{
					pMenuOption = 2;
					cout << "Pause Menu Option " << pMenuOption << " (Help & Options)" << endl;
				}
				else if (pMenuOption == 1)
				{
					pMenuOption = 3;
					cout << "Pause Menu Option " << pMenuOption << " (Main Menu)" << endl;
				}
			}

			// If accept
			if (this->player->input->State._buttons[GamePad_Button_A] == true)
			{
				if (pMenuOption == 0)
				{
					cout << "Game Running" << endl;
					gameState = GameRunning;
				}
				else if (pMenuOption == 1)
				{
					cout << "High Score" << endl;
					//gameState = HighScore;
				}
				else if (pMenuOption == 2)
				{
					cout << "Help & Options" << endl;
					//gameState = HelpAndOptions;
				}
				else if (pMenuOption == 3)
				{
					cout << "Main Menu" << endl;
					gameState = MainMenu;
				}
			}
			break;
		case HighScore:
			break;
		case HelpAndOptions:
			break;
		}

		if (this->player->input->State._buttons[GamePad_Button_Y] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_X] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_B] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_A] == true)
		{
		}

		if (this->player->input->State._buttons[GamePad_Button_START] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_BACK] == true)
		{
			cout << "Shutting down game!" << endl;
			this->running = false;
		}

		// BUMPERS & TRIGGERS
		if (this->player->input->State._buttons[GamePad_Button_LEFT_THUMB] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_THUMB] == true)
		{
		}

		if (this->player->input->State._buttons[GamePad_Button_LEFT_SHOULDER] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_SHOULDER] == true)
		{
		}

		// DPAD
		if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
		{
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
		//TitleScreen->render();			// Example of how to render the title screen

		for (static bool first = true; first; first = false)
		{
			cout << "Title Screen" << endl;
		}
		break;
	case MainMenu:
		//MainMenu->render();				// Example of how to render the main menu
		break;
	case GameRunning:
		//GameLogic->levelHandler();		// Example of how to start a level
		
		player->update(deltaTimeMs);
		gameObject->update(deltaTimeMs);

		render();
		break;
	case Pause:
		break;
	}
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