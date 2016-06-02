#include "CustomImport.h"

struct Vertex
{
	float pos[3];
	float nor[3];
	float uv[2];
	float tan[3];
	float bitan[3];
};

struct MeshStruct
{
	unsigned int VertexCount;
	unsigned int MaterialID;
	unsigned int MeshID;
	unsigned int ParentID;
	unsigned int AttributeCount;
	char MeshName[256];
	float Translation[3];
	float Rotation[3];
	float Scale[3];
	vector<Vertex> vertex;
	Vertex vertexTemp;
};

struct Material
{
	float diffuseColor[3];
	float ambientColor[3];
	float specularColor[3];
	float transparency;
	float shininess;
	float reflection;
	char diffuseMap[256];
};

struct Camera
{
	float CamPos[3];
	float CamRotation[3];
};

struct PointLight
{
	float intensity;
	float color[3];
	float position[3];
};

struct SpotLight
{
	float intensity;
	float color[3];
	float position[3];
	float rotation[3];
};

struct DirectionalLight
{
	float intensity;
	float color[3];
	float position[3];
	float rotation[3];
};

struct Light
{
	unsigned int Point;
	unsigned int Spot;
	unsigned int Directional;
};

unsigned int MeshCount = 0;
vector<MeshStruct> meshS;
MeshStruct meshTemp;
unsigned int MaterialCount = 0;
vector<Material> material;
Material materialTemp;
unsigned int CameraCount = 0;
vector<Camera> camera;
Camera cameraTemp;
unsigned int LightCount;
Light light;
vector<PointLight> pointL;
PointLight pointLightTemp;
vector<SpotLight> spotL;
SpotLight spotLightTemp;
vector<DirectionalLight> directionalL;
DirectionalLight directionalLightTemp;


CustomImport::CustomImport() {}

CustomImport::~CustomImport() {}

