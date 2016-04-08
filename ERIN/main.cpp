#include <Windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

IDXGISwapChain* gSwapChain = nullptr;
ID3D11Device* gDevice = nullptr;
ID3D11DeviceContext* gDeviceContext = nullptr;
ID3D11RenderTargetView* gBackbufferRTV = nullptr;

HWND InitWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT CreateDirect3DContext(HWND wndHandle);

//link for details about the windows datatypes
//https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx

void SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width = 640;
	vp.Height = 480;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	gDeviceContext->RSSetViewports(1, &vp);
}

void Render()
{
	float clearColor[] = { 0, 0, 0, 1 };
	gDeviceContext->ClearRenderTargetView(gBackbufferRTV, clearColor);
}

//Entry point for te program
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCommandLine, int nCommandShow)
{
	MSG msg = { 0 };

	//create window
	HWND wndHandle = InitWindow(hInstance); //Create Window

											//window is valid
	if (wndHandle)
	{
		//Create SwapChain, Device and Device Context 
		CreateDirect3DContext(wndHandle);

		SetViewport(); //Set Viewport

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
				Render();

				//switch front- and back-buffer
				gSwapChain->Present(0, 0);
			}
		}

		gBackbufferRTV->Release();
		gSwapChain->Release();
		gDevice->Release();
		gDeviceContext->Release();

		//finish program
		DestroyWindow(wndHandle);
	}

	//return how the program finished
	return (int)msg.wParam;
}

HWND InitWindow(HINSTANCE hInstance)
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
	RECT rc = { 0, 0, 640, 480 };
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
	LPARAM lParam)
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

HRESULT CreateDirect3DContext(HWND wndHandle)
{
	//struct that holds info about the swapchain
	DXGI_SWAP_CHAIN_DESC swapChainD;

	//clear out the struct for use
	ZeroMemory(&swapChainD, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainD.BufferCount = 1;
	swapChainD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainD.OutputWindow = wndHandle;
	swapChainD.SampleDesc.Count = 4;
	swapChainD.Windowed = TRUE;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainD,
		&gSwapChain,
		&gDevice,
		NULL,
		&gDeviceContext);

	if (SUCCEEDED(hr))
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		gDevice->CreateRenderTargetView(pBackBuffer, NULL, &gBackbufferRTV);
		pBackBuffer->Release();

		gDeviceContext->OMSetRenderTargets(1, &gBackbufferRTV, NULL);

	}
	return hr;
}