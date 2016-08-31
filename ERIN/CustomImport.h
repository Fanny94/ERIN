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

	/*unsigned int LightCount;
	unsigned int SkeletonAnimationCount;
	unsigned int KeyFrameCount;
	unsigned int MorphAnimationCount;*/

	/*char DiffuseMap[256];
	char NormalMap[256];
	char SpecularMap[256];

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
	float KeyFramePosition[3];*/

public:
	CustomImport();
	~CustomImport();
	void LoadCustomFormat(string filePath);
	void NewMesh();
	vector<Mesh> meshes;
};

#endif // !CUSTOMIMPORT_H