#include "Engine.h"
#include "Camera.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->camera = new Camera();
	this->running = true;
	this->graphics = new Graphics();

	// test input
	this->gameObject = new GameObject("player", 0.0f, 0.0f, 0.0f);

	MSG msg = { 0 };

	//create window
	wndHandle = InitWindow(hInstance); //Create Window

	if (!camera->InitDirectInput(hInstance))
	{
		MessageBox(0, "Direct Input Initialization - Failed", "Error", MB_OK);

		return;
	}

	camera->wndH = wndHandle;

	graphics->camera = camera;

	// window is valid
	if (wndHandle)
	{
		// Create SwapChain, Device and Device Context 
		graphics->CreateDirect3DContext(wndHandle);

		graphics->SetViewport(); // Set Viewport

		graphics->CreateShaders();

		graphics->CreateTriangle();

		graphics->CreateConstantBuffer();

		ShowWindow(wndHandle, nCommandShow);


		// read messages
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}
		else
		{
			// update/render

			//processInput();

			camera->InitCamera();

			//switch front- and back-buffer
			graphics->get_gSwapChain()->Present(0, 0);
		}
	}
}

Engine::~Engine()
{
	delete this->graphics;
	delete this->gameObject;

	// finish program
	//DestroyWindow(wndHandle);
	
	// return how the program finished
	//return (int)msg.wParam;
	if (!graphics)
	{
		delete this->graphics;
	}
	if (!camera)
	{
		delete this->camera;
	}
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
	}
}

void Engine::update(int deltaTimeMs)
{
	float deltaTimeS;
	deltaTimeS = (float)(deltaTimeMs) / 1000;
	// update code
	// example physics calculation using delta time:
	// object.x = object.x + (object.speed * deltaTimeS);

	//printf("Elapsed time: %fS.\n", deltaTimeS);

	//gameObject->input->isConnected();
}

void Engine::render()
{

	graphics->UpdateConstantBuffer();

	graphics->Render();

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
		break;
	}

	//call the default handler function if w do not handle the message here 
	return DefWindowProc(hWnd, message, wParam, lParam);
}