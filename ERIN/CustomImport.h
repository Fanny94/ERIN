#pragma once
#ifndef CUSTOMIMPORT_H
#define CUSTOMIMPORT_H
#include "Linker.h"
#include "Mesh.h"
#include "Graphics.h"

class Graphics;

class CustomImport
{

public:
	CustomImport();
	~CustomImport();
	void LoadCustomFormat(string filePath);
	void NewMesh();
	vector<Mesh> meshes;
};

#endif // !CUSTOMIMPORT_H