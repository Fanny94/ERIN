#pragma once
#ifndef CUSTOMIMPORT_H
#define CUSTOMIMPORT_H
#include "Linker.h"
#include "Mesh.h"
#include "Graphics.h"

class Graphics;

class CustomImport
{
private:
	/*
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

	/*unsigned int GroupCount;
	unsigned int LightCount;
	unsigned int SkeletonAnimationCount;
	unsigned int KeyFrameCount;
	unsigned int MorphAnimationCount;
	unsigned int CustomAttributesCount;*/

	/*char DiffuseMap[256];
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
	CustomImport();
	~CustomImport();
	void LoadCustomFormat(string filePath);
	void NewMesh();
	vector<Mesh> meshes;
};

#endif // !CUSTOMIMPORT_H