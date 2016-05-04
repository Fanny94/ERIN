#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Linker.h"
#include "Structs.h"
#include "Camera.h"
#include "WICTextureLoader.h"
#include "Mesh.h"

using namespace std;
class Camera;

class Graphics
{
public:
	Graphics();
	~Graphics();

	void SetViewport();
	void Render();
	void RendBullets(Matrix transform);

	void CustomVertexBuffer(Mesh mesh);
	void RenderCustom(Mesh mesh, Matrix transform, int cvb);
	void CustomUpdateBuffer(Matrix transform);

	void CreateShaders();
	void CreateDepthBuffer();

	void CreateTriangle(TriangleVertex* triangleVertices);
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

	struct MATRICES
	{
		Matrix worldViewProj;
		Matrix world;
		Matrix view;
		Matrix projection;
		XMFLOAT4 camPos;
	};

	Matrix viewProj;
	TriangleVertex* triangleVertices;

	MATRICES* MatrixPtr;
	MATRICES* MatrixPtr2;
	Camera* camera;

	ID3D11Buffer* customFormatBuffer = nullptr;

	struct CustomFormat
	{
		float diffuseColor[3];
		float paddingDC;
		float ambientColor[3];
		float paddingAC;
		float specularColor[3];
		float shininess;
	};

	CustomFormat* CFPtr;
	
	struct VertexCustom
	{
		float pos[3];
		float nor[3];
		float uv[2];
		float tan[3];
		float bitan[3];
	};

	vector<DWORD> indices;

private:
	float WIDTH = 1080;
	float HEIGHT = 720;

	float camPosX;
	float camPosY;

	ID3D11Device* gDevice = nullptr;
	ID3D11DeviceContext* gDeviceContext = nullptr;
	IDXGISwapChain* gSwapChain = nullptr;
	ID3D11RenderTargetView* gBackbufferRTV = nullptr;
	ID3D11DepthStencilView* gDepthStencilView = nullptr;
	ID3D11Texture2D* gDepthView = nullptr;

	ID3D11InputLayout* gVertexLayout = nullptr;
	ID3D11VertexShader* gVertexShader = nullptr;
	ID3D11Buffer* gVertexBuffer = nullptr;
	ID3D11PixelShader* gPixelShader = nullptr;

	ID3D11Buffer* gConstantBuffer = nullptr;

	vector<ID3D11Buffer*> customVertBuff;
	ID3D11Buffer* customVertBuffTemp;
	HRESULT hr;
};

#endif // !GRAPHICS_H
