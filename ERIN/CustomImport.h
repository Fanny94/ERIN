#pragma once
#ifndef CUSTOMIMPORT_H
#define CUSTOMIMPORT_H
#include "Linker.h"

struct Vertex
{
	float pos[3];
	float nor[3];
	float uv[2];
	float tan[3];
	float bitan[3];
};

class CustomImport
{
private:
	unsigned int MeshCount;
	unsigned int MaterialCount;
	unsigned int VertexCount;
	unsigned int MaterialID;
	unsigned int MeshID;
	unsigned int ParentID;
	unsigned int AttributeCount;
	char MeshName[256];
	float Translation[3];
	float Rotation[3];
	float Scale[3];
	vector<Vertex>* vertex;
	Vertex vertexTemp;
	float diffuseColor[3];
	float ambientColor[3];
	float specularColor[3];
	float transparency;
	float shininess;
	float reflection;
	char DiffuseMap[256];
	char NormalMap[256];
	char SpecularMap[256];
public:
	CustomImport();
	~CustomImport();
	void LoadCustomFormat(string filePath);
};

#endif // !CUSTOMIMPORT_H