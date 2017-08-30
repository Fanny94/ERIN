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
	char MeshName[256] = "";
	unsigned int AttributeCount;
	float Translation[3] = { 0.0, 0.0, 0.0 };
	float Rotation[3] = { 0.0, 0.0, 0.0 };
	float Scale[3] = { 1.0, 1.0, 1.0 };

	vector<Vertex> vertex;
	Vertex vertexTemp;
};

struct Material
{
	float diffuseColor[3];
	float specularColor[3];
	float ambientColor[3];
	float transparency;
	float shininess;
	float reflection;
	char diffuseMap[256];
};

//struct CameraMesh
//{
//	float CamPos[3];
//	float CamRotation[3];
//};
//struct PointLight
//{
//	float intensity;
//	float color[3];
//	float position[3];
//};
//struct SpotLight
//{
//	float intensity;
//	float color[3];
//	float position[3];
//	float rotation[3];
//};
//struct DirectionalLight
//{
//	float intensity;
//	float color[3];
//	float position[3];
//	float rotation[3];
//};
//struct Light
//{
//	unsigned int Point;
//	unsigned int Spot;
//	unsigned int Directional;
//};
//struct Skinning
//{
//	float weights[4];
//	unsigned int boneIndices[4];
//};
//struct JointHeader //one joint
//{
//	char jointName[256];
//	int ParentID = 0;
//	unsigned int jointIndex = 0;
//	unsigned int nrOfKeyframes = 0;
//	float globalBindPoseInverse[16];
//};
//struct Keyframe
//{
//	float translation[4];
//	float rotation[4];
//	float scale[4];
//	float keyTime;
//};
//struct Skeleton
//{
//	unsigned int numberOfJoints = 0; //The number of Jointheaders
//	unsigned int numberOfSkinWeights = 0; /*as big as the number of control points,
//										   +										  containing weightdata for each control point*/
//};
//struct MorphStruct
//{
//	float MorphShape[4];
//};
//struct MorphCountStruct
//{
//	unsigned int MorphShapeCount = 0;
//};

unsigned int MeshCount = 0;
vector<MeshStruct> meshList;
MeshStruct meshTemp;
unsigned int MaterialCount = 0;
vector<Material> materials;
Material materialTemp;

/*unsigned int CameraCount = 0;
vector<CameraMesh> camera;
CameraMesh cameraTemp;
unsigned int LightCount;
Light light;
vector<PointLight> pointL;
PointLight pointLightTemp;
vector<SpotLight> spotL;
SpotLight spotLightTemp;
vector<DirectionalLight> directionalL;
DirectionalLight directionalLightTemp;
unsigned int SkeletonAnimationCount;
Skeleton skeleton;
vector<JointHeader> jointHeader;
JointHeader jointHeaderTemp;
vector<Keyframe> keyframe;
Keyframe keyframeTemp;
vector<Skinning> skinning;
Skinning skinningTemp;
unsigned int MorphAnimationCount = 0;
MorphCountStruct morphCount;
vector<MorphStruct> morphVector;
MorphStruct morphTemp;*/

CustomImport::CustomImport() {}

CustomImport::~CustomImport() {}

