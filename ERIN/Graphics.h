#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Linker.h"
class Camera;

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
	
	float get_gWidth() { return this->WIDTH; }
	float get_gHeight() { return this->HEIGHT; }

	ID3D11Device* get_gDevice() { return this->gDevice; }
	ID3D11DeviceContext* get_gDeviceContext() { return this->gDeviceContext; }
	IDXGISwapChain* get_gSwapChain() { return this->gSwapChain; }
	ID3D11RenderTargetView* get_gBackbufferRTV() { return this->gBackbufferRTV; }

	ID3D11InputLayout* get_gVertexLayout() { return this->gVertexLayout; }
	ID3D11VertexShader* get_gVertexShader() { return this->gVertexShader; }
	ID3D11Buffer* get_gVertexBuffer() { return this->gVertexBuffer; }
	ID3D11PixelShader* get_gPixelShader() { return this->gPixelShader; }

	ID3D11Buffer* get_gConstantBuffer() { return this->gConstantBuffer; }

	HRESULT CreateDirect3DContext(HWND wndHandle);

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
	Camera* camera;

private:
	float WIDTH = 1080;
	float HEIGHT = 720;

	float camPosX;
	float camPosY;

	ID3D11Device* gDevice = nullptr;
	ID3D11DeviceContext* gDeviceContext = nullptr;
	IDXGISwapChain* gSwapChain = nullptr;
	ID3D11RenderTargetView* gBackbufferRTV = nullptr;

	ID3D11InputLayout* gVertexLayout = nullptr;
	ID3D11VertexShader* gVertexShader = nullptr;
	ID3D11Buffer* gVertexBuffer = nullptr;
	ID3D11PixelShader* gPixelShader = nullptr;

	ID3D11Buffer* gConstantBuffer = nullptr;
};

#endif // !GRAPHICS_H