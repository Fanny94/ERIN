#pragma once
#ifndef CUSTOMIMPORT_H
#define CUSTOMIMPORT_H
#include "Linker.h"

class CustomImport
{
private:
	unsigned int MeshCount;
	unsigned int VertexCount;
	unsigned int MaterialID;
	unsigned int MeshID;
public:
	CustomImport();
	~CustomImport();
	void LoadCustomFormat(string filePath);
};

#endif // !CUSTOMIMPORT_H