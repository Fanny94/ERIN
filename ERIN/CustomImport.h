#pragma once
#ifndef CUSTOMIMPORT_H
#define CUSTOMIMPORT_H
#include "Linker.h"
#include "Mesh.h"

class CustomImport
{
private:
	/*struct PointLight
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
	float scale[3];
	};

	struct DirectionalLight
	{
	float intensity;
	float color[3];
	float rotation[3];
	};

	struct AreaLight
	{
	float intensity;
	float color[3];
	float position[3];
	float rotation[3];
	float height;
	float width;
	};

	struct CustomVector
	{
	float cVector[3];
	};

	struct CustomFloat
	{
	float cFloat;
	};

	struct CustomInt
	{
	int cInt;
	};

	struct CustomBool
	{
	bool cBool;
	};

	struct CustomString
	{
	char cString[256];
	};*/

	/*unsigned int MaterialCount;
	unsigned int GroupCount;
	unsigned int LightCount;
	unsigned int CameraCount;
	unsigned int SkeletonAnimationCount;
	unsigned int KeyFrameCount;
	unsigned int MorphAnimationCount;
	unsigned int CustomAttributesCount;*/

	/*float diffuseColor[3];
	float ambientColor[3];
	float specularColor[3];
	float transparency;
	float shininess;
	float reflection;
	char DiffuseMap[256];
	char NormalMap[256];
	char SpecularMap[256];

	unsigned int GroupID;
	unsigned int GGroupCount;
	unsigned int GroupParentID;
	unsigned int GroupMeshID;

	unsigned int PointLightCount;
	unsigned int SpotLightCount;
	unsigned int DirectionalLightCount;
	unsigned int AreaLightCount;
	vector<PointLight> pointLight;
	PointLight pointLightTemp;
	vector<SpotLight> spotLight;
	SpotLight spotLightTemp;
	vector<DirectionalLight> directionalLight;
	DirectionalLight directionalLightTemp;
	vector<AreaLight> areaLight;
	AreaLight areaLightTemp;

	float camPosition[4];
	float camTarget[4];
	float camUp[4];
	float camRight[4];
	float camForward[4];
	float camYaw;
	float camPitch;

	float KeyFrameID;
	float KeyFrameTime;
	float KeyFramePosition[3];

	unsigned int CustomVectorCount;
	unsigned int CustomFloatCount;
	unsigned int CustomIntCount;
	unsigned int CustomBoolCount;
	unsigned int CustomStringCount;
	vector<CustomVector> customVector;
	CustomVector customVectorTemp;
	vector<CustomFloat> customFloat;
	CustomFloat customFloatTemp;
	vector<CustomInt> customInt;
	CustomInt customIntTemp;
	vector<CustomBool> customBool;
	CustomBool customBoolTemp;
	vector<CustomString> customString;
	CustomString customStringTemp;*/

public:
	vector<Mesh> meshes;
	CustomImport();
	~CustomImport();
	void LoadCustomFormat(string filePath);
	void NewMesh();
};

#endif // !CUSTOMIMPORT_H