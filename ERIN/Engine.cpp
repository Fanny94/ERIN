#include "Engine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine()
{
	 this->graphics = new Graphics();
}

Engine::~Engine()
{
	delete this->graphics;
}

int Engine::Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	MSG msg = { 0 };

	//create window
	HWND wndHandle = InitWindow(hInstance); //Create Window

											//window is valid
	if (wndHandle)
	{
		//Create SwapChain, Device and Device Context 
		graphics->CreateDirect3DContext(wndHandle);

		graphics->SetViewport(); //Set Viewport

		graphics->CreateShaders();

		graphics->CreateTriangle();

		graphics->CreateConstantBuffer();

		ShowWindow(wndHandle, nCommandShow);

		while (WM_QUIT != msg.message)
		{
			//read messages
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
			else
			{
				//update/render

				graphics->UpdateConstantBuffer();

				graphics->Render();

				//switch front- and back-buffer
				graphics->get_gSwapChain()->Present(0, 0);
			}
		}
		//finish program
		DestroyWindow(wndHandle);
	}
	//return how the program finished
	return (int)msg.wParam;
}

HWND Engine::InitWindow(HINSTANCE hInstance)
{
	//Every window created must belkong to a class

	WNDCLASSEX winClassInfo = { 0 };
	winClassInfo.cbSize = sizeof(WNDCLASSEX);
	winClassInfo.style = CS_HREDRAW | CS_VREDRAW;
	winClassInfo.lpfnWndProc = WndProc; //This function is called for events
	winClassInfo.hInstance = hInstance;
	winClassInfo.lpszClassName = "WindowClass";
	//Window is the name of the class

	if (!RegisterClassEx(&winClassInfo))
		return false;

	//the window size
	RECT rc = { 0, 0, (LONG) graphics->get_gWidth() , (LONG) graphics->get_gHeight() };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND handle = CreateWindow(
		"WindowClass",	//Class name
		"Window",		//Window name
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