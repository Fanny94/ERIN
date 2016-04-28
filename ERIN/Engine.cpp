#include "Engine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->running = true;

	this->gameState = TitleScreen;
	cout << "Title Screen" << endl;

	this->camera = new Camera();
	this->graphics = new Graphics();
	this->customImport = new CustomImport();

	this->player = new Player("player", 1.0f, 0.0f, 0.0f);

	// creating enemies
	/*size_t size = 10;
	vector<GameObject> Vector_enemies(size);*/
	//vector<GameObject> stageObjects;

	/*this->gameObject = new GameObject(0, "triangle", 0.0f, 0.0f, 0.5f, true);
	Vector_enemies.push_back(*gameObject);
	delete gameObject;
	Vector_enemies.clear();*/

	this->enemies = new GameObject*[5];
	this->enemies[0] = new GameObject(1, "enemy1", 5.0f, 0.0f, 0.1f, true);
	this->enemies[1] = new GameObject(2, "enemy2", 0.0f, 5.0f, 0.1f, true);
	this->enemies[2] = new GameObject(3, "enemy3", -5.0f, 0.0f, 0.1f, true);
	this->enemies[3] = new GameObject(4, "enemy4", 0.0f, -5.0f, 0.1f, true);

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

		graphics->CreateTriangle(enemies[0]->triangle);

		/*customImport->LoadCustomFormat("C:/Users/Taccoa/Documents/GitHub/FBX-Exporter/FBX importer.exporter/BinaryData.bin");
		customImport->NewMesh();*/

		/*if (!graphics->LoadObjModel(L"C:/Users/Fanny/Documents/LitetSpel/ERIN/stage.obj", &graphics->meshVertBuff, &graphics->meshIndexBuff, graphics->meshSubsetIndexStart, graphics->meshSubsetTexture, graphics->material, graphics->meshSubsets, true, false))
		{
			return;
		}*/
		
		/*if (!graphics->LoadObjModel(L"C:/Users/Marc/Documents/Visual Studio 2015/Projects/ERIN/Cube.obj", &graphics->meshVertBuff, &graphics->meshIndexBuff, graphics->meshSubsetIndexStart, graphics->meshSubsetTexture, graphics->material, graphics->meshSubsets, true, false))
		{
			return;
		}*/
		
		graphics->CreateConstantBuffer();

		ShowWindow(wndHandle, nCommandShow);

	}
}

Engine::~Engine()
{
	delete this->graphics;
	delete this->camera;
	delete this->player;
	//delete this->gameObject;
	delete this->customImport;

	for (int i = 0; i < 4; i++)
	{
		delete enemies[i];
	}
	delete enemies;
}

void Engine::processInput()
{
	player->input->update();

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
			if (aButtonActive == false)
			{
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
			}

			if (this->player->input->State._buttons[GamePad_Button_A] == false)
				aButtonActive = false;
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
					cout << "Pause Menu Option " << pMenuOption << " (Restart)" << endl;
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
					cout << "Pause Menu Option " << pMenuOption << " (Restart)" << endl;
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
			if(aButtonActive == false)
			{
				if (this->player->input->State._buttons[GamePad_Button_A] == true)
				{
					if (pMenuOption == 0)
					{
						cout << "Game Running" << endl;
						gameState = GameRunning;
					}
					else if (pMenuOption == 1)
					{
						cout << "Restart" << endl;
						//gameState = GameRunning;
					}
					else if (pMenuOption == 2)
					{
						cout << "Help & Options" << endl;
						//gameState = HelpAndOptions;
					}
					else if (pMenuOption == 3)
					{
						cout << "Main Menu" << endl;
						pMenuOption = 0;
						gameState = MainMenu;
						aButtonActive = true;
					}
				}
			}
			break;
		case HighScore:
			break;
		case HelpAndOptions:
			break;
		}

		/*if (this->player->input->State._buttons[GamePad_Button_Y] == true)
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
		}*/
		if (this->player->input->State._buttons[GamePad_Button_BACK] == true)
		{
			cout << "Shutting down game!" << endl;
			this->running = false;
		}

		// BUMPERS & TRIGGERS
		/*if (this->player->input->State._buttons[GamePad_Button_LEFT_THUMB] == true)
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
		}*/

		// DPAD
		/*if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
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
		}*/
	}
}

void Engine::update(double deltaTimeMs)
{
	double deltaTimeS;
	deltaTimeS = deltaTimeMs / 1000;
	// update code
	// example physics calculation using delta time:
	// object.x = object.x + (object.speed * deltaTimeS);

	switch (gameState)
	{
	case GameRunning:
		//GameLogic->levelHandler();		// Example of how to start a level
		player->update(deltaTimeMs);

		/*gameObject->updateBehavior(*player->pos, gameObject, enemies);
		gameObject->update(deltaTimeMs);*/

		for (int i = 0; i < 4; i++)
		{
			enemies[i]->updateBehavior(*player->pos, enemies[i], enemies);
			enemies[i]->update(deltaTimeMs);
		}

		//render();
		break;
	case TitleScreen:
		//TitleScreen->render();			// Example of how to render the title screen
		graphics->TitleScreenRender();
		break;
	case MainMenu:
		//MainMenu->render();				// Example of how to render the main menu
		break;
	case Pause:
		break;
	}

	// printf("Elapsed time: %fS.\n", deltaTimeS);
}

void Engine::render()
{
	//graphics->UpdateConstantBuffer();

	switch (gameState)
	{
	case GameRunning:
		//GameLogic->levelHandler();		// Example of how to start a level

		/*gameObject->updateBehavior(*player->pos, gameObject, enemies);
		gameObject->update(deltaTimeMs);*/
		graphics->Render();
		graphics->RendPlayer(*player->objectMatrix);
		/*graphics->RendPlayer(*gameObject->objectMatrix);*/
		//graphics->RenderCustom(customImport->meshes.at(0));

		for (int i = 0; i < 4; i++)
		{
			graphics->RendPlayer(*enemies[i]->objectMatrix);
		}

		camera->InitCamera();
		
		break;
	case TitleScreen:
		//TitleScreen->render();			// Example of how to render the title screen
		graphics->TitleScreenRender();
		break;
	case MainMenu:
		//MainMenu->render();				// Example of how to render the main menu
		graphics->MainMenuRender();
		break;
	case Pause:
		//graphics->PauseRender();
		break;
	}

	// Switch front- and back-buffer
	graphics->get_gSwapChain()->Present(1, 0);
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
	RECT rc = { 0, 0, (LONG)graphics->get_gWidth() , (LONG)graphics->get_gHeight() };
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