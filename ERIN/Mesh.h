#ifndef MESH_H
#define MESH_H

#include "Linker.h"

class Mesh
{
private:

public:
	Mesh();
	~Mesh();

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

	unsigned int MeshCount;
	vector<MeshStruct> mesh;
	MeshStruct meshTemp;
};
#endif // !MESH_H