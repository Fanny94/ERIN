#pragma once
#include "Linker.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Render();
	void SetViewport();
	int Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow);

	IDXGISwapChain* gSwapChain = nullptr;
	ID3D11Device* gDevice = nullptr;
	ID3D11DeviceContext* gDeviceContext = nullptr;
	ID3D11RenderTargetView* gBackbufferRTV = nullptr;

	HWND InitWindow(HINSTANCE hInstance);
	HRESULT CreateDirect3DContext(HWND wndHandle);
};