void CustomImport::LoadCustomFormat(string filePath)
{
	ifstream fileIn(filePath, ios::in | ios::binary);

	fileIn.read((char*)&MeshCount, sizeof(unsigned int));
	fileIn.read((char*)&MaterialCount, sizeof(unsigned int));
	//fileIn.read((char*)&LightCount, sizeof(unsigned int));
	//fileIn.read((char*)&CameraCount, sizeof(unsigned int));
	//fileIn.read((char*)&SkeletonAnimationCount, sizeof(unsigned int));
	//fileIn.read((char*)&MorphAnimationCount, sizeof(unsigned int));

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
		meshList.push_back(meshTemp);
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
		materials.push_back(materialTemp);
	}

	//for (int i = 0; i < LightCount; i++)
	//{
	//	fileIn.read((char*)&light.Point, sizeof(unsigned int));
	//	fileIn.read((char*)&light.Spot, sizeof(unsigned int));
	//	fileIn.read((char*)&light.Directional, sizeof(unsigned int));
	//	for (int j = 0; j < light.Point; j++)
	//	{
	//		fileIn.read((char*)&pointLightTemp.intensity, sizeof(float));
	//		fileIn.read((char*)&pointLightTemp.color, sizeof(float) * 3);
	//		fileIn.read((char*)&pointLightTemp.position, sizeof(float) * 3);
	//		pointL.push_back(pointLightTemp);
	//	}
	//	for (int k = 0; k < light.Spot; k++)
	//	{
	//		fileIn.read((char*)&spotLightTemp.intensity, sizeof(float));
	//		fileIn.read((char*)&spotLightTemp.color, sizeof(float) * 3);
	//		fileIn.read((char*)&spotLightTemp.position, sizeof(float) * 3);
	//		fileIn.read((char*)&spotLightTemp.rotation, sizeof(float) * 3);
	//		spotL.push_back(spotLightTemp);
	//	}
	//	for (int l = 0; l < light.Directional; l++)
	//	{
	//		fileIn.read((char*)&directionalLightTemp.intensity, sizeof(float));
	//		fileIn.read((char*)&directionalLightTemp.color, sizeof(float) * 3);
	//		fileIn.read((char*)&directionalLightTemp.position, sizeof(float) * 3);
	//		fileIn.read((char*)&directionalLightTemp.rotation, sizeof(float) * 3);
	//		directionalL.push_back(directionalLightTemp);
	//	}
	//}
	//for (int i = 0; i < CameraCount; i++)
	//{
	//	fileIn.read((char*)&cameraTemp.CamPos, sizeof(float) * 3);
	//	fileIn.read((char*)&cameraTemp.CamRotation, sizeof(float) * 3);
	//	camera.push_back(cameraTemp);
	//}
	//for (int i = 0; i < SkeletonAnimationCount; i++)
	//{
	//	fileIn.read((char*)&skeleton.numberOfJoints, sizeof(unsigned int));
	//	fileIn.read((char*)&skeleton.numberOfSkinWeights, sizeof(unsigned int));
	//	
	//	for (int j = 0; j < skeleton.numberOfJoints; j++)
	//	{
	//		fileIn.read((char*)&jointHeaderTemp.jointName, sizeof(char) * 256);
	//		fileIn.read((char*)&jointHeaderTemp.ParentID, sizeof(unsigned int));
	//		fileIn.read((char*)&jointHeaderTemp.jointIndex, sizeof(unsigned int));
	//		fileIn.read((char*)&jointHeaderTemp.nrOfKeyframes, sizeof(unsigned int));
	//		fileIn.read((char*)&jointHeaderTemp.globalBindPoseInverse, sizeof(float) * 16);
	//		jointHeader.push_back(jointHeaderTemp);
	//		
	//		for (int k = 0; k < jointHeader.at(j).nrOfKeyframes; k++)
	//		{
	//			fileIn.read((char*)&keyframeTemp.translation, sizeof(float) * 4);
	//			fileIn.read((char*)&keyframeTemp.rotation, sizeof(float) * 4);
	//			fileIn.read((char*)&keyframeTemp.scale, sizeof(float) * 4);
	//			fileIn.read((char*)&keyframeTemp.keyTime, sizeof(float) * 4);
	//			keyframe.push_back(keyframeTemp);
	//		}
	//	}
	//	for (int j = 0; j < skeleton.numberOfSkinWeights; j++)
	//	{
	//		fileIn.read((char*)&skinningTemp.boneIndices, sizeof(unsigned int) * 4);
	//		fileIn.read((char*)&skinningTemp.weights, sizeof(float) * 4);
	//		skinning.push_back(skinningTemp);
	//	}
	//
	//}
	//for (int i = 0; i < MorphAnimationCount; i++)
	//{
	//	fileIn.read((char*)&morphCount.MorphShapeCount, sizeof(unsigned int));
	//	for (int j = 0; j < morphCount.MorphShapeCount; j++)
	//	{
	//		fileIn.read((char*)&morphTemp.MorphShape, sizeof(float) * 4);
	//		morphVector.push_back(morphTemp);
	//	}
	//}

	fileIn.close();
}

