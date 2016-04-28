#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Linker.h"
#include "Structs.h"
#include "Camera.h"
#include "WICTextureLoader.h"
#include "Mesh.h"

class Camera;

class Graphics
{
public:
	Graphics();
	~Graphics();

	void SetViewport();
	void Render();
	void RendPlayer(Matrix transform);
	void RenderCustom(Mesh mesh);
	void CreateShaders();
	void CreateTriangle(TriangleVertex* triangleVertices);
	void CreateTriangle();
	void CreateConstantBuffer();
	void CreateTriangleAABBBox(AABBBox* axisAllignedBox);
	void CreateSquareAABBBox(AABBBox* axisAllignedBox);
	void CreateDepthBuffer();
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

	ID3D11Buffer* objBuffer = nullptr;

	struct OBJ
	{
		XMFLOAT4 difColor;
		int hasTexture;
		float padding[3];
	};

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

	struct Vertex
	{
		Vertex() {}
		Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz) : pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}

		XMFLOAT3 pos;
		XMFLOAT2 texCoord;
		XMFLOAT3 normal;
	};

	struct VertexCustom
	{
		float pos[3];
		float nor[3];
		float uv[2];
		float tan[3];
		float bitan[3];
	};

	struct SurfaceMaterial
	{
		wstring matName;
		XMFLOAT4 difColor;
		int texArrayIndex;
		bool hasTexture;
		bool transparent;
	};

	bool LoadObjModel(wstring filename,		//.obj filename
		ID3D11Buffer** vertBuff,			//mesh vertex buffer
		ID3D11Buffer** indexBuff,			//mesh index buffer
		vector<int>& subsetIndexStart,		//start index of each subset
		vector<int>& subsetMaterialArray,	//index value of material for each subset
		vector<SurfaceMaterial>& material,	//vector of material structures
		int& subsetCount,					//Number of subsets in mesh
		bool isRHCoordSys,					//true if model was created in right hand coord system
		bool computeNormals);				//true to compute the normals, false to use the files normals

	ID3D11BlendState* Transparency;
	ID3D11Buffer* meshVertBuff;
	ID3D11Buffer* meshIndexBuff;
	int meshSubsets = 0;
	vector<int> meshSubsetIndexStart;
	vector<int> meshSubsetTexture;
	vector<ID3D11ShaderResourceView*> meshSRV;
	vector<wstring> textureNameArray;
	vector<SurfaceMaterial> material;
	vector<Vertex> vertexMeshSize;
	vector<AABBBox> triangleBox;
	vector<AABBBox> squareBox;

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

	ID3D11Buffer* customVertBuff = nullptr;
	HRESULT hr;
};

#endif // !GRAPHICS_H