void CustomImport::LoadCustomFormat(string filePath)
{
	ifstream fileIn(filePath, ios::in | ios::binary);

	fileIn.read((char*)&MeshCount, sizeof(unsigned int));
	fileIn.read((char*)&MaterialCount, sizeof(unsigned int));
	//fileIn.read((char*)&GroupCount, sizeof(unsigned int));
	fileIn.read((char*)&LightCount, sizeof(unsigned int));
	fileIn.read((char*)&CameraCount, sizeof(unsigned int));
	//fileIn.read((char*)&SkeletonAnimationCount, sizeof(unsigned int));
	//fileIn.read((char*)&KeyFrameCount, sizeof(unsigned int));
	//fileIn.read((char*)&MorphAnimationCount, sizeof(unsigned int));
	//fileIn.read((char*)&CustomAttributesCount, sizeof(unsigned int));

	for (int i = 0; i < MeshCount; i++)
	{
		fileIn.read((char*)&meshTemp.VertexCount, sizeof(unsigned int));
		fileIn.read((char*)&meshTemp.MaterialID, sizeof(unsigned int));
		fileIn.read((char*)&meshTemp.MeshID, sizeof(unsigned int));
		fileIn.read((char*)&meshTemp.ParentID, sizeof(unsigned int));
		fileIn.read((char*)&meshTemp.MeshName, sizeof(char) * 256);
		fileIn.read((char*)&meshTemp.AttributeCount, sizeof(unsigned int));
		fileIn.read((char*)&meshTemp.Translation, sizeof(float) * 3);
		fileIn.read((char*)&meshTemp.Rotation, sizeof(float) * 3);
		fileIn.read((char*)&meshTemp.Scale, sizeof(float) * 3);

		for (int j = 0; j < meshTemp.VertexCount; j++)
		{
			fileIn.read((char*)&meshTemp.vertexTemp.pos, sizeof(float) * 3);
			fileIn.read((char*)&meshTemp.vertexTemp.nor, sizeof(float) * 3);
			fileIn.read((char*)&meshTemp.vertexTemp.uv, sizeof(float) * 2);
			fileIn.read((char*)&meshTemp.vertexTemp.tan, sizeof(float) * 3);
			fileIn.read((char*)&meshTemp.vertexTemp.bitan, sizeof(float) * 3);
			meshTemp.vertex.push_back(meshTemp.vertexTemp);
		}
		meshS.push_back(meshTemp);
		meshTemp.vertex.clear();
	}

	for (int i = 0; i < MaterialCount; i++)
	{
		fileIn.read((char*)&materialTemp.diffuseColor, sizeof(float) * 3);
		fileIn.read((char*)&materialTemp.specularColor, sizeof(float) * 3);
		fileIn.read((char*)&materialTemp.ambientColor, sizeof(float) * 3);
		fileIn.read((char*)&materialTemp.transparency, sizeof(float));
		fileIn.read((char*)&materialTemp.shininess, sizeof(float));
		fileIn.read((char*)&materialTemp.reflection, sizeof(float));
		fileIn.read((char*)&materialTemp.diffuseMap, sizeof(char) * 256);
		/*fileIn.read((char*)&NormalMap, sizeof(char) * 256);
		fileIn.read((char*)&SpecularMap, sizeof(char) * 256);*/
		material.push_back(materialTemp);
	}

	/*for (int i = 0; i < GroupCount; i++)
	{
	fileIn.read((char*)&GroupID, sizeof(unsigned int));
	fileIn.read((char*)&GGroupCount, sizeof(unsigned int));
	fileIn.read((char*)&GroupParentID, sizeof(unsigned int));
	fileIn.read((char*)&GroupMeshID, sizeof(unsigned int));
	}*/

	for (int i = 0; i < LightCount; i++)
	{
		fileIn.read((char*)&light.Point, sizeof(unsigned int));
		fileIn.read((char*)&light.Spot, sizeof(unsigned int));
		fileIn.read((char*)&light.Directional, sizeof(unsigned int));

		for (int j = 0; j < light.Point; j++)
		{
			fileIn.read((char*)&pointLightTemp.intensity, sizeof(float));
			fileIn.read((char*)&pointLightTemp.color, sizeof(float) * 3);
			fileIn.read((char*)&pointLightTemp.position, sizeof(float) * 3);
			pointL.push_back(pointLightTemp);
		}

		for (int k = 0; k < light.Spot; k++)
		{
			fileIn.read((char*)&spotLightTemp.intensity, sizeof(float));
			fileIn.read((char*)&spotLightTemp.color, sizeof(float) * 3);
			fileIn.read((char*)&spotLightTemp.position, sizeof(float) * 3);
			fileIn.read((char*)&spotLightTemp.rotation, sizeof(float) * 3);
			spotL.push_back(spotLightTemp);
		}

		for (int l = 0; l < light.Directional; l++)
		{
			fileIn.read((char*)&directionalLightTemp.intensity, sizeof(float));
			fileIn.read((char*)&directionalLightTemp.color, sizeof(float) * 3);
			fileIn.read((char*)&directionalLightTemp.position, sizeof(float) * 3);
			fileIn.read((char*)&directionalLightTemp.rotation, sizeof(float) * 3);
			directionalL.push_back(directionalLightTemp);
		}
	}

	for (int i = 0; i < CameraCount; i++)
	{
		fileIn.read((char*)&cameraTemp.CamPos, sizeof(float) * 3);
		fileIn.read((char*)&cameraTemp.CamRotation, sizeof(float) * 3);
		camera.push_back(cameraTemp);
	}

	/*for (int i = 0; i < SkeletonAnimationCount; i++)
	{

	}*/

	/*for (int i = 0; i < KeyFrameCount; i++)
	{
	fileIn.read((char*)&KeyFrameID, sizeof(float));
	fileIn.read((char*)&KeyFrameTime, sizeof(float));
	fileIn.read((char*)&KeyFramePosition, sizeof(float) * 3);
	}*/

	/*for (int i = 0; i < MorphAnimationCount; i++)
	{

	}*/

	/*for (int i = 0; i < CustomAttributesCount; i++)
	{
	fileIn.read((char*)&CustomVectorCount, sizeof(unsigned int));
	fileIn.read((char*)&CustomFloatCount, sizeof(unsigned int));
	fileIn.read((char*)&CustomIntCount, sizeof(unsigned int));
	fileIn.read((char*)&CustomBoolCount, sizeof(unsigned int));
	fileIn.read((char*)&CustomStringCount, sizeof(unsigned int));

	for (int j = 0; j < CustomVectorCount; j++)
	{
	fileIn.read((char*)&customVectorTemp.cVector, sizeof(float) * 3);
	customVector.push_back(customVectorTemp);
	}

	for (int k = 0; k < CustomFloatCount; k++)
	{
	fileIn.read((char*)&customFloatTemp.cFloat, sizeof(float));
	customFloat.push_back(customFloatTemp);
	}

	for (int l = 0; l < CustomIntCount; l++)
	{
	fileIn.read((char*)&customIntTemp.cInt, sizeof(int));
	customInt.push_back(customIntTemp);
	}

	for (int m = 0; m < CustomBoolCount; m++)
	{
	fileIn.read((char*)&customBoolTemp.cBool, sizeof(bool));
	customBool.push_back(customBoolTemp);
	}

	for (int n = 0; n < CustomStringCount; n++)
	{
	fileIn.read((char*)&customStringTemp.cString, sizeof(char) * 256);
	customString.push_back(customStringTemp);
	}
	}*/
	fileIn.close();
}

