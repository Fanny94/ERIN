#ifndef ENGINE_H
#define ENGINE_H
#include "Linker.h"
#include "GameLogic.h"

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

	ID3D11InputLayout* gVertexLayout = nullptr;
	ID3D11VertexShader* gVertexShader = nullptr;
	ID3D11Buffer* gVertexBuffer = nullptr;
	ID3D11PixelShader* gPixelShader = nullptr;

	void CreateShaders();
	void CreateTriangle();
};

#endif // !ENGINE_H