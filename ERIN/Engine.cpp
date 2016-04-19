#include "Engine.h"
#include "Camera.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->running = true;
	this->camera = new Camera();
	this->graphics = new Graphics();

	// test input
	this->gameObject = new GameObject("player", -0.5f, 0.0f, 0.0f);

	//create window
	wndHandle = InitWindow(hInstance);

	AllocConsole();

	freopen("CONOUT$", "w", stdout);

	if (!camera->InitDirectInput(hInstance))
	{
		MessageBox(0, "Direct Input Initialization - Failed", "Error", MB_OK);

		return;
	}

	// camera->wndH = wndHandle; Behövs denna raden?? / Marc

	graphics->camera = camera;

	// window is valid
	if (wndHandle)
	{
		// Create SwapChain, Device and Device Context 
		graphics->CreateDirect3DContext(wndHandle);

		graphics->SetViewport(); // Set Viewport

		graphics->CreateShaders();

		graphics->CreateTriangle(gameObject->triangle);

		graphics->CreateTriangleAABBBox(gameObject->axisAllignedBox, gameObject->triangle);
		
		graphics->CreateSquareAABBBox(gameObject->axisAllignedBox, gameObject->triangle);

		if (!graphics->LoadObjModel(L"C:/Users/Fanny/Documents/LitetSpel/ERIN/Cube.obj", &graphics->meshVertBuff, &graphics->meshIndexBuff, graphics->meshSubsetIndexStart, graphics->meshSubsetTexture, graphics->material, graphics->meshSubsets, true, false))
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
	delete this->gameObject;
	delete this->camera;

	fclose(stdout);
	// finish program
	//DestroyWindow(wndHandle);
	
	// return how the program finished
	//return (int)msg.wParam;
}

void Engine::processInput()
{

	gameObject->input->update(); // test object, should be done for all objects

	if (gameObject->input->isConnected())
	{
		if (this->gameObject->input->State._buttons[GamePad_Button_Y] == true)
		{
			this->running = false;
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_X] == true)
		{
			this->running = false;
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_B] == true)
		{
			this->running = false;
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_A] == true)
		{
			this->running = false;
		}

		if (this->gameObject->input->State._buttons[GamePad_Button_START] == true)
		{
			this->running = false;
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_BACK] == true)
		{
			this->running = false;
		}

		if (this->gameObject->input->State._buttons[GamePad_Button_LEFT_THUMB] == true)
		{
			this->running = false;
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_RIGHT_THUMB] == true)
		{
			this->running = false;
		}

		if (this->gameObject->input->State._buttons[GamePad_Button_LEFT_SHOULDER] == true)
		{
			this->running = false;
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_RIGHT_SHOULDER] == true)
		{
			this->running = false;
		}

		// test camera movement
		if (this->gameObject->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
		{
			this->camera->cameraMoveLeft();
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
		{
			this->camera->cameraMoveRight();
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_DPAD_UP] == true)
		{
			this->camera->cameraMoveUp();
		}
		if (this->gameObject->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
		{
			this->camera->cameraMoveDown();
		}

		// test xbox thumstix

		/*float leftX = this->gameObject->input->State._left_thumbstick.x;
		float leftY = this->gameObject->input->State._left_thumbstick.y;

		if (leftX < -0.0f)
		{
			this->camera->cameraMoveLeft(leftX);
		}
		if (leftX > 0.0f)
		{
			this->camera->cameraMoveRight(leftX);
		}
		if (leftY < -0.0f)
		{
			this->camera->cameraMoveDown(leftY);
		}
		if (leftY > 0.0f)
		{
			this->camera->cameraMoveUp(leftY);
		}*/

		float thumbLeftX = this->gameObject->input->State._left_thumbstick.x;
		float thumbLeftY = this->gameObject->input->State._left_thumbstick.y;

		float playerX = this->gameObject->GetX();
		float playerY = this->gameObject->GetY();

		float speed = 5.0f; // (float)(5.0f * time);

		if (thumbLeftX < -0.0f)
		{
			playerX -= 0.001f;
			this->gameObject->SetX(playerX);
		}
		if (thumbLeftX > 0.0f)
		{
			playerX += 0.001f;
			this->gameObject->SetX(playerX);
		}
		if (thumbLeftY < -0.0f)
		{
			playerY -= 0.001f;
			this->gameObject->SetY(playerY);
		}
		if (thumbLeftY > 0.0f)
		{
			playerY += 0.001f;
			this->gameObject->SetY(playerY);
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

	//gameObject->input->isConnected();
	gameObject->update();
}

void Engine::render()
{
	graphics->UpdateConstantBuffer();
	gameLogic->AABBtoAABB(*gameObject->axisAllignedBox, *gameObject->axisAllignedBox);

	graphics->Render();
	graphics->RendPlayer(*gameObject->objectMatrix);
	camera->InitCamera();

	// switch front- and back-buffer
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
	// Window is the name of the class

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