void CustomImport::NewMesh()
{
	Mesh newMesh;
	newMesh.MeshCount = MeshCount;
	newMesh.MaterialCount = MaterialCount;

	int count = meshS.size() - newMesh.MeshCount;

	for (int i = count; i < meshS.size(); i++)
	{
		newMesh.meshTemp.VertexCount = meshS.at(i).VertexCount;
		newMesh.meshTemp.MaterialID = meshS.at(i).MaterialID;
		newMesh.meshTemp.MeshID = meshS.at(i).MeshID;
		newMesh.meshTemp.ParentID = meshS.at(i).ParentID;
		for (int j = 0; j < 256; j++)
		{
			newMesh.meshTemp.MeshName[j] = meshS.at(i).MeshName[j];
		}
		newMesh.meshTemp.AttributeCount = meshS.at(i).AttributeCount;
		for (int k = 0; k < 3; k++)
		{
			newMesh.meshTemp.Translation[k] = meshS.at(i).Translation[k];
			newMesh.meshTemp.Rotation[k] = meshS.at(i).Rotation[k];
			newMesh.meshTemp.Scale[k] = meshS.at(i).Scale[k];
		}

		newMesh.world = XMMatrixTranslation(newMesh.meshTemp.Translation[0], newMesh.meshTemp.Translation[1], newMesh.meshTemp.Translation[2]);

		for (int l = 0; l < newMesh.meshTemp.VertexCount; l++)
		{
			int vertIndex = l;
				if (l % 3 == 0)
				{ 
					vertIndex += 2;
				}
				else if (l % 3 == 2)
				{
					vertIndex -= 2;
				}

			for (int m = 0; m < 3; m++)
			{
				newMesh.meshTemp.vertexTemp.pos[m] = meshS.at(i).vertex.at(vertIndex).pos[m];
				newMesh.meshTemp.vertexTemp.nor[m] = meshS.at(i).vertex.at(vertIndex).nor[m];

				newMesh.meshTemp.vertexTemp.tan[m] = meshS.at(i).vertex.at(vertIndex).tan[m];
				newMesh.meshTemp.vertexTemp.bitan[m] = meshS.at(i).vertex.at(vertIndex).bitan[m];
			}
			for (int n = 0; n < 2; n++)
			{
				newMesh.meshTemp.vertexTemp.uv[n] = meshS.at(i).vertex.at(vertIndex).uv[n];
	
			}
			newMesh.meshTemp.vertex.push_back(newMesh.meshTemp.vertexTemp);
		}
		newMesh.mesh.push_back(newMesh.meshTemp);
	}
	int mcount = material.size() - newMesh.MaterialCount;

	for (int i = mcount; i < material.size(); i++)
	{
		char temp[256];
		for (int e = 0; e < 256; e++)
		{
			if (material.at(i).diffuseMap[e] == '\0')
			{
				temp[e] = '\0';
				int snafu = 256 - e;
				for (int w = 1; w < snafu; w++)
				{
					temp[e + w] = '0';
				}
				break;
			}
			temp[e] = material.at(i).diffuseMap[e];
		}

		for (int p = 256; p > 0; p--)
		{
			if (temp[p] == '/')
			{
				material.at(i).diffuseMap[0] = '.';
				material.at(i).diffuseMap[1] = '.';
				int size = 256 - p;
				p = p - 2;
				for (int q = 2; q < size; q++)
				{
					material.at(i).diffuseMap[q] = temp[p + q];
				}
				break;
			}
			else if (temp[p] == '\\')
			{
				material.at(i).diffuseMap[0] = '.';
				material.at(i).diffuseMap[1] = '.';
				int size = 256 - p;
				p = p - 2;
				for (int q = 2; q < size; q++)
				{
					material.at(i).diffuseMap[q] = temp[p + q];
				}
				break;
			}
		}

		for (int j = 0; j < 3; j++)
		{
			newMesh.materialTemp.diffuseColor[j] = material.at(i).diffuseColor[j];
			newMesh.materialTemp.specularColor[j] = material.at(i).specularColor[j];
			newMesh.materialTemp.ambientColor[j] = material.at(i).ambientColor[j];
		}
		newMesh.materialTemp.transparency = material.at(i).transparency;
		newMesh.materialTemp.shininess = material.at(i).shininess;
		newMesh.materialTemp.reflection = material.at(i).reflection;
		for (int k = 0; k < 256; k++)
		{
			newMesh.materialTemp.diffuseMap[k] = material.at(i).diffuseMap[k];
		}
		newMesh.material.push_back(newMesh.materialTemp);
	}
	newMesh.textureBool = false;
	meshes.push_back(newMesh);
}