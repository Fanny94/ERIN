#pragma once
#ifndef CUSTOMIMPORT_H
#define CUSTOMIMPORT_H
#include "Linker.h"

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
	float Roatation[3];
	float Scale[3];
public:
	CustomImport();
	~CustomImport();
	void LoadCustomFormat(string filePath);
};

#endif // !CUSTOMIMPORT_H