#pragma once
#include "Linker.h"

class Engine
{
public:
	Engine();
	~Engine();

	struct TriangleVertex
	{
		float x, y, z;
		float r, g, b;
	};

	struct MATRICES
	{
		Matrix worldViewProj;
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	TriangleVertex* triangleVertices;
	const float WIDTH = 640;
	const float HEIGHT = 480;

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

	ID3D11Buffer* gConstantBuffer = nullptr;

	void CreateShaders();
	void CreateTriangle();
	void CreateConstantBuffer();
	void UpdateConstantBuffer();
};