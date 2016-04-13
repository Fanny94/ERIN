#ifndef MESH_H
#define MESH_H

#include "Linker.h"
#include "Graphics.h"
#include "WICTextureLoader.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	struct Vertex
	{
		Vertex(){}
		Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz): pos(x,y,z), texCoord(u,v), normal(nx, ny, nz){}

		XMFLOAT3 pos;
		XMFLOAT2 texCoord;
		XMFLOAT3 normal;
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
	XMMATRIX meshWorld;
	int meshSubsets = 0;
	vector<int> meshSubsetIndexStart;
	vector<int> meshSubsetTexture;
	vector<ID3D11ShaderResourceView*>* meshSRV;
	vector<wstring> textureNameArray;
	vector<SurfaceMaterial> material;

private:
	Graphics* graphics;
};
#endif // !MESH_H