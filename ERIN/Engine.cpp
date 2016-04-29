#include "Engine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->running = true;
	this->camera = new Camera();
	this->graphics = new Graphics();
	this->gameLogic = new GameLogic();

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

		customImport->LoadCustomFormat("C:/Users/Fanny/Documents/LitetSpel/ERIN/BinaryData.bin");
		customImport->NewMesh();

		//customImport->LoadCustomFormat("C:/Users/Taccoa/Documents/GitHub/FBX-Exporter/FBX importer.exporter/BinaryDataSphere.bin");
		customImport->NewMesh();
		
		graphics->CreateTriangleAABBBox(player->triangle);

		graphics->AABBTrianglePoints();

		for (int i = 0; i < 2; i++)
		{
			graphics->CreateSquareAABBBox(customImport->meshes.at(i));
		}
		graphics->AABBSquarePoints();
		
		graphics->CreateConstantBuffer();

		ShowWindow(wndHandle, nCommandShow);
	}
}

Engine::~Engine()
{
	delete this->graphics;
	delete this->camera;
	delete this->customImport;
	delete this->gameLogic;

	// player enemies
	delete this->player;
	//delete this->gameObject;

	for (int i = 0; i < 4; i++)
	{
		delete enemies[i];
	}
	delete enemies;
}

void Engine::processInput()
{

	player->input->update(); // test object, should be done for all objects

	if (player->input->isConnected())
	{
		player->playerInput();

		if (this->player->input->State._buttons[GamePad_Button_Y] == true)
		{
			this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_X] == true)
		{
			this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_B] == true)
		{
			this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_A] == true)
		{
			this->running = false;
		}

		if (this->player->input->State._buttons[GamePad_Button_START] == true)
		{
			this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_BACK] == true)
		{
			this->running = false;
		}

		if (this->player->input->State._buttons[GamePad_Button_LEFT_THUMB] == true)
		{
			this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_THUMB] == true)
		{
			this->running = false;
		}

		if (this->player->input->State._buttons[GamePad_Button_LEFT_SHOULDER] == true)
		{
			this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_SHOULDER] == true)
		{
			this->running = false;
		}

		// Dpad camera movement
		if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
		{
			this->camera->cameraMoveLeft();
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
		{
			this->camera->cameraMoveRight();
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
		{
			this->camera->cameraMoveUp();
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
		{
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

	player->update(deltaTimeMs);
	/*gameObject->updateBehavior(*player->pos, gameObject, enemies);
	gameObject->update(deltaTimeMs);*/

	for (int i = 0; i < 4; i++)
	{
		enemies[i]->updateBehavior(*player->shipPos, enemies[i], enemies);
		enemies[i]->update(deltaTimeMs);
	}

	//printf("Elapsed time: %fS.\n", deltaTimeS);
}

void Engine::render()
{
	//graphics->UpdateConstantBuffer();

	//graphics->transformBoundingBox(*gameObject->objectMatrix);
	graphics->AABBtoAABB();

	graphics->Render();
	graphics->RendPlayer(*player->shipMatrix);
	graphics->RendPlayer(*player->turretMatrix);
	/*graphics->RendPlayer(*gameObject->objectMatrix);*/

	graphics->RendTriangleAABB(*player->shipMatrix);
	customImport->meshes.at(1).world = XMMatrixTranslation(4, 0, 0);
	//	graphics->RenderCustom(customImport->meshes.at(0), customImport->meshes.at(0).world);
	for (int j = 0; j < 2; j++)
	{
		graphics->RenderCustom(customImport->meshes.at(j), customImport->meshes.at(j).world);
	}

	//render 2 AABB boxes
	for (int k = 0; k < 2; k++)
	{
		graphics->RendAABB(customImport->meshes.at(k).world);
	}

	for (int i = 0; i < 4; i++)
	{
		graphics->RendPlayer(*enemies[i]->objectMatrix);
	}

	camera->InitCamera();

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