void CustomImport::NewMesh()
{
	Mesh newMesh;
	newMesh.MeshCount = MeshCount;
	newMesh.MaterialCount = MaterialCount;

	int count = meshList.size() - newMesh.MeshCount;

	for (int i = count; i < meshList.size(); i++)
	{
		newMesh.meshTemp.VertexCount = meshList.at(i).VertexCount;
		newMesh.meshTemp.MaterialID = meshList.at(i).MaterialID;
		newMesh.meshTemp.MeshID = meshList.at(i).MeshID;
		newMesh.meshTemp.ParentID = meshList.at(i).ParentID;
		for (int j = 0; j < 256; j++)
		{
			newMesh.meshTemp.MeshName[j] = meshList.at(i).MeshName[j];
		}
		newMesh.meshTemp.AttributeCount = meshList.at(i).AttributeCount;
		for (int k = 0; k < 3; k++)
		{
			newMesh.meshTemp.Translation[k] = meshList.at(i).Translation[k];
			newMesh.meshTemp.Rotation[k] = meshList.at(i).Rotation[k];
			newMesh.meshTemp.Scale[k] = meshList.at(i).Scale[k];
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
				newMesh.meshTemp.vertexTemp.pos[m] = meshList.at(i).vertex.at(vertIndex).pos[m];
				newMesh.meshTemp.vertexTemp.nor[m] = meshList.at(i).vertex.at(vertIndex).nor[m];

				newMesh.meshTemp.vertexTemp.tan[m] = meshList.at(i).vertex.at(vertIndex).tan[m];
				newMesh.meshTemp.vertexTemp.bitan[m] = meshList.at(i).vertex.at(vertIndex).bitan[m];
			}
			for (int n = 0; n < 2; n++)
			{
				newMesh.meshTemp.vertexTemp.uv[n] = meshList.at(i).vertex.at(vertIndex).uv[n];
	
			}
			newMesh.meshTemp.vertex.push_back(newMesh.meshTemp.vertexTemp);
		}
		newMesh.mesh.push_back(newMesh.meshTemp);
	}
	int mcount = materials.size() - newMesh.MaterialCount;

	for (int i = mcount; i < materials.size(); i++)
	{
		char temp[256];
		for (int e = 0; e < 256; e++)
		{
			if (materials.at(i).diffuseMap[e] == '\0')
			{
				temp[e] = '\0';
				int snafu = 256 - e;
				for (int w = 1; w < snafu; w++)
				{
					temp[e + w] = '0';
				}
				break;
			}
			temp[e] = materials.at(i).diffuseMap[e];
		}

		for (int p = 256; p > 0; p--)
		{
			if (temp[p] == '/')
			{
				materials.at(i).diffuseMap[0] = '.';
				materials.at(i).diffuseMap[1] = '.';
				materials.at(i).diffuseMap[2] = '/';
				materials.at(i).diffuseMap[3] = 't';
				materials.at(i).diffuseMap[4] = 'x';

				int size = 256 - p;
				p = p - 5;
				for (int q = 5; q < size; q++)
				{
					materials.at(i).diffuseMap[q] = temp[p + q];
				}
				break;
			}
			else if (temp[p] == '\\')
			{
				materials.at(i).diffuseMap[0] = '.';
				materials.at(i).diffuseMap[1] = '.';
				materials.at(i).diffuseMap[2] = '\\';
				materials.at(i).diffuseMap[3] = 't';
				materials.at(i).diffuseMap[4] = 'x';

				int size = 256 - p;
				p = p - 5;
				for (int q = 5; q < size; q++)
				{
					materials.at(i).diffuseMap[q] = temp[p + q];
				}
				break;
			}
		}

		for (int j = 0; j < 3; j++)
		{
			newMesh.materialTemp.diffuseColor[j] = materials.at(i).diffuseColor[j];
			newMesh.materialTemp.specularColor[j] = materials.at(i).specularColor[j];
			newMesh.materialTemp.ambientColor[j] = materials.at(i).ambientColor[j];
		}
		newMesh.materialTemp.transparency = materials.at(i).transparency;
		newMesh.materialTemp.shininess = materials.at(i).shininess;
		newMesh.materialTemp.reflection = materials.at(i).reflection;

		for (int k = 0; k < 256; k++)
		{
			newMesh.materialTemp.diffuseMap[k] = materials.at(i).diffuseMap[k];
		}
		newMesh.material.push_back(newMesh.materialTemp);
	}
	newMesh.textureBool = false;

	meshes.push_back(newMesh);
}