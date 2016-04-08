#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Linker.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void Render();
	void SetViewport();
	void CreateShaders();
	void CreateTriangle();
	void CreateConstantBuffer();
	void UpdateConstantBuffer();

	const float WIDTH = 640;
	const float HEIGHT = 480;

	HRESULT CreateDirect3DContext(HWND wndHandle);

	ID3D11Device* gDevice = nullptr;
	ID3D11DeviceContext* gDeviceContext = nullptr;
	IDXGISwapChain* gSwapChain = nullptr;
	ID3D11RenderTargetView* gBackbufferRTV = nullptr;

	ID3D11InputLayout* gVertexLayout = nullptr;
	ID3D11VertexShader* gVertexShader = nullptr;
	ID3D11Buffer* gVertexBuffer = nullptr;
	ID3D11PixelShader* gPixelShader = nullptr;

	ID3D11Buffer* gConstantBuffer = nullptr;

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
};

#endif // !GRAPHICS_H